import Rational;

#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <compare>

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

int main()
{
	using namespace rational;
	
	Rational x = 1, y(2, 1);

	assert(equal(static_cast<double>(x), 1));

	assert((x += y) == Rational(+3, 1));
	assert((x -= y) == Rational(+1, 1));
	assert((x *= y) == Rational(+2, 1));
	assert((x /= y) == Rational(+1, 1));

	assert((x++) == Rational(+1, 1));
	assert((x--) == Rational(+2, 1));
	assert((++y) == Rational(+3, 1));
	assert((--y) == Rational(+2, 1));

	[[maybe_unused]] auto z = 0;

	assert((x + y) == Rational(+3, 1));
	assert((x - y) == Rational(-1, 1));
	assert((x * y) == Rational(+2, 1));
	assert((x / y) == Rational(+1, 2));

	assert((x += 1) == Rational(+2, 1));
	assert((x + 1) == Rational(+3, 1));
	assert((1 + y) == Rational(+3, 1));
	assert((1 + 1) == Rational(+2, 1));

	assert((x <=> y) == std::strong_ordering::equal);
	assert((x <=> Rational(1, 1)) == std::strong_ordering::greater);
	assert((Rational(1, 2) <=> x) == std::strong_ordering::less);

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

	std::stringstream stream_1("1/2");
	std::stringstream stream_2;

	stream_1 >> x;
	stream_2 << x;

	assert(stream_2.str() == stream_1.str());

	std::cout << "All Rational module tests passed successfully!" << std::endl;

	return 0;
}
