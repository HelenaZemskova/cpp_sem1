#include <cassert>
#include <iostream>
#include <string>

class Person
{
public:
	Person(std::string name, int age, int grade)
		: m_name(name), m_age(age), m_grade(grade)
	{}

	std::string name() const { return m_name; }
	int age() const { return m_age; }
	int grade() const { return m_grade; }

	// Оператор вывода для удобства отладки
	friend std::ostream& operator<<(std::ostream& os, const Person& person)
	{
		os << "Person { name: \"" << person.m_name 
		   << "\", age: " << person.m_age 
		   << ", grade: " << person.m_grade << " }";
		return os;
	}

private:
	std::string m_name;
	int m_age;
	int m_grade;
};

class Builder
{
public:
	Builder() : m_name(""), m_age(0), m_grade(0) {}

	Builder& name(const std::string& name)
	{
		m_name = name;
		return *this;
	}

	Builder& age(int age)
	{
		m_age = age;
		return *this;
	}

	Builder& grade(int grade)
	{
		m_grade = grade;
		return *this;
	}

	Person get() const
	{
		return Person(m_name, m_age, m_grade);
	}

private:
	std::string m_name;
	int m_age;
	int m_grade;
};

int main()
{
	Builder builder;
	auto person = builder.name("Ivan").age(25).grade(10).get();

	assert(person.name() == "Ivan");
	assert(person.age() == 25);
	assert(person.grade() == 10);

	std::cout << "Test 1 passed: " << person << std::endl;

	Builder builder2;
	auto person2 = builder2.name("Maria").age(30).grade(5).get();

	assert(person2.name() == "Maria");
	assert(person2.age() == 30);
	assert(person2.grade() == 5);

	std::cout << "Test 2 passed: " << person2 << std::endl;

	Builder builder3;
	auto person3 = builder3.grade(8).age(22).name("Alex").get();

	assert(person3.name() == "Alex");
	assert(person3.age() == 22);
	assert(person3.grade() == 8);

	std::cout << "Test 3 passed: " << person3 << std::endl;

	// Создание нескольких объектов из одного Builder
	Builder builder4;
	builder4.name("John").age(40);
	
	auto person4a = builder4.grade(7).get();
	auto person4b = builder4.grade(9).get();

	assert(person4a.name() == "John");
	assert(person4a.age() == 40);
	assert(person4a.grade() == 7);

	assert(person4b.name() == "John");
	assert(person4b.age() == 40);
	assert(person4b.grade() == 9);

	std::cout << "Test 4a passed: " << person4a << std::endl;
	std::cout << "Test 4b passed: " << person4b << std::endl;

	Builder builder5;
	auto person5 = builder5.get();  // Используем значения по умолчанию

	assert(person5.name() == "");
	assert(person5.age() == 0);
	assert(person5.grade() == 0);

	std::cout << "Test 5 passed: " << person5 << std::endl;

	Builder builder6;
	auto person6 = builder6.name("Bob").age(18).get();  // grade по умолчанию

	assert(person6.name() == "Bob");
	assert(person6.age() == 18);
	assert(person6.grade() == 0);

	std::cout << "Test 6 passed: " << person6 << std::endl;

	std::cout << "\nAll tests passed successfully!" << std::endl;
}

