#include "rational.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

// Вспомогательная функция для сравнения double
bool equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

int main()
{
	std::cout << "RATIONAL CLASS TESTS\n\n";

	std::cout << "Test 1: Basic operations\n";
	Rational x = 1, y(2, 1);

	assert(equal(static_cast<double>(x), 1));
	std::cout << "  Creation and cast to double: OK\n";

	std::cout << "\nTest 2: Assignment operators\n";
	assert((x += y) == Rational(+3, 1));
	assert((x -= y) == Rational(+1, 1));
	assert((x *= y) == Rational(+2, 1));
	assert((x /= y) == Rational(+1, 1));
	std::cout << "  +=, -=, *=, /=: OK\n";

	std::cout << "\nTest 3: Increment/Decrement\n";
	assert((x++) == Rational(+1, 1));
	assert((x--) == Rational(+2, 1));
	assert((++y) == Rational(+3, 1));
	assert((--y) == Rational(+2, 1));
	std::cout << "  ++, --: OK\n";

	std::cout << "\nTest 4: Binary operators\n";
	assert((x + y) == Rational(+3, 1));
	assert((x - y) == Rational(-1, 1));
	assert((x * y) == Rational(+2, 1));
	assert((x / y) == Rational(+1, 2));
	std::cout << "  +, -, *, /: OK\n";

	std::cout << "\nTest 5: Mixed operations\n";
	assert((x += 1) == Rational(+2, 1));
	assert((x + 1) == Rational(+3, 1));
	assert((1 + y) == Rational(+3, 1));
	assert((1 + 1) == Rational(+2, 1));
	std::cout << "  Mixed with int: OK\n";

	std::cout << "\nTest 6: Three-way comparison\n";
	assert((x <=> y) == std::strong_ordering::equal);
	assert((x <=> Rational(1, 1)) == std::strong_ordering::greater);
	assert((Rational(1, 2) <=> x) == std::strong_ordering::less);
	std::cout << "  operator<=>: OK\n";

	std::cout << "\nTest 7: Comparison operators\n";
	assert((x < y) == false);
	assert((x > y) == false);
	assert((x <= y) == true);
	assert((x >= y) == true);
	assert((x == y) == true);
	assert((x != y) == false);

	assert(Rational(1, 2) < Rational(2, 3));
	assert(Rational(3, 4) > Rational(1, 2));
	assert(Rational(2, 4) == Rational(1, 2));
	assert(Rational(1, 3) != Rational(1, 2));
	std::cout << "  <, >, <=, >=, ==, !=: OK\n";

	std::cout << "\nTest 8: Input/Output\n";
	std::stringstream stream_1("1/2");
	std::stringstream stream_2;
	
	stream_1 >> x;
	stream_2 << x;

	assert(stream_2.str() == stream_1.str());
	std::cout << "  operator>> and operator<<: OK\n";

	std::cout << "\nTest 9: Fraction reduction\n";
	Rational r1(4, 8);
	Rational r2(1, 2);
	assert(r1 == r2);
	std::cout << "  4/8 = 1/2: OK\n";

	Rational r3(6, 9);
	Rational r4(2, 3);
	assert(r3 == r4);
	std::cout << "  6/9 = 2/3: OK\n";

	std::cout << "\nTest 10: Negative fractions\n";
	Rational r5(-1, 2);
	Rational r6(1, -2);
	assert(r5 == r6);
	std::cout << "  -1/2 = 1/-2: OK\n";

	std::cout << "\nALL TESTS PASSED!\n";

	return 0;
}

