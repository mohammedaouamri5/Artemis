

#ifndef _VECTOR_H_
#define _VECTOR_H_


enum TypeOfVector {COL , ROW} ; // column(|) vector or row(-) vector
 
template <typename T, int _Nm  , TypeOfVector Type >
struct Vector // its good of you stick to int float
{
private:
    T _data[_Nm];
public:
    Vector(T *data  )  ;
    Vector()  ;
    T &x();
    T &y();
    T &z();
    T &t();

    T &operator[](int i) const;
    // ( vector * scaler ) <=> (scaler * vector)
    template <typename T2>
    T operator*(const T2 &other) const;
    template <typename T2>
    T operator+(const T2 &other) const;
    template <typename T2>
    T operator-(const T2 &other) const;
    template <typename T2>
    T operator/(const T2 &other) const;
    template <typename T2>
    T operator%(const T2 &other) const;

    // // TODO :  vector * vector
    // T operator*(const T & other) const;
    // Vector<float , _Nm> operator*(const Vector<float , _Nm> & other) const;
    // T operator*(const T2 & other) const;
    // ~Vector() = default;
};

#endif // _VECTOR_H_