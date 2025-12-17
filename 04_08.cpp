#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////

// Базовый шаблон - пустой кортеж
template<typename... Ts>
class Tuple
{
public:
	constexpr std::size_t size() const
	{
		return 0;
	}
};

////////////////////////////////////////////////////////////////////////////////////

// Специализация для непустого кортежа
template<typename T, typename... Ts>
class Tuple<T, Ts...>
{
public:

	constexpr Tuple(T && x, Ts && ... xs)
	:
		m_head(std::forward<T>(x)),
		m_tail(std::forward<Ts>(xs)...)
	{}

	////////////////////////////////////////////////////////////////////////////////////

	template<std::size_t I>
	constexpr auto get() const
	{
		if constexpr (I > 0)
		{
			return m_tail.template get<I - 1>();
		}
		else
		{
			return m_head;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////

	constexpr std::size_t size() const
	{
		return 1 + sizeof...(Ts);
	}

private:

	T m_head;
	Tuple<Ts...> m_tail;
};

////////////////////////////////////////////////////////////////////////////////////

constexpr Tuple<int, double, int> tuple1(10, 3.14, 42);

static_assert(tuple1.size() == 3, "Size should be 3");
static_assert(tuple1.get<0>() == 10, "First element should be 10");
static_assert(tuple1.get<1>() == 3.14, "Second element should be 3.14");
static_assert(tuple1.get<2>() == 42, "Third element should be 42");

constexpr Tuple<int> tuple2(100);

static_assert(tuple2.size() == 1, "Size should be 1");
static_assert(tuple2.get<0>() == 100, "Element should be 100");

constexpr Tuple<int, int> tuple3(5, 7);

static_assert(tuple3.size() == 2, "Size should be 2");
static_assert(tuple3.get<0>() == 5, "First element should be 5");
static_assert(tuple3.get<1>() == 7, "Second element should be 7");

constexpr Tuple<int, int, int, int, int> tuple4(1, 2, 3, 4, 5);

static_assert(tuple4.size() == 5, "Size should be 5");
static_assert(tuple4.get<0>() == 1, "First element should be 1");
static_assert(tuple4.get<1>() == 2, "Second element should be 2");
static_assert(tuple4.get<2>() == 3, "Third element should be 3");
static_assert(tuple4.get<3>() == 4, "Fourth element should be 4");
static_assert(tuple4.get<4>() == 5, "Fifth element should be 5");

constexpr Tuple<> tuple5;

static_assert(tuple5.size() == 0, "Empty tuple size should be 0");

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Tuple<int, double, std::string> tuple(1, 2.0, "aaaaa");

	assert(tuple.get<0>() == 1);
	assert(tuple.get<1>() == 2.0);
	assert(tuple.get<2>() == "aaaaa");
	assert(tuple.size() == 3);

	Tuple<int> single(42);
	assert(single.get<0>() == 42);
	assert(single.size() == 1);

	Tuple<> empty;
	assert(empty.size() == 0);

	std::cout << "All tests passed successfully!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////

