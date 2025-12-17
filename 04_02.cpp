#include <cassert>
#include <cmath>
#include <iostream>

// базовый случай
template<typename T>
T maximum(T value)
{
    return value;
}

// рекурсивный случай
template<typename T, typename... Args>
T maximum(T first, Args... args)
{
    T rest = maximum(args...);
    return (first > rest) ? first : rest;
}

// базовый случай
template<typename T>
T minimum(T value)
{
    return value;
}

// рекурсивный случай
template<typename T, typename... Args>
T minimum(T first, Args... args)
{
    T rest = minimum(args...);
    return (first < rest) ? first : rest;
}

// Сумма через свертку
template<typename... Args>
double sum(Args... args)
{
    return (args + ...);
}

// Среднее арифметическое через свертку
template<typename... Args>
double average(Args... args)
{
    return sum(args...) / sizeof...(args);
}

int main()
{
    assert(maximum(3.5) == 3.5);
    assert(maximum(3.5, 7.2) == 7.2);
    assert(maximum(3.5, 7.2, 1.8, 9.4, 2.1) == 9.4);
    assert(maximum(-5.0, -2.0, -10.0) == -2.0);

    assert(minimum(3.5) == 3.5);
    assert(minimum(3.5, 7.2) == 3.5);
    assert(minimum(3.5, 7.2, 1.8, 9.4, 2.1) == 1.8);
    assert(minimum(-5.0, -2.0, -10.0) == -10.0);

    assert(sum(5.0) == 5.0);
    assert(sum(2.5, 3.5) == 6.0);
    assert(sum(1.0, 2.0, 3.0, 4.0) == 10.0);
    assert(std::abs(sum(0.1, 0.2, 0.3) - 0.6) < 1e-9);

    assert(average(5.0) == 5.0);
    assert(average(2.0, 4.0) == 3.0);
    assert(average(1.0, 2.0, 3.0, 4.0, 5.0) == 3.0);
    assert(std::abs(average(2.5, 3.5, 4.0) - 3.333333333) < 1e-6);

    double max_val = maximum(1.5, 8.3, 3.7, 9.2, 4.1);
    double min_val = minimum(1.5, 8.3, 3.7, 9.2, 4.1);
    double sum_val = sum(1.5, 8.3, 3.7, 9.2, 4.1);
    double avg_val = average(1.5, 8.3, 3.7, 9.2, 4.1);

    assert(max_val == 9.2);
    assert(min_val == 1.5);
    assert(std::abs(sum_val - 26.8) < 1e-9);
    assert(std::abs(avg_val - 5.36) < 1e-9);

    std::cout << "All tests passed successfully!" << std::endl;
}

