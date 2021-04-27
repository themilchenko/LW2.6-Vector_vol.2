#include "Vector.h"

template <class T>
Vector<T>::Vector(const T* vec, size_t num) : _size(num), _capacity(_size + 1)
{
    digits = new T[_capacity];

    for (int i = 0; i < _size; ++i)
        digits[i] = vec[i];
}

template <class T>
Vector<T>::Vector(const Vector<T>& vec) : _size(vec._size), _capacity(vec._capacity)
{
    if (_capacity == 1)
        digits = new T[1];
    else
    {
        digits = new T[_capacity];

        for (int i = 0; i < _size; ++i)
            digits[i] = vec.digits[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        if (_capacity != other._capacity)
        {
            delete[] digits;
            _capacity = other._capacity;
            _size = other._size;
            digits = new T[_capacity];
        }

        for (int i = 0; i < _size; ++i)
            digits[i] = other.digits[i];
    }

    return *this;
}

template <typename T>
void Vector<T>::reserve(size_t num)
{
    if (num > _capacity)
    {
        _capacity = num;

        T *temp;
        temp = new T[_size];
        for (size_t i = 0; i < _size; ++i)
            temp[i] = digits[i];

        delete[] digits;
        digits = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
            digits[i] = temp[i];

        delete[] temp;
    }

}

template <typename T>
VectorIterator<T> Vector<T>::insert(const VectorIterator<T>& it, T&& element)
{
    _size++;

    if (_capacity >= _size)
    {
        T* temp = new T[std::distance(it, this->end()) + 1];
        size_t t_count = 0;
        for (auto iter = it; iter != this->end() - 1; iter++)  /*копирование второй части массива во временный массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        size_t position = std::distance(this->begin(), it);
        digits[std::distance(this->begin(), it)] = element;

        for (size_t i = 0; i < t_count; i++)
            digits[std::distance(this->begin(), it + 1) + i] = temp[i];

        delete[] temp;

        return it - 1;
    }
    else
    {
        size_t pos = 0;     /* ищу индекс, где массив разделится (адрес итератора не будет актуальным при расширении вместимости вектора) */
        for (auto iter = this->begin(); iter != it; iter++)
            pos++;

        T* temp = new T[std::distance(it, this->end())];
        size_t t_count = 0;

        for (auto iter = it; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        this->reserve(1.5 * _capacity);

        digits[pos] = element;
        T* res = new T(digits[pos]);
        VectorIterator<T> result(res);
        pos++;

        for (size_t i = 0; i < t_count; i++)
            digits[pos + i] = temp[i];
        delete[] temp;

        return result;
    }
}

template <typename T>
VectorIterator<T> Vector<T>::insert(const VectorIterator<T>& it, size_t count, T&& element)
{
    _size += count;

    if (_capacity >= _size)
    {
        T* temp = new T[std::distance(it, this->end() - count)];
        size_t t_count = 0;
        for (auto iter = it; iter != this->end() - 1; iter++)  /*копирование второй части массива во временный массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        for (size_t i = 0; i < count; i++)
            digits[std::distance(this->begin(), it + 1) - 1 + i] = element;

        for (size_t i = 0; i < t_count; i++)
            digits[std::distance(this->begin(), it + 1) + count + i - 1] = temp[i];
        delete[] temp;

        return it - 1;
    }
    else
    {
        size_t pos = 0;
        for (auto iter = this->begin(); iter != it; iter++)
            pos++;

        T* temp = new T[std::distance(it, this->end()) - count];
        size_t t_count = 0;

        for (auto iter = it; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        while (_capacity < _size)
            this->reserve(1.5 * _capacity);

        for (size_t i = 0; i < count; i++)
        {
            digits[pos] = element;
            pos++;
        }

        T* res = new T(digits[pos]);
        VectorIterator<T> result(res);
        pos++;

        for (size_t i = 0; i < t_count; i++)
            digits[pos + i] = temp[i];
        delete[] temp;

        return result;
    }
}

template <typename T>
VectorIterator<T> Vector<T>::insert(const VectorIterator<T>& _where,
                                    const VectorIterator<T>& l_it,
                                    const VectorIterator<T>& r_it)
{

    if (_size + std::distance(l_it, r_it) <= _capacity)
    {
        size_t cur_size = std::distance(l_it, r_it);
        T* temp = new T[std::distance(_where, this->end())];
        size_t t_count = 0;

        for (auto iter = _where; iter != this->end(); iter++) /*копирование второй части во вр. массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        VectorIterator<T> it = l_it;
        for (size_t i = 0; i < cur_size; i++) /*заполняем промежуток нужными элементами*/
        {
            digits[std::distance(this->begin(), _where + 1) - 1 + i] = *it;
            it++;
        }

        for (size_t i = 0; i < t_count; i++)  /*вставляем то что держали во вр. массиве*/
            digits[std::distance(this->begin(), _where + 1) + cur_size + i - 1] = temp[i];

        _size += cur_size;
        delete[] temp;
        return VectorIterator<T>(this->begin() + std::distance(this->begin(), _where) + cur_size - 1);
    }
    else
    {
        size_t cur_size = std::distance(l_it, r_it);
        size_t pos = 0;
        for (auto iter = this->begin(); iter != _where; iter++)
            pos++;

        size_t tt = std::distance(_where, this->end());
        T* temp = new T[std::distance(_where, this->end())];
        size_t t_count = 0;

        for (auto iter = _where; iter != this->end(); iter++)  /*копирование второй части массива во временный массив*/
        {
            temp[t_count] = *iter;
            t_count++;
        }

        while (_capacity < _size + cur_size)    /*пока места не будет достаточно, выделяем память*/
            this->reserve(1.5 * _capacity);

        for (auto iter = l_it; iter != r_it; iter++)      /*копируем что требуется */
        {
            digits[pos] = *iter;
            pos++;
        }

        T* res = new T(*(r_it - 1));

        for (size_t i = 0; i < t_count; i++)  /*вставляем то что запоминали*/
        {
            digits[pos] = temp[i];
            pos++;
        }

        _size += cur_size;
        delete[] temp;
        return VectorIterator<T>(res);
    }
}

template <typename T>
VectorIterator<T> Vector<T>::erase(const VectorIterator<T>& it)
{
    T* temp = new T[std::distance(it + 1, this->end())];
    size_t count = 0;

    for (auto iter = it + 1; iter != this->end(); iter++)
    {
        temp[count] = *iter;
        count++;
    }

    size_t pos = 0;
    for (size_t i = std::distance(this->begin(), it); i < std::distance(this->begin(), this->end()); i++)
    {
        digits[i] = temp[pos];
        pos++;
    }

    delete[] temp;
    _size--;
    return it;
}

template <typename T>
VectorIterator<T> Vector<T>::erase(const VectorIterator<T>& l_it, const VectorIterator<T>& r_it)
{
    size_t distance = std::distance(l_it, r_it);
    size_t count = 0;
    T* temp = new T[std::distance(r_it, this->end())];

    for (auto iter = r_it; iter != this->end(); iter++)
    {
        temp[count] = *iter;
        count++;
    }

    size_t pos = 0;
    for (size_t i = std::distance(this->begin(), l_it); i < std::distance(this->begin(), r_it); i++)
    {
        digits[i] = temp[pos];
        pos++;
    }

    delete[] temp;
    _size -= distance;
    return l_it;
}

template <typename T>
void Vector<T>::push_back(T&& element)
{
    if (_capacity > _size)
    {
        _size++;
        digits[_size - 1] = element;
    }
    else
    {
        if (_capacity == 0)
            _capacity = 2;
        reserve(1.5 * _capacity);
        _size++;
        digits[_size - 1] = element;
    }
}

template <typename T>
void Vector<T>::resize(size_t actual_size)
{
    T* temp = new T[_size];

    for (size_t i = 0; i < _size; i++)
        temp[i] = digits[i];

    delete[] digits;
    digits = new T[actual_size];

    if (actual_size < _size)
        for (size_t i = 0; i < actual_size; i++)
            digits[i] = temp[i];
    else
    {
        for (size_t i = 0; i < _size; i++)
            digits[i] = temp[i];

        //for (size_t i = _size; i < actual_size; i++)
        //   digits[i] = 0;
    }

    delete[] temp;
    _size = actual_size;
    if (_capacity < _size)
        _capacity = _size;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other)
{
    Vector temp = *this;
    *this = other;
    other = temp;
}