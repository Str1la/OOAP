#include <iostream>
#include <string>
#include <limits>

class Car {
public:
	std::string engineType;
	double engineVolume;
	bool hasABS;
	bool hasESP;
	int airbags;
	bool hasOnboardComputer;
	std::string climateControl;
	std::string interior;
	std::string price;

	void showSpecifications() const {
		std::cout << "Engine Type: " << engineType << std::endl;
		std::cout << "Engine Volume: " << engineVolume << " L" << std::endl;
		std::cout << "ABS: " << (hasABS ? "Yes" : "No") << std::endl;
		std::cout << "ESP: " << (hasESP ? "Yes" : "No") << std::endl;
		std::cout << "Airbags: " << airbags << std::endl;
		std::cout << "Onboard Computer: " << (hasOnboardComputer ? "Yes" : "No") << std::endl;
		std::cout << "Climate Control: " << climateControl << std::endl;
		std::cout << "Interior: " << interior << std::endl;
		std::cout << "Price: $" << price << std::endl;
	}
};

class CarBuilder {
public:
	virtual ~CarBuilder() = default;
	virtual void setEngineType(const std::string& type) = 0;
	virtual void setEngineVolume(double volume) = 0;
	virtual void setABS(bool abs) = 0;
	virtual void setESP(bool esp) = 0;
	virtual void setAirbags(int airbags) = 0;
	virtual void setOnboardComputer(bool hasComputer) = 0;
	virtual void setClimateControl(const std::string& climate) = 0;
	virtual void setInterior(const std::string& interior) = 0;
	virtual void setPrice(const std::string price) = 0;
	virtual Car* getCar() = 0;
};

class BaseCarBuilder : public CarBuilder {
private:
	Car* car;
public:
	BaseCarBuilder() { car = new Car(); }
	~BaseCarBuilder() { delete car; }

	void setEngineType(const std::string& type = "Petrol") override { car->engineType = type; }
	void setEngineVolume(double volume = 1.4) override { car->engineVolume = volume; }
	void setABS(bool abs) override { car->hasABS = false; }
	void setESP(bool esp) override { car->hasESP = false; }
	void setAirbags(int airbags = 2) override { car->airbags = airbags; }
	void setOnboardComputer(bool hasComputer) override { car->hasOnboardComputer = false; }
	void setClimateControl(const std::string& climate = "None") override { car->climateControl = climate; }
	void setInterior(const std::string& interior = "Fabric") override { car->interior = interior; }
	void setPrice(std::string price = "15000") override { car->price = price; }

	Car* getCar() override { return car; }
};

class ComfortCarBuilder : public CarBuilder {
private:
	Car* car;
public:
	ComfortCarBuilder() { car = new Car(); }
	~ComfortCarBuilder() { delete car; }

	void setEngineType(const std::string& type = "Petrol") override { car->engineType = type; }
	void setEngineVolume(double volume = 1.6) override { car->engineVolume = volume; }
	void setABS(bool abs) override { car->hasABS = true; }
	void setESP(bool esp) override { car->hasESP = true; }
	void setAirbags(int airbags = 4) override { car->airbags = airbags; }
	void setOnboardComputer(bool hasComputer) override { car->hasOnboardComputer = true; }
	void setClimateControl(const std::string& climate = "Air Conditioner") override { car->climateControl = climate; }
	void setInterior(const std::string& interior = "Improved Fabric") override { car->interior = interior; }
	void setPrice(std::string price = "20000") override { car->price = price; }

	Car* getCar() override { return car; }
};

class LuxuryCarBuilder : public CarBuilder {
private:
	Car* car;
public:
	LuxuryCarBuilder() { car = new Car(); }
	~LuxuryCarBuilder() { delete car; }

	void setEngineType(const std::string& type = "Disel") override { car->engineType = type; }
	void setEngineVolume(double volume = 2.0) override { car->engineVolume = volume; }
	void setABS(bool abs) override { car->hasABS = true; }
	void setESP(bool esp) override { car->hasESP = true; }
	void setAirbags(int airbags = 6) override { car->airbags = airbags; }
	void setOnboardComputer(bool hasComputer) override { car->hasOnboardComputer = true; }
	void setClimateControl(const std::string& climate = "Climate Control") override { car->climateControl = climate; }
	void setInterior(const std::string& interior = "Leather") override { car->interior = interior; }
	void setPrice(std::string price = "30000") override { car->price = price; }

