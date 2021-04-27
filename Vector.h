#include "VectorIterator.h"
#include <stdexcept>
#include <iostream>

#pragma once

template <typename T>
class Vector
{
    T* digits;
    size_t _size;
    size_t _capacity;

public:
    Vector() : digits(nullptr), _size(0), _capacity(0) { };
    Vector(const Vector<T>& vec);
    Vector(const T* vec, size_t num);

    void print()
    {
        for (const T& i : *this)
            std::cout << i << ' ';
        std::cout << std::endl;
    }

    size_t size() const { return _size; };
    size_t length() const { return _size; };
    size_t capacity() const { return _capacity - 1; };

    ~Vector()
    {
        if (digits != nullptr)
            delete[] digits;
    };

    Vector& operator=(const Vector<T>& other);
    VectorIterator<T> begin() const { return VectorIterator<T>(&digits[0]); };
    VectorIterator<T> end() const { return VectorIterator<T>(&digits[_size]); };

    T& at(size_t index)
    {
        if ((index < _size) && (index >= 0))
            return digits[index];
        else
            throw std::out_of_range("Out of range");
    }

    T& operator[](size_t index) { return digits[index]; };

    T& front() { return *this->begin(); };
    T& back() { return *(this->end() - 1); };

    T* data() { return digits; };

    bool empty() const
    {
        if (_size == 0)
            return true;
        else
            return false;
    }

    void reserve(size_t num);

    void clear()
    {
        delete[] digits;
        digits = nullptr;
        _size = 0;
        size_t temp = _capacity;
        _capacity = 0;
        reserve(temp);
    }

    VectorIterator<T> insert(const VectorIterator<T>& it, T&& element);
    VectorIterator<T> insert(const VectorIterator<T>& it, size_t count, T&& element);
    VectorIterator<T> insert(const VectorIterator<T>& _where,
                             const VectorIterator<T>& l_it,
                             const VectorIterator<T>& r_it);

    VectorIterator<T> erase(const VectorIterator<T>& it);
    VectorIterator<T> erase(const VectorIterator<T>& l_it, const VectorIterator<T>& r_it);

    void push_back(T&& element);
    void pop_back() { _size--; };

    void resize(size_t actual_size);
    void swap(Vector& other);
};