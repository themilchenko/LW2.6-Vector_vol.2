#include <iterator>

#pragma once

template <typename T>
class VectorIterator
{
    T* pos;

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;

    VectorIterator(T* position) : pos(position) { };

    bool operator==(const VectorIterator<T>& other) const { return pos == other.pos; };
    bool operator!=(const VectorIterator<T>& other) const { return pos != other.pos; };
    bool operator>(const VectorIterator<T>& other) const  { return pos > other.pos;  };
    bool operator<(const VectorIterator<T>& other) const  { return pos < other.pos;  };
    bool operator>=(const VectorIterator<T>& other) const { return pos >= other.pos; };
    bool operator<=(const VectorIterator<T>& other) const { return pos <= other.pos; };

    reference operator*() const { return *pos; };
    pointer operator->() const { return pos; };

    VectorIterator& operator++()
    {
        ++pos;
        return *this;
    };

    VectorIterator& operator++(int)
    {
        VectorIterator<T> temp = *this;
        ++pos;
        return temp;
    };

    VectorIterator& operator--()
    {
        --pos;
        return *this;
    };

    VectorIterator& operator--(int)
    {
        VectorIterator<T> temp = *this;
        --pos;
        return temp;
    };

    reference operator[](size_t index) const { return pos[index]; };

    VectorIterator operator+(const difference_type& diff) const { return VectorIterator<T>(pos + diff); };
    friend inline VectorIterator operator+(const difference_type& diff, const VectorIterator<T>& other)
    {
        return VectorIterator<T>(other.pos + diff);
    };

    VectorIterator<T> operator-(const difference_type& diff) const { return VectorIterator<T>(pos - diff); };
    difference_type operator-(const VectorIterator<T>& other) const { return std::distance(other.pos, pos); };

    VectorIterator<T> operator+=(const difference_type& diff)
    {
        pos += diff;
        return *this;
    };

    VectorIterator<T> operator-=(const difference_type& diff)
    {
        pos -= diff;
        return *this;
    };
};