	Car* getCar() override { return car; }
};

class ElectricCarBuilder : public CarBuilder {
private:
	Car* car;
public:
	ElectricCarBuilder() { car = new Car(); }
	~ElectricCarBuilder() { delete car; }

	void setEngineType(const std::string& type) override { car->engineType = "Electric"; }
	void setEngineVolume(double volume) override { car->engineVolume = 0.0; }
	void setABS(bool abs) override { car->hasABS = true; }
	void setESP(bool esp) override { car->hasESP = true; }
	void setAirbags(int airbags = 8) override { car->airbags = airbags; }
	void setOnboardComputer(bool hasComputer) override { car->hasOnboardComputer = true; }
	void setClimateControl(const std::string& climate = "Advanced Climate Control") override { car->climateControl = climate; }
	void setInterior(const std::string& interior = "Electric Leather") override { car->interior = interior; }
	void setPrice(std::string price = "45000") override { car->price = price; }

	Car* getCar() override { return car; }
};

class CarDirector {
private:
	CarBuilder* builder;
public:
	void setBuilder(CarBuilder* newBuilder) {
		builder = newBuilder;
	}

	void buildCar() {
		builder->setEngineType("Petrol");
		builder->setEngineVolume(1.6);
		builder->setABS(true);
		builder->setESP(true);
		builder->setAirbags(4);
		builder->setOnboardComputer(true);
		builder->setClimateControl("Air Conditioner");
		builder->setInterior("Fabric");
		builder->setPrice("20000");
	}

	void buildCustomCar() {
		std::string engineType, climateControl, interior, price = "Udefined";
		double engineVolume = 0.0;
		bool hasABS = false, hasESP = false, hasOnboardComputer = false;
		int airbags = 0;

		std::cout << "Enter Engine Type: ";
		std::cin >> engineType;

		while (true) {
			std::cout << "Enter Engine Volume: ";
			std::cin >> engineVolume;
			if (std::cin.fail() || engineVolume <= 0) {
				std::cout << "Invalid input! Engine volume must be a positive number.\n";
				clearInputStream();
			}
			else {
				break;
			}
		}

		while (true) {
			std::cout << "Enter number of Airbags: ";
			std::cin >> airbags;
			if (std::cin.fail() || airbags < 0) {
				std::cout << "Invalid input! Number of airbags must be a non-negative integer.\n";
				clearInputStream();
			}
			else {
				break;
			}
		}

		std::cout << "Enter Climate Control: ";
		std::cin >> climateControl;

		std::cout << "Enter Interior: ";
		std::cin >> interior;

		builder->setEngineType(engineType);
		builder->setEngineVolume(engineVolume);
		builder->setABS(hasABS);
		builder->setESP(hasESP);
		builder->setAirbags(airbags);
		builder->setOnboardComputer(hasOnboardComputer);
		builder->setClimateControl(climateControl);
		builder->setInterior(interior);
		builder->setPrice(price);
	}


