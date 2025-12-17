#include <cassert>
#include <cstddef>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////
// is_class - проверка, является ли тип классом
////////////////////////////////////////////////////////////////////////////////////

/*
 * Синтаксис "int T::*" означает "указатель на член класса T типа int".
 * Существует только если T - это класс или структура.
 * 
 * Если T это примитивный тип (int, double и т.д.) или enum, 
 * то синтаксис "int T::*" недопустим - SFINAE отбросит перегрузку.
 * 
 * В соответствии с этим, можем определить, является ли тип классом:
 * Если T класс, то "int T::*" валиден и выбирается первая перегрузка (char)
 * Если T не класс, то SFINAE отбрасывает первую перегрузку и выбирается вторая (long)
 */

template<typename T>
class is_class
{
	template<typename U>
	static char test(int U::*);  // Работает только для классов/структур
	
	template<typename>
	static long test(...);  // Fallback для всех остальных типов
	
public:
	static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(char);
};

template<typename T>
constexpr bool is_class_v = is_class<T>::value;


template<typename T>
struct add_const
{
	using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct remove_const
{
	using type = T;
};

template<typename T>
struct remove_const<const T>
{
	using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

// conditional - условный выбор типа

template<bool B, typename T, typename F>
struct conditional
{
	using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F>
{
	using type = F;
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template<typename T>
struct remove_reference
{
	using type = T;
};

template<typename T>
struct remove_reference<T&>
{
	using type = T;
};

template<typename T>
struct remove_reference<T&&>
{
	using type = T;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
struct remove_volatile
{
	using type = T;
};

template<typename T>
struct remove_volatile<volatile T>
{
	using type = T;
};

template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template<typename T>
struct remove_cv
{
	using type = typename remove_volatile<typename remove_const<T>::type>::type;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

template<typename T>
struct is_array
{
	static constexpr bool value = false;
};

template<typename T>
struct is_array<T[]>
{
	static constexpr bool value = true;
};

template<typename T, std::size_t N>
struct is_array<T[N]>
{
	static constexpr bool value = true;
};

template<typename T>
constexpr bool is_array_v = is_array<T>::value;

template<typename T>
struct is_function
{
	static constexpr bool value = false;
};

template<typename Ret, typename... Args>
struct is_function<Ret(Args...)>
{
	static constexpr bool value = true;
};

template<typename Ret, typename... Args>
struct is_function<Ret(Args...) const>
{
	static constexpr bool value = true;
};

template<typename T>
constexpr bool is_function_v = is_function<T>::value;

template<typename T>
struct remove_extent
{
	using type = T;
};

template<typename T>
struct remove_extent<T[]>
{
	using type = T;
};

template<typename T, std::size_t N>
struct remove_extent<T[N]>
{
	using type = T;
};

template<typename T>
using remove_extent_t = typename remove_extent<T>::type;

template<typename T>
struct add_pointer
{
	using type = T*;
};

template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

template<typename T>
struct decay
{
private:
	using U = remove_reference_t<T>;
	
public:
	using type = conditional_t<
		is_array_v<U>,
		remove_extent_t<U>*,
		conditional_t<
			is_function_v<U>,
			add_pointer_t<U>,
			remove_cv_t<U>
		>
	>;
};

template<typename T>
using decay_t = typename decay<T>::type;

template<typename T, typename U>
struct is_same
{
	static constexpr bool value = false;
};

template<typename T>
struct is_same<T, T>
{
	static constexpr bool value = true;
};

template<typename T, typename U>
constexpr bool is_same_v = is_same<T, U>::value;

// Тестовые типы

class MyClass {};
struct MyStruct {};
enum MyEnum { A, B, C };
union MyUnion { int i; double d; };


static_assert(is_class_v<MyClass>, "MyClass should be a class");
static_assert(is_class_v<MyStruct>, "MyStruct should be a class");
static_assert(is_class_v<MyUnion>, "MyUnion should be a class");
static_assert(!is_class_v<int>, "int should not be a class");
static_assert(!is_class_v<double>, "double should not be a class");
static_assert(!is_class_v<MyEnum>, "MyEnum should not be a class");
static_assert(!is_class_v<int*>, "int* should not be a class");
static_assert(!is_class_v<int&>, "int& should not be a class");
static_assert(!is_class_v<void>, "void should not be a class");

static_assert(is_same_v<add_const_t<int>, const int>, "add_const should add const");
static_assert(is_same_v<add_const_t<const int>, const int>, "add_const should keep const");
static_assert(is_same_v<add_const_t<int*>, int* const>, "add_const should add const to pointer");

static_assert(is_same_v<remove_const_t<const int>, int>, "remove_const should remove const");
static_assert(is_same_v<remove_const_t<int>, int>, "remove_const should keep non-const");
static_assert(is_same_v<remove_const_t<int* const>, int*>, "remove_const should remove const from const pointer");

static_assert(is_same_v<conditional_t<true, int, double>, int>, "conditional should select first type when true");
static_assert(is_same_v<conditional_t<false, int, double>, double>, "conditional should select second type when false");
static_assert(is_same_v<conditional_t<(2 > 1), char, long>, char>, "conditional should work with expressions");

static_assert(is_same_v<decay_t<int>, int>, "decay of int should be int");
static_assert(is_same_v<decay_t<int&>, int>, "decay of int& should be int");
static_assert(is_same_v<decay_t<int&&>, int>, "decay of int&& should be int");
static_assert(is_same_v<decay_t<const int&>, int>, "decay of const int& should be int");
static_assert(is_same_v<decay_t<int[10]>, int*>, "decay of int[10] should be int*");
static_assert(is_same_v<decay_t<int[]>, int*>, "decay of int[] should be int*");
static_assert(is_same_v<decay_t<const int[10]>, const int*>, "decay of const int[10] should be const int*");

static_assert(is_same_v<remove_reference_t<int&>, int>, "remove_reference should work");
static_assert(is_same_v<remove_cv_t<const volatile int>, int>, "remove_cv should work");
static_assert(is_array_v<int[10]>, "is_array should detect arrays");
static_assert(!is_array_v<int*>, "is_array should not detect pointers");

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "All static assertions passed!" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Type trait results:" << std::endl;
	std::cout << "  is_class<MyClass>: " << is_class_v<MyClass> << std::endl;
	std::cout << "  is_class<int>: " << is_class_v<int> << std::endl;
	std::cout << "  is_array<int[10]>: " << is_array_v<int[10]> << std::endl;
	std::cout << "  is_array<int*>: " << is_array_v<int*> << std::endl;
	std::cout << std::endl;
	
	std::cout << "All tests passed successfully!" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////

