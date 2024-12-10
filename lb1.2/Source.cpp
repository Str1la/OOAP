#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using std::string;
using std::unique_ptr;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::make_unique;

class IPerson {
public:
    virtual string getName() const = 0;
    virtual void printInfo() const = 0;
    virtual void changeAddress(const string& newCity, const string& newStreet, const string& newBuilding) = 0;
    virtual ~IPerson() = default;
};

class IAddressBook {
public:
    virtual void addEntry(unique_ptr<IPerson> person) = 0;
    virtual void removeEntry(const string& name) = 0;
    virtual void printEntries() const = 0;
    virtual void changePersonAddress(const string& name, const string& newCity, const string& newStreet, const string& newBuilding) = 0;
    virtual ~IAddressBook() = default;
};

class Address {
    string city;
    string street;
    string building;
public:
    Address(const string& city, const string& street, const string& building)
        : city(city), street(street), building(building) {}

    string getFullAddress() const {
        return city + ", " + street + ", " + building;
    }

    void changeAddress(const string& newCity, const string& newStreet, const string& newBuilding) {
        city = newCity;
        street = newStreet;
        building = newBuilding;
    }
};

class Person : public IPerson {
    string name;
    unique_ptr<Address> address;
public:
    Person(string name, unique_ptr<Address> address)
        : name(name), address(move(address)) {}

    string getName() const override { return name; }

    void printInfo() const override {
        cout << "Name: " << name << ", Address: " << address->getFullAddress() << endl;
    }

    void changeAddress(const string& newCity, const string& newStreet, const string& newBuilding) override {
        address->changeAddress(newCity, newStreet, newBuilding);
    }
};


class AddressBookManager {
public:
    void addEntry(vector<unique_ptr<IPerson>>& entries, unique_ptr<IPerson> person) {
        entries.push_back(move(person));
    }

    void removeEntry(vector<unique_ptr<IPerson>>& entries, const string& name) {
        auto it = remove_if(entries.begin(), entries.end(),
            [&name](const unique_ptr<IPerson>& person) { return person->getName() == name; });
        if (it != entries.end()) {
            entries.erase(it, entries.end());
            cout << "Entry for " << name << " removed.\n";
        }
        else {
            cout << "Entry for " << name << " not found.\n";
        }
    }

    void printEntries(const vector<unique_ptr<IPerson>>& entries) const {
        for (const auto& person : entries) {
            person->printInfo();
        }
    }

    IPerson* findPerson(vector<unique_ptr<IPerson>>& entries, const string& name) {
        for (auto& person : entries) {
            if (person->getName() == name) {
                return person.get();
            }
        }
        return nullptr;
    }
};

class AddressBook : public IAddressBook {
    vector<unique_ptr<IPerson>> entries;
    AddressBookManager manager;
public:
    void addEntry(unique_ptr<IPerson> person) override {
        manager.addEntry(entries, move(person));
    }

    void removeEntry(const string& name) override {
        manager.removeEntry(entries, name);
    }

    void printEntries() const override {
        manager.printEntries(entries);
    }

    void changePersonAddress(const string& name, const string& newCity, const string& newStreet, const string& newBuilding) override {
        IPerson* person = manager.findPerson(entries, name);
        if (person) {
            person->changeAddress(newCity, newStreet, newBuilding);
            cout << "Address for " << name << " changed.\n";
        }
        else {
            cout << "Person not found.\n";
        }
    }
};

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    unique_ptr<IAddressBook> addressBook = make_unique<AddressBook>();

    unique_ptr<Address> address1 = make_unique<Address>(string("Kyiv"), string("Khreshchatyk"), string("1"));
    unique_ptr<IPerson> person1 = make_unique<Person>(string("Taras"), move(address1));
    addressBook->addEntry(move(person1));

    unique_ptr<Address> address2 = make_unique<Address>(string("Lviv"), string("Styiska"), string("22"));
    unique_ptr<IPerson> person2 = make_unique<Person>(string("Stepan"), move(address2));
    addressBook->addEntry(move(person2));

    unique_ptr<Address> address3 = make_unique<Address>(string("Lviv"), string("Kulparkivska"), string("221"));
    unique_ptr<IPerson> person3 = make_unique<Person>(string("Yevhen"), move(address3));
    addressBook->addEntry(move(person3));

    int choice;

    do {
        cout << "-------------------------------------------";
        cout << "\nMenu:\n";
        cout << "1. Add entry\n";
        cout << "2. Remove entry\n";
        cout << "3. Print all entries\n";
        cout << "4. Change address\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputStream();
            continue;
        }

        switch (choice) {
        case 1: {
            string name, city, street, building;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter street: ";
            cin >> street;
            cout << "Enter building: ";
            cin >> building;

            unique_ptr<Address> address = make_unique<Address>(city, street, building);
            unique_ptr<IPerson> person = make_unique<Person>(name, move(address));
            addressBook->addEntry(move(person));
            cout << "Entry added.\n";
            break;
        }
        case 2: {
            string name;
            cout << "Enter name to remove: ";
            cin >> name;
            addressBook->removeEntry(name);
            break;
        }
        case 3: {
            addressBook->printEntries();
            break;
        }
        case 4: {
            string name, newCity, newStreet, newBuilding;
            cout << "Enter name to change address: ";
            cin >> name;

            cout << "Enter new city: ";
            cin >> newCity;
            cout << "Enter new street: ";
            cin >> newStreet;
            cout << "Enter new building: ";
            cin >> newBuilding;

            addressBook->changePersonAddress(name, newCity, newStreet, newBuilding);
            break;
        }
        case 5:
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
