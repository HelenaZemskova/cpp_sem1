#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void order(std::vector<T> & vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i) 
    {
        for (auto j = i; j > left; --j)
        {
            if (vector[j - 1] > vector[j]) 
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

// Вычисление медианы первого, среднего и последнего элементов
template <typename T>
T medianOfThree(std::vector<T> & vector, std::size_t left, std::size_t right)
{
    std::size_t mid = left + (right - left - 1) / 2;
    std::size_t last = right - 1;
    
    if (vector[left] > vector[mid])
        std::swap(vector[left], vector[mid]);
    if (vector[left] > vector[last])
        std::swap(vector[left], vector[last]);
    if (vector[mid] > vector[last])
        std::swap(vector[mid], vector[last]);
    
    std::swap(vector[mid], vector[last]);
    
    return vector[last];
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::size_t hoare(std::vector<T> & vector, std::size_t left, std::size_t right)
{
    // Выбираем опорный элемент как медиану трех и перемещаем его в конец
    T pivot = medianOfThree(vector, left, right);
    std::size_t last = right - 1;
    
    std::size_t i = left;
    std::size_t j = last - 1;
    
    while (true) {
        while (vector[i] < pivot) {
            ++i;
        }
        
        while (j > left && vector[j] > pivot) {
            --j;
        }
        
        if (i >= j) {
            std::swap(vector[i], vector[last]);
            return i;
        }
        
        std::swap(vector[i], vector[j]);
    }
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void quick_sort(std::vector<T> & vector, std::size_t left, std::size_t right)
{
    // Для небольших подмассивов используем сортировку вставками
    if (right - left > 16)
    {
        std::size_t pivot_index = hoare(vector, left, right);
        
        quick_sort(vector, left, pivot_index);
        quick_sort(vector, pivot_index + 1, right);
    }
    else
    {
        order(vector, left, right);
    }
}

////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void sort(std::vector<T> & vector)
{
    quick_sort(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // Тест с int
    auto size = 1'000uz;
//  ---------------------------------------
    std::vector<int> vector_int(size, 0);
//  ---------------------------------------
    for (auto i = 0uz; i < size; ++i)
    {
        vector_int[i] = size - i;
    }
//  ---------------------------------------
    sort(vector_int);
//  ---------------------------------------
    assert(std::ranges::is_sorted(vector_int));

    // Тест с double
    std::vector<double> vector_double = {5.5, 2.2, 8.8, 1.1, 9.9, 3.3};
    sort(vector_double);
    assert(std::ranges::is_sorted(vector_double));

    // Тест с char
    std::vector<char> vector_char = {'z', 'a', 'm', 'b', 'y', 'c'};
    sort(vector_char);
    assert(std::ranges::is_sorted(vector_char));

    // Тест со строками
    std::vector<std::string> vector_string = {"zebra", "apple", "mango", "banana"};
    sort(vector_string);
    assert(std::ranges::is_sorted(vector_string));
}

////////////////////////////////////////////////////////////////////////////////////

