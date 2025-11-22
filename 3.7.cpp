#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>
#include <cassert>
#include <cmath>

class Vector {
private:
    int* m_data = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;

public:
    Vector() = default;
    
    Vector(std::size_t initial_capacity) : m_capacity(initial_capacity) {
        if (m_capacity > 0) {
            m_data = new int[m_capacity];
        }
    }
    
    Vector(std::initializer_list<int> list) : m_size(list.size()), m_capacity(list.size()) {
        if (m_capacity > 0) {
            m_data = new int[m_capacity];
            std::copy(list.begin(), list.end(), m_data);
        }
    }
    

    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        if (m_capacity > 0) {
            m_data = new int[m_capacity];
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
        }
    }
    
    Vector(Vector&& other) noexcept 
        : m_data(std::exchange(other.m_data, nullptr)),
          m_size(std::exchange(other.m_size, 0)),
          m_capacity(std::exchange(other.m_capacity, 0)) {}
    
    Vector& operator=(Vector other) {
        swap(other);
        return *this;
    }
    
    ~Vector() {
        delete[] m_data;
    }
    
    void swap(Vector& other) noexcept {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }
    

////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t size() const { return m_size; }
    std::size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }
    
    int& operator[](std::size_t index) { return m_data[index]; }
    const int& operator[](std::size_t index) const { return m_data[index]; }
    
    void reserve(std::size_t new_capacity) {
        if (new_capacity <= m_capacity)
            return;

        int *new_array = new int[new_capacity];

        if (m_data) {
            std::ranges::copy(m_data, m_data + m_size, new_array);
            delete[] m_data;
        }

        m_data = new_array;
        m_capacity = new_capacity;
    }
    
    void push_back(int value) {
        if (m_size == m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }

        m_data[m_size] = value;
        ++m_size;
    }
    

    void clear() {
        m_size = 0;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////
};




int main() {
    Vector vec;
    assert(vec.empty());
    std::cout << "empty test passed \n"; 
    
    // Добавляем элементы и наблюдаем за ростом емкости
    for (int i = 1; i <= 20; ++i) {
        vec.push_back(i);
        assert(vec[i-1] == i);
        assert(vec.size() == i);
        std::cout << vec.capacity() << std::endl;
        //assert(vec.capacity() == std::pow(2, i / 2));
    }
    std::cout << "push back and capacity growth test passed \n"; 

    vec.clear();
    assert(vec.size() == 0);
    assert(vec.capacity() == 32);
    std::cout << "vector.clear test passed \n"; 
    
    return 0;
}