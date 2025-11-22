#include <iostream>
#include <numeric>
#include <cstdlib>
#include <random>
#include <chrono>
#include <cassert>

int findGCDRecursive(int first, int second) {
    if (second == 0) return std::abs(first);
    return findGCDRecursive(second, first % second);
}

int findGCDIterative(int first, int second) {
    first = std::abs(first);
    second = std::abs(second);
    while (second != 0) {
        int remainder = second;
        second = first % second;
        first = remainder;
    }
    return first;
}

int findLCM(int first, int second) {
    if (first == 0 || second == 0) return 0;
    int gcd_result = findGCDIterative(first, second);
    return std::abs(first * second) / gcd_result;
}

int main() {
    auto time_point = std::chrono::steady_clock::now();
    unsigned seed_value = time_point.time_since_epoch().count();
    std::mt19937 random_generator(seed_value);
    std::uniform_int_distribution<int> number_range(1, 1000);
    
    int num1 = number_range(random_generator);
    int num2 = number_range(random_generator);
    
    std::cout << "Test values: " << num1 << " & " << num2 << std::endl;
    
    int gcd_recursive_result = findGCDRecursive(num1, num2);
    int gcd_iterative_result = findGCDIterative(num1, num2);
    int gcd_standard = std::gcd(num1, num2);
    
    int lcm_custom = findLCM(num1, num2);
    int lcm_standard = std::lcm(num1, num2);
    
    assert(gcd_recursive_result == gcd_standard);
    assert(gcd_iterative_result == gcd_standard);
    assert(lcm_custom == lcm_standard);
    
    std::cout << "Calculation results:" << std::endl;
    std::cout << "GCD = " << gcd_recursive_result << std::endl;
    std::cout << "LCM = " << lcm_custom << std::endl;
    
    return 0;
}