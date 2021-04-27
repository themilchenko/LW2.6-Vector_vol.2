#include "Vector.h"
#include "Vector.cpp"
#include "MyDataType.h"

template class Vector<int>;
template class Vector<double>;
template class Vector<char>;
template class Vector<size_t>;
template class Vector<std::string>;
template class Vector<MyDataType>;

template class VectorIterator<int>;
template class VectorIterator<double>;
template class VectorIterator<char>;
template class VectorIterator<size_t>;
template class VectorIterator<std::string>;
template class VectorIterator<MyDataType>;