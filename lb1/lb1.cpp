#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <limits>
#include <cctype>

class User {
public:
    User(const std::string& name) : name_(name) {}

    std::string getName() const {
        return name_;
    }

private:
    const std::string name_;
};

class Car {
public:
    Car() : model_(""), currentUser_(nullptr) {}

    Car(const std::string& model)
        : model_(model), currentUser_(nullptr) {}

    std::string getModel() const {
        return model_;
    }

    std::shared_ptr<User> getCurrentUser() const {
        return currentUser_;
    }

    const std::vector<std::shared_ptr<User>>& getUserHistory() const {
        return userHistory_;
    }

    Car assignUser(std::shared_ptr<User> newUser) {
        if (currentUser_ != nullptr) {
            userHistory_.push_back(currentUser_);
        }
        currentUser_ = newUser;
        return *this;
    }

    bool isAvailable() const {
        return currentUser_ == nullptr;
    }

private:
    std::string model_;
    std::shared_ptr<User> currentUser_;
    std::vector<std::shared_ptr<User>> userHistory_;
};

class RegistrationSystem {
public:
    void addUser(const std::string& name) {
        if (users_.find(name) != users_.end()) {
            std::cout << "User already exists." << std::endl;
            return;
        }
        users_[name] = std::make_shared<User>(name);
        std::cout << "User added: " << name << std::endl;
    }

    void addCar(const std::string& model) {
        if (cars_.find(model) != cars_.end()) {
            std::cout << "Car already exists." << std::endl;
            return;
        }
        cars_[model] = Car(model);
        std::cout << "Car added: " << model << std::endl;
    }

    void assignCarToUser(const std::string& model, const std::string& userName) {
        if (cars_.find(model) == cars_.end()) {
            std::cout << "Car not found." << std::endl;
            return;
        }
        if (users_.find(userName) == users_.end()) {
            std::cout << "User not found." << std::endl;
            return;
        }

        Car& car = cars_[model];
        if (!car.isAvailable()) {
            std::cout << "Car was assigned to another user. Previous user information is saved." << std::endl;
        }

        car.assignUser(users_[userName]);
        std::cout << "Car " << model << " assigned to user " << userName << std::endl;
    }

    void showUsers() const {
        if (users_.empty()) {
            std::cout << "No users available." << std::endl;
            return;
        }
        std::cout << "Users list:" << std::endl;
        for (const auto& [name, user] : users_) {
            std::cout << "- " << name << std::endl;
        }
    }

    void showCars() const {
        if (cars_.empty()) {
            std::cout << "No cars available." << std::endl;
            return;
        }
        std::cout << "Cars list:" << std::endl;
        for (const auto& [model, car] : cars_) {
            std::cout << "- " << model;
            if (car.getCurrentUser()) {
                std::cout << " (current user: " << car.getCurrentUser()->getName() << ")";
            }
            std::cout << std::endl;
        }
    }

    void showCarHistory(const std::string& model) const {
        if (cars_.find(model) == cars_.end()) {
            std::cout << "Car not found." << std::endl;
            return;
        }

        const Car& car = cars_.at(model);
        std::cout << "Car model: " << car.getModel() << std::endl;
        std::cout << "Current user: " << (car.getCurrentUser() ? car.getCurrentUser()->getName() : "None") << std::endl;

        std::cout << "User history:" << std::endl;
        const auto& history = car.getUserHistory();
        if (history.empty()) {
            std::cout << "No previous users." << std::endl;
        }
        else {
            for (const auto& user : history) {
                std::cout << "- " << user->getName() << std::endl;
            }
        }
    }

    void initializeData() {
        addUser("John");
        addUser("Alice");
        addUser("Bob");

        addCar("Tesla");
        addCar("BMW");
        addCar("Audi");

        assignCarToUser("Tesla", "John");
        assignCarToUser("BMW", "Alice");
        assignCarToUser("Audi", "Bob");
    }

private:
    std::unordered_map<std::string, std::shared_ptr<User>> users_;
    std::unordered_map<std::string, Car> cars_;
};

void menu() {
    std::cout << "-------------------------------------------------------";
    std::cout << "\n1. Add new user\n";
    std::cout << "2. Add new car\n";
    std::cout << "3. Assign car to user\n";
    std::cout << "4. Show all users\n";
    std::cout << "5. Show all cars\n";
    std::cout << "6. Show car history\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

bool getValidChoice(int& choice) {
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    RegistrationSystem system;
    system.initializeData();
    std::system("cls");

    int choice;
    std::string name, model;

    do {
        menu();
        if (!getValidChoice(choice)) {
            std::cout << "Invalid input. Please enter a number.\n" << std::endl;
            continue;
        }
        std::cout << '\n';

        switch (choice) {
        case 1:
            std::cout << "Enter user name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);
            system.addUser(name);
            break;

        case 2:
            std::cout << "Enter car model: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, model);
            system.addCar(model);
            break;

        case 3:
            std::cout << "Enter car model: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, model);
            std::cout << "Enter user name: ";
            std::getline(std::cin, name);
            system.assignCarToUser(model, name);
            break;

        case 4:
            system.showUsers();
            break;

        case 5:
            system.showCars();
            break;

        case 6:
            std::cout << "Enter car model: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, model);
            system.showCarHistory(model);
            break;

        case 7:
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 7);

    return 0;
}
