#include <cassert>
#include <iostream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////////////

template<int N = 0, int D = 1>
struct Ratio
{
	constexpr static auto num = N;
	constexpr static auto den = D;
};

////////////////////////////////////////////////////////////////////////////////////

// Sum с сокращением дроби через std::gcd
template<typename R1, typename R2>
struct Sum
{
	constexpr static auto num_raw = R1::num * R2::den + R2::num * R1::den;
	constexpr static auto den_raw = R1::den * R2::den;
	
	constexpr static auto gcd_val = std::gcd(num_raw, den_raw);
	constexpr static auto num = num_raw / gcd_val;
	constexpr static auto den = den_raw / gcd_val;
	
	using type = Ratio<num, den>;
};

template<typename R1, typename R2>
using sum = typename Sum<R1, R2>::type;

////////////////////////////////////////////////////////////////////////////////////

// Sub - вычитание дробей с сокращением через std::gcd
template<typename R1, typename R2>
struct Sub
{
	constexpr static auto num_raw = R1::num * R2::den - R2::num * R1::den;
	constexpr static auto den_raw = R1::den * R2::den;
	
	constexpr static auto gcd_val = std::gcd(num_raw, den_raw);
	constexpr static auto num = num_raw / gcd_val;
	constexpr static auto den = den_raw / gcd_val;
	
	using type = Ratio<num, den>;
};

template<typename R1, typename R2>
using sub = typename Sub<R1, R2>::type;

////////////////////////////////////////////////////////////////////////////////////

// Mul - умножение дробей с сокращением через std::gcd
template<typename R1, typename R2>
struct Mul
{
	constexpr static auto num_raw = R1::num * R2::num;
	constexpr static auto den_raw = R1::den * R2::den;
	
	constexpr static auto gcd_val = std::gcd(num_raw, den_raw);
	constexpr static auto num = num_raw / gcd_val;
	constexpr static auto den = den_raw / gcd_val;
	
	using type = Ratio<num, den>;
};

template<typename R1, typename R2>
using mul = typename Mul<R1, R2>::type;

////////////////////////////////////////////////////////////////////////////////////

// Div - деление дробей через Mul (устранение дублирования)
template<typename R1, typename R2>
struct Div
{
	// Проверка деления на ноль на этапе компиляции
	static_assert(R2::num != 0, "Division by zero in Ratio");
	
	using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
};

template<typename R1, typename R2>
using ratio_div = typename Div<R1, R2>::type;

////////////////////////////////////////////////////////////////////////////////////

template<typename T, typename R = Ratio<1>>
struct Duration 
{
	T x = T();
	
	constexpr Duration() = default;
	constexpr explicit Duration(T value) : x(value) {}
};

////////////////////////////////////////////////////////////////////////////////////

// Оператор сложения интервалов
template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(Duration<T1, R1> const & lhs, Duration<T2, R2> const & rhs)
{
	using ratio_t = Ratio<1, sum<R1, R2>::den>;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +
		rhs.x * ratio_t::den / R2::den * R2::num
	);

	return Duration<decltype(x), ratio_t>(x);
}

////////////////////////////////////////////////////////////////////////////////////

// Унарный минус для Duration
template<typename T, typename R>
constexpr auto operator-(Duration<T, R> const & duration)
{
	return Duration<T, R>(-duration.x);
}

////////////////////////////////////////////////////////////////////////////////////

// Оператор вычитания интервалов через оператор сложения
template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(Duration<T1, R1> const & lhs, Duration<T2, R2> const & rhs)
{
	return lhs + (-rhs);
}

////////////////////////////////////////////////////////////////////////////////////

static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::num == 5, "Sum numerator incorrect");
static_assert(sum<Ratio<1, 2>, Ratio<1, 3>>::den == 6, "Sum denominator incorrect");
static_assert(sum<Ratio<2, 4>, Ratio<1, 4>>::num == 3, "Sum simplification incorrect");
static_assert(sum<Ratio<2, 4>, Ratio<1, 4>>::den == 4, "Sum simplification incorrect");

static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::num == 1, "Sub numerator incorrect");
static_assert(sub<Ratio<1, 2>, Ratio<1, 3>>::den == 6, "Sub denominator incorrect");
static_assert(sub<Ratio<3, 4>, Ratio<1, 4>>::num == 1, "Sub simplification incorrect");
static_assert(sub<Ratio<3, 4>, Ratio<1, 4>>::den == 2, "Sub simplification incorrect");

static_assert(mul<Ratio<2, 3>, Ratio<3, 4>>::num == 1, "Mul numerator incorrect");
static_assert(mul<Ratio<2, 3>, Ratio<3, 4>>::den == 2, "Mul denominator incorrect");
static_assert(mul<Ratio<4, 6>, Ratio<3, 8>>::num == 1, "Mul simplification incorrect");
static_assert(mul<Ratio<4, 6>, Ratio<3, 8>>::den == 4, "Mul simplification incorrect");

static_assert(ratio_div<Ratio<1, 2>, Ratio<1, 3>>::num == 3, "Div numerator incorrect");
static_assert(ratio_div<Ratio<1, 2>, Ratio<1, 3>>::den == 2, "Div denominator incorrect");
static_assert(ratio_div<Ratio<2, 3>, Ratio<4, 6>>::num == 1, "Div simplification incorrect");
static_assert(ratio_div<Ratio<2, 3>, Ratio<4, 6>>::den == 1, "Div simplification incorrect");

// Тест деления на ноль
//static_assert(ratio_div<Ratio<1, 2>, Ratio<0, 1>>::num == 0);

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 1, y = 2;

	Duration<int, Ratio<1, 2>> duration_1(x);
	Duration<int, Ratio<1, 3>> duration_2(y);
	Duration<int, Ratio<1, 6>> duration_3 = duration_1 + duration_2;
	assert(duration_3.x == 7);

	Duration<int, Ratio<1, 2>> duration_4(10);
	Duration<int, Ratio<1, 3>> duration_5(6);
	auto duration_6 = duration_4 - duration_5;
	assert(duration_6.x == 18);

	Duration<int, Ratio<1, 4>> duration_7(8);
	Duration<int, Ratio<1, 4>> duration_8(4);
	auto duration_9 = duration_7 - duration_8;
	assert(duration_9.x == 2);

	std::cout << "All tests passed successfully!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////

