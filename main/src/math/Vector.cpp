

#include "Vector.hpp"

// Constructor implementation
template <typename T, int _Nm, TypeOfVector Type >
Vector<T, _Nm , Type >::Vector(T *data )
{
    // Assuming _Nm elements are provided in the 'data' array
    for (int i = 0; i < _Nm; ++i)
        _data[i] = data[i];
}
template <typename T, int _Nm, TypeOfVector Type >
Vector<T, _Nm , Type >::Vector( )
{
    // Assuming _Nm elements are provided in the 'data' array
    for (int i = 0; i < _Nm; ++i)
        _data[i] = 0;
}

// Accessor implementations
template <typename T, int _Nm, TypeOfVector Type >
T &Vector<T, _Nm , Type >::x()
{
    return _data[0];
}

template <typename T, int _Nm, TypeOfVector Type >
T &Vector<T, _Nm , Type >::y()
{
    return _data[1];
}

template <typename T, int _Nm, TypeOfVector Type >
T &Vector<T, _Nm , Type >::z()
{
    return _data[2];
}

template <typename T, int _Nm , TypeOfVector Type>
T &Vector<T, _Nm , Type>::t()
{
    return _data[3];
}

// Scalar operation implementations
template <typename T, int _Nm, TypeOfVector Type >
template <typename T2>
T Vector<T, _Nm , Type >::operator*(const T2 &other) const
{
    // Scalar multiplication
    // Assuming T has operator* defined
    T result;
    for (int i = 0; i < _Nm; ++i)
        result[i] = _data[i] * other;
    return result;
}

template <typename T, int _Nm, TypeOfVector Type >
template <typename T2>
T Vector<T, _Nm , Type >::operator+(const T2 &other) const
{
    // Scalar addition
    // Assuming T has operator+ defined
    T result;
    for (int i = 0; i < _Nm; ++i)
        result[i] = _data[i] + other;
    return result;
}

template <typename T, int _Nm, TypeOfVector Type >
template <typename T2>
T Vector<T, _Nm , Type >::operator-(const T2 &other) const
{
    // Scalar subtraction
    // Assuming T has operator- defined
    T result;
    for (int i = 0; i < _Nm; ++i)
        result[i] = _data[i] - other;
    return result;
}

template <typename T, int _Nm, TypeOfVector Type >
template <typename T2>
T Vector<T, _Nm , Type >::operator/(const T2 &other) const
{
    // Scalar division
    // Assuming T has operator/ defined
    T result;
    for (int i = 0; i < _Nm; ++i)
        result[i] = _data[i] / other;
    return result;
}

template <typename T, int _Nm, TypeOfVector Type >
template <typename T2>
T Vector<T, _Nm , Type >::operator%(const T2 &other) const
{
    // Scalar modulo
    // Assuming T has operator% defined
    T result;
    for (int i = 0; i < _Nm; ++i)
        result[i] = _data[i] % other;
    return result;
}

// // Destructor implementation
// template <typename T, int _Nm, TypeOfVector Type >
// Vector<T, _Nm , Type >::~Vector()
// {
//     // Destructor code, if needed
// }
