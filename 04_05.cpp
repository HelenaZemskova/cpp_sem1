#include <cassert>
#include <climits>
#include <iostream>

template<int N>
struct Fibonacci;

// Базовый шаблон
template<int N>
struct Fibonacci
{
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
    
    // Проверяем, что Fibonacci<N-1>::value + Fibonacci<N-2>::value не вызовет переполнение
    static_assert(Fibonacci<N - 1>::value <= INT_MAX - Fibonacci<N - 2>::value,
                  "Integer overflow detected in Fibonacci calculation");
};

template<>
struct Fibonacci<0>
{
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1>
{
    static constexpr int value = 1;
};

template<int N>
constexpr int Fibonacci_v = Fibonacci<N>::value;

static_assert(Fibonacci_v<0> == 0, "F(0) should be 0");
static_assert(Fibonacci_v<1> == 1, "F(1) should be 1");
static_assert(Fibonacci_v<2> == 1, "F(2) should be 1");
static_assert(Fibonacci_v<3> == 2, "F(3) should be 2");
static_assert(Fibonacci_v<4> == 3, "F(4) should be 3");
static_assert(Fibonacci_v<5> == 5, "F(5) should be 5");
static_assert(Fibonacci_v<6> == 8, "F(6) should be 8");
static_assert(Fibonacci_v<7> == 13, "F(7) should be 13");
static_assert(Fibonacci_v<8> == 21, "F(8) should be 21");
static_assert(Fibonacci_v<9> == 34, "F(9) should be 34");
static_assert(Fibonacci_v<10> == 55, "F(10) should be 55");
static_assert(Fibonacci_v<15> == 610, "F(15) should be 610");
static_assert(Fibonacci_v<20> == 6765, "F(20) should be 6765");
static_assert(Fibonacci_v<25> == 75025, "F(25) should be 75025");
static_assert(Fibonacci_v<30> == 832040, "F(30) should be 832040");

// F(46) = 1836311903 - последнее число Фибоначчи, помещающееся в int
static_assert(Fibonacci_v<46> == 1836311903, "F(46) should be 1836311903");

// F(47) вызовет переполнение и ошибку компиляции из-за static_assert
//static_assert(Fibonacci_v<47> == 2971215073);


int main()
{
    std::cout << "Fibonacci numbers computed at compile time:" << std::endl;
    std::cout << "F(0) = " << Fibonacci_v<0> << std::endl;
    std::cout << "F(1) = " << Fibonacci_v<1> << std::endl;
    std::cout << "F(2) = " << Fibonacci_v<2> << std::endl;
    std::cout << "F(5) = " << Fibonacci_v<5> << std::endl;
    std::cout << "F(10) = " << Fibonacci_v<10> << std::endl;
    std::cout << "F(15) = " << Fibonacci_v<15> << std::endl;
    std::cout << "F(20) = " << Fibonacci_v<20> << std::endl;
    std::cout << "F(25) = " << Fibonacci_v<25> << std::endl;
    std::cout << "F(30) = " << Fibonacci_v<30> << std::endl;
    std::cout << "F(40) = " << Fibonacci_v<40> << std::endl;
    std::cout << "F(46) = " << Fibonacci_v<46> << std::endl;

    assert(Fibonacci<0>::value == 0);
    assert(Fibonacci<1>::value == 1);
    assert(Fibonacci<10>::value == 55);
    assert(Fibonacci<20>::value == 6765);
    assert(Fibonacci<30>::value == 832040);
    assert(Fibonacci<46>::value == 1836311903);

    std::cout << "\nAll tests passed successfully!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////

