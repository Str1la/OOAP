#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

class House {
public:
    virtual ~House() = default;

    virtual void displayInfo() const = 0;
    virtual void editInfo() = 0;
    virtual std::unique_ptr<House> clone() const = 0;

protected:
    std::string address;
    int floors;
    double area;
};

class ApartmentBuilding : public House {
public:
    ApartmentBuilding(const std::string& addr, int fl, double ar, const std::vector<std::string>& owners)
        : owners(owners) {
        address = addr;
        floors = fl;
        area = ar;
    }

    void displayInfo() const override {
        std::cout << "Apartment building:\n"
            << "Address: " << address << "\n"
            << "Floors: " << floors << "\n"
            << "Area: " << area << " sq.m\n"
            << "Owners:\n";
        for (const auto& owner : owners) {
            std::cout << "- " << owner << "\n";
        }
    }

    void editInfo() override {
        std::cout << "Edit apartment building.\n";
        std::cout << "Enter new address: ";
        std::cin >> address;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        std::cout << "Enter area: ";
        std::cin >> area;

        std::cout << "Enter number of owners: ";
        int numOwners;
        std::cin >> numOwners;
        owners.clear();
        for (int i = 0; i < numOwners; ++i) {
            std::string owner;
            std::cout << "Owner " << (i + 1) << ": ";
            std::cin >> owner;
            owners.push_back(owner);
        }
    }

    std::unique_ptr<House> clone() const override {
        return std::make_unique<ApartmentBuilding>(*this);
    }

private:
    std::vector<std::string> owners;
};

class Cottage : public House {
public:
    Cottage(const std::string& addr, int fl, double ar, const std::string& owner)
        : owner(owner) {
        address = addr;
        floors = fl;
        area = ar;
    }

    void displayInfo() const override {
        std::cout << "Cottage:\n"
            << "Address: " << address << "\n"
            << "Floors: " << floors << "\n"
            << "Area: " << area << " sq.m\n"
            << "Owner: " << owner << "\n";
    }

    void editInfo() override {
        std::cout << "Edit cottage.\n";
        std::cout << "Enter new address: ";
        std::cin >> address;
        std::cout << "Enter number of floors: ";
        std::cin >> floors;
        std::cout << "Enter area: ";
        std::cin >> area;
        std::cout << "Enter new owner: ";
        std::cin >> owner;
    }

    std::unique_ptr<House> clone() const override {
        return std::make_unique<Cottage>(*this);
    }

private:
    std::string owner;
};

class HousePrototypeFactory {
public:
    void registerPrototype(const std::string& type, std::unique_ptr<House> prototype) {
        prototypes[type] = std::move(prototype);
    }

    std::unique_ptr<House> createHouse(const std::string& type) {
        if (prototypes.find(type) != prototypes.end()) {
            return prototypes[type]->clone();
        }
        throw std::invalid_argument("Unknown house type");
    }

private:
    std::unordered_map<std::string, std::unique_ptr<House>> prototypes;
};

int main() {
    HousePrototypeFactory factory;

    factory.registerPrototype("ApartmentBuilding",
        std::make_unique<ApartmentBuilding>("DefaultAddress", 5, 500.0, std::vector<std::string>{"Owner1", "Owner2"}));

    factory.registerPrototype("Cottage",
        std::make_unique<Cottage>("DefaultAddress", 2, 120.0, "DefaultOwner"));

    std::vector<std::unique_ptr<House>> houses;

    int choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Add apartment building\n"
            << "2. Add cottage\n"
            << "3. Show all houses\n"
            << "4. Edit house\n"
            << "0. Exit\n"
            << "Choice: ";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            try {
                std::string type = (choice == 1) ? "ApartmentBuilding" : "Cottage";
                auto house = factory.createHouse(type);
                house->editInfo();
                houses.push_back(std::move(house));
            }
            catch (const std::exception& ex) {
                std::cerr << "Error: " << ex.what() << "\n";
            }
        }
        else if (choice == 3) {
            if (houses.empty()) {
                std::cout << "No houses available.\n";
            }
            else {
                for (size_t i = 0; i < houses.size(); ++i) {
                    std::cout << "House " << (i + 1) << ":\n";
                    houses[i]->displayInfo();
                    std::cout << "\n";
                }
            }
        }
        else if (choice == 4) {
            std::cout << "Enter house number to edit: ";
            size_t index;
            std::cin >> index;
            if (index > 0 && index <= houses.size()) {
                houses[index - 1]->editInfo();
            }
            else {
                std::cerr << "Invalid house number.\n";
            }
        }
    } while (choice != 0);

    return 0;
}
