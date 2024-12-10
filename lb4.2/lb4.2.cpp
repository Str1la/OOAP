#include <iostream>
#include <memory>

class Laptop {
public:
    virtual void plugIn() = 0;
    virtual ~Laptop() = default;
};

class MyLaptop : public Laptop {
public:
    void plugIn() override {
        std::cout << "Laptop is plugged in and charging.\n";
    }
};

class NewVagonSystem {
public:
    virtual void matchSocket() = 0;
    virtual ~NewVagonSystem() = default;
};

class NewVagon : public NewVagonSystem {
public:
    void matchSocket() override {
        std::cout << "New vagon system: Socket matched. Charging...\n";
    }
};

class OldVagonSystem {
public:
    virtual void thinSocket() = 0;
    virtual ~OldVagonSystem() = default;
};

class OldVagon : public OldVagonSystem {
public:
    void thinSocket() override {
        std::cout << "Old vagon system: Thin socket found. Adapter required.\n";
    }
};

class Adapter : public NewVagonSystem {
    std::shared_ptr<OldVagonSystem> oldVagon;

public:
    Adapter(std::shared_ptr<OldVagonSystem> oldVagonSystem) : oldVagon(std::move(oldVagonSystem)) {}

    void matchSocket() override {
        std::cout << "Adapter in use: Converting thin socket to match socket.\n";
        oldVagon->thinSocket();
        std::cout << "Adapter: Conversion successful. Charging laptop.\n";
    }
};

void travelSimulation(Laptop& laptop, NewVagonSystem& vagonSystem) {
    vagonSystem.matchSocket();
    laptop.plugIn();
}

int main() {
    std::shared_ptr<Laptop> myLaptop = std::make_shared<MyLaptop>();

    NewVagon modernVagon;

    std::cout << "Case 1: Modern vagon:\n";
    travelSimulation(*myLaptop, modernVagon);

    std::shared_ptr<OldVagonSystem> oldVagon = std::make_shared<OldVagon>();
    Adapter adapter(oldVagon);

    std::cout << "\nCase 2: Old vagon with adapter:\n";
    travelSimulation(*myLaptop, adapter);

    return 0;
}
