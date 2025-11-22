#include <iostream>
#include <numbers>
#include <cmath>
#include <cassert>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
};

class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double first, double second, double third) 
        : side1(first), side2(second), side3(third) {}

    double area() const override final {
        double semiPerimeter = perimeter() / 2.0;
        double product = semiPerimeter * (semiPerimeter - side1) * 
                        (semiPerimeter - side2) * (semiPerimeter - side3);
        return std::sqrt(product);
    }

    double perimeter() const override final {
        return side1 + side2 + side3;
    }
};

class Square final : public Shape {
private:
    double sideLength;

public:
    Square(double length) : sideLength(length) {}

    double area() const override {
        return sideLength * sideLength;
    }

    double perimeter() const override {
        return 4.0 * sideLength;
    }
};

class Circle final : public Shape {
    private:
        double circleRadius;
    
    public:
        Circle(double r) : circleRadius(r) {}
    
        double area() const override {
            return std::numbers::pi * circleRadius * circleRadius;
        }
    
        double perimeter() const override {
            return 2.0 * std::numbers::pi * circleRadius;
        }
    };
int main() {
    Triangle triangle(3.0, 4.0, 5.0);
    assert(triangle.perimeter() == 12.0);
    assert(triangle.area() == 6.0);
    std::cout << "Triangle test passed" << std::endl;

    Square square(5.0);
    assert(square.perimeter() == 20.0);
    assert(square.area() == 25.0);
    std::cout << "Square test passed" << std::endl;

    Circle circle(3.0);
    assert(std::abs(circle.perimeter() - 18.8496) <= 1e-3);
    assert(std::abs(circle.area() - 28.2743) <= 1e-3);
    std::cout << "Circle test passed" << std::endl;
    
    std::vector<Shape*> shapes;
    
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));
    shapes.push_back(new Square(5.0));
    shapes.push_back(new Circle(3.0));
    
    std::cout << "Testing through std::vector<Shape*>:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "Figure " << i + 1 << ": perimeter = " 
                  << shapes[i]->perimeter() << ", area = " 
                  << shapes[i]->area() << std::endl;
    }
    
    for (size_t i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
    shapes.clear();
    
    std::cout << "All tests are passed successfully" << std::endl;
    
    return 0;
}