#include <cassert>
#include <iostream>
#include <vector>
#include <string>

// вставка значения в контейнер
template<typename Container>
void handle(Container & container, int value)
{
    container.push_back(value);
}

template<typename Container, typename T>
void handle(Container &, T)
{
    // Игнорируем аргументы других типов
}

// Функция вставки с использованием свертки и запятой
template<typename Container, typename... Args>
void insert(Container & container, Args... args)
{
    (handle(container, args), ...);
}

int main()
{
    // только int
    std::vector<int> vec1;
    insert(vec1, 1, 2, 3, 4, 5);
    assert(vec1.size() == 5);
    assert(vec1[0] == 1);
    assert(vec1[1] == 2);
    assert(vec1[2] == 3);
    assert(vec1[3] == 4);
    assert(vec1[4] == 5);

    // int и double
    std::vector<int> vec2;
    insert(vec2, 10, 3.14, 20, 2.71, 30);
    assert(vec2.size() == 3);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);
    assert(vec2[2] == 30);

    // int, double, string, char
    std::vector<int> vec3;
    insert(vec3, 100, "hello", 200, 3.14159, 'a', 300, std::string("world"), 400);
    assert(vec3.size() == 4);
    assert(vec3[0] == 100);
    assert(vec3[1] == 200);
    assert(vec3[2] == 300);
    assert(vec3[3] == 400);

    // только не-int 
    std::vector<int> vec4;
    insert(vec4, "test", 3.14, 'x', std::string("abc"));
    assert(vec4.size() == 0);

    // пустой пакет
    std::vector<int> vec5;
    insert(vec5);
    assert(vec5.size() == 0);

    // один int
    std::vector<int> vec6;
    insert(vec6, 42);
    assert(vec6.size() == 1);
    assert(vec6[0] == 42);

    // отрицательные числа
    std::vector<int> vec7;
    insert(vec7, -10, 2.5, -20, "test", -30);
    assert(vec7.size() == 3);
    assert(vec7[0] == -10);
    assert(vec7[1] == -20);
    assert(vec7[2] == -30);

    std::cout << "All tests passed successfully!" << std::endl;
}

