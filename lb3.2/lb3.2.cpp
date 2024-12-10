#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <vector>

constexpr double g_pi{ 3.1415 };

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual std::string color() const = 0;
    virtual std::pair<double, double> boundingCircleCenter() const = 0;
    virtual void display() const = 0;
};

class Circle : public Shape {
public:
    Circle(double x, double y, double r, const std::string& c)
        : centerX(x), centerY(y), radius(r), shapeColor(c) {}

    double area() const override {
        return g_pi * radius * radius;
    }

    std::string color() const override {
        return shapeColor;
    }

    std::pair<double, double> boundingCircleCenter() const override {
        return { centerX, centerY };
    }

    void display() const override {
        std::cout << "Circle: center=(" << centerX << ", " << centerY
            << "), radius=" << radius << ", color=" << shapeColor << "\n";
    }

private:
    double centerX, centerY, radius;
    std::string shapeColor;
};

class Rectangle : public Shape {
public:
    Rectangle(double x, double y, double w, double h, const std::string& c)
        : centerX(x), centerY(y), width(w), height(h), shapeColor(c) {}

    double area() const override {
        return width * height;
    }

    std::string color() const override {
        return shapeColor;
    }

    std::pair<double, double> boundingCircleCenter() const override {
        return { centerX, centerY };
    }

    void display() const override {
        std::cout << "Rectangle: center=(" << centerX << ", " << centerY
            << "), width=" << width << ", height=" << height
            << ", color=" << shapeColor << "\n";
    }

private:
    double centerX, centerY, width, height;
    std::string shapeColor;
};

class Triangle : public Shape {
public:
    Triangle(double x, double y, double base, double height, const std::string& c)
        : centerX(x), centerY(y), baseLength(base), heightLength(height), shapeColor(c) {}

    double area() const override {
        return 0.5 * baseLength * heightLength;
    }

    std::string color() const override {
        return shapeColor;
    }

    std::pair<double, double> boundingCircleCenter() const override {
        return { centerX, centerY };
    }

    void display() const override {
        std::cout << "Triangle: center=(" << centerX << ", " << centerY
            << "), base=" << baseLength << ", height=" << heightLength
            << ", color=" << shapeColor << "\n";
    }

private:
    double centerX, centerY, baseLength, heightLength;
    std::string shapeColor;
};

class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;
    virtual std::unique_ptr<Shape> createShape() const = 0;
};

class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        double x, y, r;
        std::string color;
        std::cout << "Enter center (x, y): ";
        std::cin >> x >> y;
        std::cout << "Enter radius: ";
        std::cin >> r;
        std::cout << "Enter color: ";
        std::cin >> color;
        return std::make_unique<Circle>(x, y, r, color);
    }
};

class RectangleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        double x, y, w, h;
        std::string color;
        std::cout << "Enter center (x, y): ";
        std::cin >> x >> y;
        std::cout << "Enter width and height: ";
        std::cin >> w >> h;
        std::cout << "Enter color: ";
        std::cin >> color;
        return std::make_unique<Rectangle>(x, y, w, h, color);
    }
};

class TriangleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        double x, y, base, height;
        std::string color;
        std::cout << "Enter center (x, y): ";
        std::cin >> x >> y;
        std::cout << "Enter base and height: ";
        std::cin >> base >> height;
        std::cout << "Enter color: ";
        std::cin >> color;
        return std::make_unique<Triangle>(x, y, base, height, color);
    }
};

int main() {
    std::unique_ptr<ShapeFactory> factory;
    std::vector<std::unique_ptr<Shape>> shapes;

    int choice;
    do {
        std::cout << "\nMenu:\n"
            << "1. Create Circle\n"
            << "2. Create Rectangle\n"
            << "3. Create Triangle\n"
            << "4. Display All Shapes\n"
            << "0. Exit\n"
            << "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            factory = std::make_unique<CircleFactory>();
        }
        else if (choice == 2) {
            factory = std::make_unique<RectangleFactory>();
        }
        else if (choice == 3) {
            factory = std::make_unique<TriangleFactory>();
        }
        else if (choice == 4) {
            if (shapes.empty()) {
                std::cout << "No shapes created.\n";
            }
            else {
                for (const auto& shape : shapes) {
                    shape->display();
                    std::cout << "Area: " << shape->area() << "\n"
                        << "Color: " << shape->color() << "\n"
                        << "Bounding Circle Center: ("
                        << shape->boundingCircleCenter().first << ", "
                        << shape->boundingCircleCenter().second << ")\n\n";
                }
            }
            continue;
        }
        else if (choice == 0) {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
            continue;
        }

        if (factory) {
            shapes.push_back(factory->createShape());
        }
    } while (choice != 0);

    return 0;
}
