#include <iostream>
#include <string>

class Entity_v1 {
public:
    virtual void test(const std::string& msg) {
        std::cout << "Entity_v1::test: " << msg << std::endl;
    }
    
    virtual ~Entity_v1() = default;
};

class Entity_v2 {
public:
    virtual void test(const std::string& msg) {
        std::cout << "Entity_v2::test: " << msg << std::endl;
    }
    
    virtual ~Entity_v2() = default;
};

class Adapter_v1 : public Entity_v1 {
public:
    virtual void test_v1(const std::string& msg) = 0;
    
private:
    void test(const std::string& msg) override final {
        test_v1(msg);
    }
};

class Adapter_v2 : public Entity_v2 {
public:
    virtual void test_v2(const std::string& msg) = 0;
    
private:
    void test(const std::string& msg) override final {
        test_v2(msg);
    }
};

class Client : public Adapter_v1, public Adapter_v2 {
public:
    void test_v1(const std::string& msg) override {
        std::cout << "Client::test_v1: " << msg << std::endl;
    }
    
    void test_v2(const std::string& msg) override {
        std::cout << "Client::test_v2: " << msg << std::endl;
    }
};

int main() {
    Client client;
    
    Entity_v1* ptr1 = &client;
    ptr1->test("Message from Entity_v1");
    
    Entity_v2* ptr2 = &client;
    ptr2->test("Message from Entity_v2");
    
    return 0;
}