	Car* getCar() {
		return builder->getCar();
	}
	void clearInputStream() {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};

void clearInputStream() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void buildAndCopySpecifications(CarDirector& director, CarBuilder* baseBuilder, CarBuilder* comfortBuilder, CarBuilder* luxuryBuilder, CarBuilder* electricBuilder) {
	std::cout << "Enter the specifications for all cars:\n";

	director.setBuilder(baseBuilder);
	director.buildCustomCar();
	Car* baseCar = director.getCar();

	director.setBuilder(comfortBuilder);
	comfortBuilder->setEngineType(baseCar->engineType);
	comfortBuilder->setEngineVolume(baseCar->engineVolume);
	comfortBuilder->setABS(baseCar->hasABS);
	comfortBuilder->setESP(baseCar->hasESP);
	comfortBuilder->setAirbags(baseCar->airbags);
	comfortBuilder->setOnboardComputer(baseCar->hasOnboardComputer);
	comfortBuilder->setClimateControl(baseCar->climateControl);
	comfortBuilder->setInterior(baseCar->interior);
	comfortBuilder->setPrice(baseCar->price);

	director.setBuilder(luxuryBuilder);
	luxuryBuilder->setEngineType(baseCar->engineType);
	luxuryBuilder->setEngineVolume(baseCar->engineVolume);
	luxuryBuilder->setABS(baseCar->hasABS);
	luxuryBuilder->setESP(baseCar->hasESP);
	luxuryBuilder->setAirbags(baseCar->airbags);
	luxuryBuilder->setOnboardComputer(baseCar->hasOnboardComputer);
	luxuryBuilder->setClimateControl(baseCar->climateControl);
	luxuryBuilder->setInterior(baseCar->interior);
	luxuryBuilder->setPrice(baseCar->price);

	director.setBuilder(electricBuilder);
	electricBuilder->setEngineType(baseCar->engineType);
	electricBuilder->setEngineVolume(baseCar->engineVolume);
	electricBuilder->setABS(baseCar->hasABS);
	electricBuilder->setESP(baseCar->hasESP);
	electricBuilder->setAirbags(baseCar->airbags);
	electricBuilder->setOnboardComputer(baseCar->hasOnboardComputer);
	electricBuilder->setClimateControl(baseCar->climateControl);
	electricBuilder->setInterior(baseCar->interior);
	electricBuilder->setPrice(baseCar->price);

	std::cout << "\nBase Car Specifications:\n";
	baseCar->showSpecifications();

	std::cout << "\nComfort Car Specifications:\n";
	comfortBuilder->getCar()->showSpecifications();

	std::cout << "\nLuxury Car Specifications:\n";
	luxuryBuilder->getCar()->showSpecifications();

	std::cout << "\nElectric Car Specifications:\n";
	electricBuilder->getCar()->showSpecifications();
}


int main() {
	CarDirector director;
	CarBuilder* baseBuilder = new BaseCarBuilder();
	CarBuilder* comfortBuilder = new ComfortCarBuilder();
	CarBuilder* luxuryBuilder = new LuxuryCarBuilder();
	CarBuilder* electricBuilder = new ElectricCarBuilder();

	int choice;
	while (true) {
		std::cout << "Select configuration: (1) Base, (2) Comfort, (3) Luxury, (4) Electric, (5) All Cars\n";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cout << "Invalid input. Please enter a number.\n";
			clearInputStream();
			continue;
		}

		if (choice >= 1 && choice <= 5) {
			break;
		}

		std::cout << "Invalid choice. Please select between 1 and 5.\n";
	}

	int customChoice;
	std::cout << "Do you want to use a pre-defined template (1) or create your own (2)?\n";
	std::cin >> customChoice;

	if (choice == 5) {
		if (customChoice == 1) {
			director.setBuilder(baseBuilder);
			director.buildCar();
			Car* baseCar = director.getCar();

			director.setBuilder(comfortBuilder);
			director.buildCar();
			Car* comfortCar = director.getCar();

			director.setBuilder(luxuryBuilder);
			director.buildCar();
			Car* luxuryCar = director.getCar();

			director.setBuilder(electricBuilder);
			director.buildCar();
			Car* electricCar = director.getCar();

			std::cout << "\nBase Car Specifications:\n";
			baseCar->showSpecifications();

			std::cout << "\nComfort Car Specifications:\n";
			comfortCar->showSpecifications();

			std::cout << "\nLuxury Car Specifications:\n";
			luxuryCar->showSpecifications();

			std::cout << "\nElectric Car Specifications:\n";
			electricCar->showSpecifications();
		}
		else {
			buildAndCopySpecifications(director, baseBuilder, comfortBuilder, luxuryBuilder, electricBuilder);
		}
	}
	else {
		if (customChoice == 1) {
			switch (choice) {
			case 1:
				director.setBuilder(baseBuilder);
				break;
			case 2:
				director.setBuilder(comfortBuilder);
				break;
			case 3:
				director.setBuilder(luxuryBuilder);
				break;
			case 4:
				director.setBuilder(electricBuilder);
				break;
			}
			director.buildCar();
		}
		else {
			switch (choice) {
			case 1:
				director.setBuilder(baseBuilder);
				break;
			case 2:
				director.setBuilder(comfortBuilder);
				break;
			case 3:
				director.setBuilder(luxuryBuilder);
				break;
			case 4:
				director.setBuilder(electricBuilder);
				break;
			}
			director.buildCustomCar();
		}

		Car* car = director.getCar();
		std::cout << "\nCar Specifications:\n";
		car->showSpecifications();
	}

	delete baseBuilder;
	delete comfortBuilder;
	delete luxuryBuilder;
	delete electricBuilder;

	return 0;
}