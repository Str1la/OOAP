#include <iostream>
#include <string>
#include <vector>
#include <memory>

class RentalImplementation {
public:
    virtual ~RentalImplementation() = default;
    virtual double getSnowboardPrice() const = 0;
    virtual double getSetupPrice() const = 0;
};

class StandardRental : public RentalImplementation {
public:
    double getSnowboardPrice() const override {
        return 20.0;
    }

    double getSetupPrice() const override {
        return 10.0;
    }
};

class PremiumRental : public RentalImplementation {
public:
    double getSnowboardPrice() const override {
        return 40.0;
    }

    double getSetupPrice() const override {
        return 20.0;
    }
};

class SkiMuneris {
protected:
    std::shared_ptr<RentalImplementation> rentalImpl;

public:
    SkiMuneris(std::shared_ptr<RentalImplementation> impl) : rentalImpl(std::move(impl)) {}
    virtual ~SkiMuneris() = default;
    virtual void addSnowboard(const std::string& brand, int size, const std::string& direction) = 0;
    virtual double calculateTotalPrice() const = 0;
    virtual void displayOrder() const = 0;
    void setRentalImplementation(std::shared_ptr<RentalImplementation> impl) {
        rentalImpl = std::move(impl);
    }
};

class SnowboardRental : public SkiMuneris {
    struct Snowboard {
        std::string brand;
        int shoeSize;
        std::string direction;
    };

    std::vector<Snowboard> snowboards;

public:
    SnowboardRental(std::shared_ptr<RentalImplementation> impl) : SkiMuneris(std::move(impl)) {}

    void addSnowboard(const std::string& brand, int size, const std::string& direction) override {
        snowboards.push_back({ brand, size, direction });
    }

    double calculateTotalPrice() const override {
        double total = 0.0;
        for (const auto& snowboard : snowboards) {
            total += rentalImpl->getSnowboardPrice() + rentalImpl->getSetupPrice();
        }
        return total;
    }

    void displayOrder() const override {
        if (snowboards.empty()) {
            std::cout << "No snowboards in the order.\n";
            return;
        }

        std::cout << "Snowboard Rental Order:\n";
        for (size_t i = 0; i < snowboards.size(); ++i) {
            const auto& sb = snowboards[i];
            std::cout << i + 1 << ". Brand: " << sb.brand
                << ", Shoe Size: " << sb.shoeSize
                << ", Direction: " << sb.direction << "\n";
        }
        std::cout << "Total Price: $" << calculateTotalPrice() << "\n";
    }
};

int main() {
    std::shared_ptr<RentalImplementation> standardRental = std::make_shared<StandardRental>();
    std::shared_ptr<RentalImplementation> premiumRental = std::make_shared<PremiumRental>();

    SnowboardRental rental(standardRental);

    int choice;
    do {
        std::cout << "\nSnowboard Rental Menu:\n"
            << "1. Add snowboard to order\n"
            << "2. Show order details\n"
            << "3. Switch to Premium Rental\n"
            << "4. Switch to Standard Rental\n"
            << "0. Exit\n"
            << "Your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string brand, direction;
            int size;
            std::cout << "Enter snowboard brand: ";
            std::cin >> brand;
            std::cout << "Enter shoe size: ";
            std::cin >> size;
            std::cout << "Enter binding direction (left/right): ";
            std::cin >> direction;
            rental.addSnowboard(brand, size, direction);
        }
        else if (choice == 2) {
            rental.displayOrder();
        }
        else if (choice == 3) {
            rental.setRentalImplementation(premiumRental);
            std::cout << "Switched to Premium Rental.\n";
        }
        else if (choice == 4) {
            rental.setRentalImplementation(standardRental);
            std::cout << "Switched to Standard Rental.\n";
        }
        else if (choice != 0) {
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
