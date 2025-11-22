#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

void order(std::vector<int> & vector, std::size_t left, std::size_t right)
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
int medianOfThree(std::vector<int> & vector, std::size_t left, std::size_t right)
{
    std::size_t mid = left + (right - left - 1) / 2;
    std::size_t last = right - 1;
    
    // Сортируем три элемента на своих местах
    if (vector[left] > vector[mid])
        std::swap(vector[left], vector[mid]);
    if (vector[left] > vector[last])
        std::swap(vector[left], vector[last]);
    if (vector[mid] > vector[last])
        std::swap(vector[mid], vector[last]);
    
    // Перемещаем медиану (средний элемент) в позицию last для метода Хоара
    std::swap(vector[mid], vector[last]);
    
    // Возвращаем значение медианы
    return vector[last];
}

////////////////////////////////////////////////////////////////////////////////////

// Разбиение Хоара
std::size_t hoare(std::vector<int> & vector, std::size_t left, std::size_t right)
{
    // Выбираем опорный элемент как медиану трех и перемещаем его в конец
    int pivot = medianOfThree(vector, left, right);
    std::size_t last = right - 1;
    
    std::size_t i = left;
    std::size_t j = last - 1;
    
    while (true) {
        // Находим элемент слева, который >= опорного
        while (vector[i] < pivot) {
            ++i;
        }
        
        // Находим элемент справа, который <= опорного
        while (j > left && vector[j] > pivot) {
            --j;
        }
        
        // Если указатели пересеклись - разбиение завершено
        if (i >= j) {
            // Меняем опорный элемент с элементом в позиции i
            std::swap(vector[i], vector[last]);
            return i;
        }
        
        // Меняем местами неупорядоченные элементы
        std::swap(vector[i], vector[j]);
    }
}

////////////////////////////////////////////////////////////////////////////////////

// Рекурсивная процедура быстрой сортировки
void quick_sort(std::vector<int> & vector, std::size_t left, std::size_t right)
{
    // Для небольших подмассивов используем сортировку вставками
    if (right - left > 16)
    {
        // Выполняем разбиение Хоара
        std::size_t pivot_index = hoare(vector, left, right);
        
        // Рекурсивно сортируем левую и правую части
        quick_sort(vector, left, pivot_index);
        quick_sort(vector, pivot_index + 1, right);
    }
    else
    {
        order(vector, left, right);
    }
}

////////////////////////////////////////////////////////////////////////////////////

void sort(std::vector<int> & vector)
{
    quick_sort(vector, 0, std::size(vector));
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1'000uz;
//  ---------------------------------------
    std::vector<int> vector(size, 0);
//  ---------------------------------------
    for (auto i = 0uz; i < size; ++i)
    {
        vector[i] = size - i;
    }
//  ---------------------------------------
    sort(vector);
//  ---------------------------------------
    assert(std::ranges::is_sorted(vector));
}

////////////////////////////////////////////////////////////////////////////////////