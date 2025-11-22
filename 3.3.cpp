#include <iostream>
#include <cassert>

class List {
private:
    struct Node {
        int value;
        Node* next;
        
        Node(int val) : value(val), next(nullptr) {}
    };
    
    Node* headPtr;
    Node* tailPtr;

public:
    List() : headPtr(nullptr), tailPtr(nullptr) {}
    
    bool empty() const {
        return headPtr == nullptr;
    }
    
    void show() const {
        Node* iterator = headPtr;
        while (iterator != nullptr) {
            std::cout << iterator->value << " ";
            iterator = iterator->next;
        }
        std::cout << std::endl;
    }

    void push_front(int value) {
        Node* newElement = new Node(value);
        if (!empty()) {
            newElement->next = headPtr;
            headPtr = newElement;
        } else {
            headPtr = newElement;
            tailPtr = newElement;
        }
    }

    void push_back(int value) {
        Node* newElement = new Node(value);
        if (!empty()) {
            tailPtr->next = newElement;
            tailPtr = newElement;
        } else {
            headPtr = newElement;
            tailPtr = newElement;
        }
    }

    void pop_front() {
        if (empty()) return;
        Node* nextElement = headPtr->next;
        delete headPtr;
        headPtr = nextElement;
        if (headPtr == nullptr) {
            tailPtr = nullptr;
        }
    }

    void pop_back() {
        if (empty()) return;
        if (tailPtr == headPtr) {
            delete headPtr;
            tailPtr = nullptr;
            headPtr = nullptr;
            return;
        }
        Node* iterator = headPtr;
        while (iterator->next != tailPtr) {
            iterator = iterator->next;
        }
        delete tailPtr;
        tailPtr = iterator;
        iterator->next = nullptr;
    }

    int get() const {
        if (empty()) return -1;
        Node* fastPtr = headPtr;
        Node* slowPtr = headPtr;
        bool moveSlow = false;
        while (fastPtr->next != nullptr) {
            if (moveSlow) {
                slowPtr = slowPtr->next;
            }
            moveSlow = !moveSlow;
            fastPtr = fastPtr->next;
        }
        return slowPtr->value;
    }
    
    ~List() {
        while (!empty()) {
            pop_front();
        }
    }
};

int main() {
    List testList;
    assert(testList.empty());
    testList.push_back(1);
    assert(!testList.empty());
    std::cout << "empty() test is passed" << std::endl;
    testList.pop_back();
    
    testList.push_back(1);
    testList.push_back(2);
    testList.push_back(3);
    std::cout << "After push_back: ";
    testList.show();
    
    testList.push_front(0);
    std::cout << "After push_front: ";
    testList.show();
    assert(testList.get() == 1);
    std::cout << "The middle element for size 5 is correct" << std::endl;
    
    testList.pop_front();
    std::cout << "After pop_front: ";
    testList.show();
    assert(testList.get() == 2);
    std::cout << "The middle element for size 3 is correct" << std::endl;
    
    testList.pop_back();
    std::cout << "After pop_back: ";
    testList.show();
    assert(testList.get() == 1);
    std::cout << "The middle element for size 2 is correct" << std::endl;

    return 0;
}