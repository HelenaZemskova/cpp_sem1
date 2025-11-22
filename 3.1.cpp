#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

struct Rectangle {
    int topLeftX, topLeftY, bottomRightX, bottomRightY;

    Rectangle(int x1, int y1, int x2, int y2) 
        : topLeftX(x1), topLeftY(y1), bottomRightX(x2), bottomRightY(y2) {}
};

int calculateIntersectionArea(const std::vector<Rectangle>& rectangles) {
    if (rectangles.empty()) return -1;
    
    int intersectionLeftX = rectangles[0].topLeftX;
    int intersectionTopY = rectangles[0].topLeftY;
    int intersectionRightX = rectangles[0].bottomRightX;
    int intersectionBottomY = rectangles[0].bottomRightY;
    
    for (size_t index = 1; index < rectangles.size(); ++index) {
        intersectionLeftX = std::max(intersectionLeftX, rectangles[index].topLeftX);
        intersectionTopY = std::max(intersectionTopY, rectangles[index].topLeftY);
        intersectionRightX = std::min(intersectionRightX, rectangles[index].bottomRightX);
        intersectionBottomY = std::min(intersectionBottomY, rectangles[index].bottomRightY);
    }
    
    if (intersectionLeftX > intersectionRightX || intersectionTopY > intersectionBottomY) {
        return -1;
    }
    
    if (intersectionLeftX == intersectionRightX || intersectionTopY == intersectionBottomY) {
        return 0;
    }

    int width = intersectionRightX - intersectionLeftX;
    int height = intersectionBottomY - intersectionTopY;
    return width * height;
}

Rectangle computeBoundingBox(const std::vector<Rectangle>& rectangles) {
    if (rectangles.empty()) {
        return Rectangle(0, 0, 0, 0);
    }
    
    int minX = rectangles[0].topLeftX;
    int minY = rectangles[0].topLeftY;
    int maxX = rectangles[0].bottomRightX;
    int maxY = rectangles[0].bottomRightY;
    
    for (size_t idx = 1; idx < rectangles.size(); ++idx) {
        minX = std::min(minX, rectangles[idx].topLeftX);
        minY = std::min(minY, rectangles[idx].topLeftY);
        maxX = std::max(maxX, rectangles[idx].bottomRightX);
        maxY = std::max(maxY, rectangles[idx].bottomRightY);
    }
    
    return Rectangle(minX, minY, maxX, maxY);
}

int main() {
    // Пересекающиеся прямоугольники
    std::vector<Rectangle> testCase1 = {
        Rectangle(0, 0, 10, 10),
        Rectangle(5, 5, 15, 15)
    };
    assert(calculateIntersectionArea(testCase1) == 25);
    
    // Непересекающиеся прямоугольники
    std::vector<Rectangle> testCase2 = {
        Rectangle(0, 0, 10, 10),
        Rectangle(25, 15, 45, 55)
    };
    assert(calculateIntersectionArea(testCase2) == -1);
    
    // Вырожденное пересечение
    std::vector<Rectangle> testCase3 = {
        Rectangle(0, 0, 10, 10),
        Rectangle(5, 10, 45, 55)
    };
    assert(calculateIntersectionArea(testCase3) == 0);
    
    // Наименьший ограничивающий прямоугольник
    Rectangle boundingRect = computeBoundingBox(testCase1);
    assert(boundingRect.topLeftX == 0 && boundingRect.topLeftY == 0);
    assert(boundingRect.bottomRightX == 15 && boundingRect.bottomRightY == 15);
    
    std::cout << "All tests passed" << std::endl;
    
    return 0;
}


