#include <iostream>
#include <cassert>

class Entity {
private:
    static void test_v1(int parameter) {
        std::cout << "Access to test_v1 obtained, value = " << parameter << std::endl;
    }
    
    static void test_v2() {
        std::cout << "Access to test_v2 obtained" << std::endl;
    }

    friend class Attorney_v1;
    friend class Attorney_v2;
};

class Attorney_v1 {
private:
    static void invoke_test_v1(int value) { 
        Entity::test_v1(value); 
    }
    friend class Tester_v1;
};

class Attorney_v2 {
private:
    static void invoke_test_v2() { 
        Entity::test_v2(); 
    }
    friend class Tester_v2;
};

class Tester_v1 {
public:
    static void runTest(int testValue) {
        Attorney_v1::invoke_test_v1(testValue);
    }
};

class Tester_v2 {
public:
    static void runTest() {
        Attorney_v2::invoke_test_v2();
    }
};

int main() {
    Tester_v1::runTest(42);
    
    Tester_v2::runTest();
    
    std::cout << "All tests are passed" << std::endl;
    
    return 0;
}