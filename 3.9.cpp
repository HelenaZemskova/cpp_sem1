#include <iostream>
#include <array>
#include <cstdint>
#include <sstream>
#include <cassert>

class IPv4 {
private:
    std::array<std::uint8_t, 4> data;

public:
    IPv4() : data{0, 0, 0, 0} {}
    
    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) 
        : data{a, b, c, d} {}
    
    IPv4& operator++() {
        for (int i = 3; i >= 0; --i) {
            if (data[i] < 255) {
                ++data[i];
                break;
            } else {
                data[i] = 0;
            }
        }
        return *this;
    }
    
    IPv4 operator++(int) {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }
    
    IPv4& operator--() {
        for (int i = 3; i >= 0; --i) {
            if (data[i] > 0) {
                --data[i];
                break;
            } else {
                data[i] = 255;
            }
        }
        return *this;
    }
    
    IPv4 operator--(int) {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }
    
    friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
        return lhs.data == rhs.data;
    }
    
    friend bool operator!=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs == rhs);
    }
    
    friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
        return lhs.data < rhs.data;
    }
    
    friend bool operator>(const IPv4& lhs, const IPv4& rhs) {
        return rhs < lhs;
    }
    
    friend bool operator<=(const IPv4& lhs, const IPv4& rhs) {
        return !(rhs < lhs);
    }
    
    friend bool operator>=(const IPv4& lhs, const IPv4& rhs) {
        return !(lhs < rhs);
    }
    
    friend std::stringstream& operator<<(std::stringstream& ss, const IPv4& ip) {
        ss << static_cast<int>(ip.data[0]) << '.' 
           << static_cast<int>(ip.data[1]) << '.' 
           << static_cast<int>(ip.data[2]) << '.' 
           << static_cast<int>(ip.data[3]);
        return ss;
    }
    
    friend std::stringstream& operator>>(std::stringstream& ss, IPv4& ip) {
        int a{}, b{}, c{}, d{};
        char dot1{}, dot2{}, dot3{};
        
        ss >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d;
        
        if (dot1 != '.' || dot2 != '.' || dot3 != '.' ||
            a < 0 || a > 255 || b < 0 || b > 255 || 
            c < 0 || c > 255 || d < 0 || d > 255) {
            ss.setstate(std::ios::failbit);
            return ss;
        }
        
        ip.data[0] = static_cast<std::uint8_t>(a);
        ip.data[1] = static_cast<std::uint8_t>(b);
        ip.data[2] = static_cast<std::uint8_t>(c);
        ip.data[3] = static_cast<std::uint8_t>(d);
        
        return ss;
    }
};

int main() {
    // конструкторы
    IPv4 ip1;
    IPv4 ip2(192, 168, 1, 1);
    IPv4 ip3(255, 255, 255, 255);
    
    // вывод через std::stringstream
    std::stringstream ss_out;
    ss_out << ip1;
    assert(ss_out.str() == "0.0.0.0");
    
    ss_out.str("");
    ss_out << ip2;
    assert(ss_out.str() == "192.168.1.1");
    
    ss_out.str("");
    ss_out << ip3;
    assert(ss_out.str() == "255.255.255.255");
    std::cout << "Output test passed" << std::endl;
    
    // ввод через std::stringstream
    std::stringstream ss_in;
    ss_in.str("192.168.1.1");
    IPv4 ip4;
    ss_in >> ip4;
    assert(ip4 == IPv4(192, 168, 1, 1));
    
    ss_in.clear();
    ss_in.str("10.0.0.1");
    ss_in >> ip4;
    assert(ip4 == IPv4(10, 0, 0, 1));
    std::cout << "Input test passed" << std::endl;
    
    //  инкремент
    IPv4 ip5(192, 168, 1, 254);
    assert(++ip5 == IPv4(192, 168, 1, 255));
    assert(ip5++ == IPv4(192, 168, 1, 255));
    assert(ip5 == IPv4(192, 168, 2, 0));
    std::cout << "Increment test passed" << std::endl;
    
    //  декремент
    IPv4 ip6(192, 168, 2, 1);
    assert(--ip6 == IPv4(192, 168, 2, 0));
    assert(ip6-- == IPv4(192, 168, 2, 0));
    assert(ip6 == IPv4(192, 168, 1, 255));
    std::cout << "Decrement test passed" << std::endl;
    
    //  сравнение
    IPv4 ip7(10, 0, 0, 1);
    IPv4 ip8(10, 0, 0, 2);
    assert((ip7 == ip8) == false);
    assert(ip7 < ip8);
    assert((ip7 > ip8) == false);
    std::cout << "Comparison test passed" << std::endl;
    
    //  граничные случаи
    IPv4 ip9(255, 255, 255, 255);
    ++ip9;
    assert(ip9 == IPv4(0, 0, 0, 0));
    
    IPv4 ip10(0, 0, 0, 0);
    --ip10;
    assert(ip10 == IPv4(255, 255, 255, 255));
    std::cout << "Edge cases test passed" << std::endl;
    
    return 0;
}