#include <array>
#include <iostream>

// consteval функция для вычисления числа пи через ряд Лейбница

consteval double compute_pi(double epsilon)
{
    double pi_sum = 0.0;
    double pi_term = 1.0;
    double denominator = 1.0;
    double sign = 1.0;

    while (pi_term >= epsilon || -pi_term >= epsilon)
    {
        pi_sum += pi_term;
        sign = -sign;
        denominator += 2.0;
        pi_term = sign / denominator;
    }
    
    return 4.0 * pi_sum;
}

// consteval функция для вычисления числа е через ряд Маклорена
consteval double compute_e(double epsilon)
{
    double e_sum = 0.0;
    double e_term = 1.0;
    int k = 1;
    
    while (e_term >= epsilon)
    {
        e_sum += e_term;
        e_term = e_term / k;
        k++;
    }
    
    return e_sum;
}

constexpr std::array<double, 5> epsilons = {0.1, 0.01, 0.001, 0.0001, 0.00001};

// Вычисления на этапе компиляции
constexpr double pi_01    = compute_pi(0.1);
constexpr double pi_001   = compute_pi(0.01);
constexpr double pi_0001  = compute_pi(0.001);
constexpr double pi_00001 = compute_pi(0.0001);

constexpr double e_01     = compute_e(0.1);
constexpr double e_001    = compute_e(0.01);
constexpr double e_0001   = compute_e(0.001);
constexpr double e_00001  = compute_e(0.0001);


// При больших epsilon точность ниже, поэтому диапазоны шире
static_assert(pi_01 > 3.0 && pi_01 < 3.5, "Pi with epsilon=0.1 is incorrect");
static_assert(pi_001 > 3.1 && pi_001 < 3.2, "Pi with epsilon=0.01 is incorrect");
static_assert(pi_0001 > 3.13 && pi_0001 < 3.15, "Pi with epsilon=0.001 is incorrect");
static_assert(pi_00001 > 3.141 && pi_00001 < 3.143, "Pi with epsilon=0.0001 is incorrect");

static_assert(e_01 > 2.6 && e_01 < 2.8, "E with epsilon=0.1 is incorrect");
static_assert(e_001 > 2.70 && e_001 < 2.72, "E with epsilon=0.01 is incorrect");
static_assert(e_0001 > 2.717 && e_0001 < 2.719, "E with epsilon=0.001 is incorrect");
static_assert(e_00001 > 2.7182 && e_00001 < 2.7184, "E with epsilon=0.0001 is incorrect");

int main()
{
    std::cout << "Numbers computed at compile time:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Values of pi with different epsilon:" << std::endl;
    std::cout << "  epsilon = " << epsilons[0] << " : pi = " << pi_01 << std::endl;
    std::cout << "  epsilon = " << epsilons[1] << " : pi = " << pi_001 << std::endl;
    std::cout << "  epsilon = " << epsilons[2] << " : pi = " << pi_0001 << std::endl;
    std::cout << "  epsilon = " << epsilons[3] << " : pi = " << pi_00001 << std::endl;
    std::cout << std::endl;
    
    std::cout << "Values of e with different epsilon:" << std::endl;
    std::cout << "  epsilon = " << epsilons[0] << " : e = " << e_01 << std::endl;
    std::cout << "  epsilon = " << epsilons[1] << " : e = " << e_001 << std::endl;
    std::cout << "  epsilon = " << epsilons[2] << " : e = " << e_0001 << std::endl;
    std::cout << "  epsilon = " << epsilons[3] << " : e = " << e_00001 << std::endl;
    std::cout << std::endl;
    
    std::cout << "Reference values:" << std::endl;
    std::cout << "  Pi ≈ 3.14159265359" << std::endl;
    std::cout << "  e ≈ 2.71828182846" << std::endl;
    std::cout << std::endl;
    
    std::cout << "All tests passed successfully!" << std::endl;
}

