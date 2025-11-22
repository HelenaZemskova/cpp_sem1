#include <iostream>
#include <numbers>
#include <cmath>
#include <cassert>

class Triangle {
private:
    double side1, side2, side3;

public:
    Triangle(double first, double second, double third) 
        : side1(first), side2(second), side3(third) {}

    double area() const {
        double semiPerimeter = perimeter() / 2.0;
        double product = semiPerimeter * (semiPerimeter - side1) * 
                        (semiPerimeter - side2) * (semiPerimeter - side3);
        return std::sqrt(product);
    }

    double perimeter() const {
        return side1 + side2 + side3;
    }
};

class Square {
private:
    double sideLength;

public:
    Square(double length) : sideLength(length) {}

    double area() const {
        return sideLength * sideLength;
    }

    double perimeter() const {
        return 4.0 * sideLength;
    }
};

class Circle {
    private:
        double circleRadius;
    
    public:
        Circle(double r) : circleRadius(r) {}
    
        double area() const {
            return std::numbers::pi * circleRadius * circleRadius;
        }
    
        double perimeter() const {
            return 2.0 * std::numbers::pi * circleRadius;
        }
    };

int main() {
    Triangle triangle(3.0, 4.0, 5.0);
    assert(triangle.perimeter() == 12.0);
    assert(triangle.area() == 6.0);
    std::cout << "Triangle test is passed" << std::endl;

    Square square(5.0);
    assert(square.perimeter() == 20.0);
    assert(square.area() == 25.0);
    std::cout << "Square test is passed" << std::endl;

    Circle circle(3.0);
    assert(std::abs(circle.perimeter() - 18.8496) <= 1e-3);
    assert(std::abs(circle.area() - 28.2743) <= 1e-3);
    std::cout << "Circle test is passed" << std::endl;

    return 0;
}