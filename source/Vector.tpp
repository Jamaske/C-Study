#include <cmath>
#include <iostream>
#include "Vector.h"

template<typename T>
Vector<T>::Vector(T x, T y, T z):
        x(x), y(y), z(z){

}

template<typename T>
Vector<T>::Vector():
    Vector(0,0,0){

}

template<typename T>
Vector<T>::~Vector()= default;

template<typename T>
Vector<T>::Vector(const Vector<T> &src):
    x(src.x), y(src.y), z(src.z){

}

template<typename T>
Vector<T> Vector<T>::operator= (Vector<T> &src) {
    x = src.x;
    y = src.y;
    z = src.z;
}

template<typename T>
T Vector<T>::Len2() {
    return Vector::x*Vector::x+Vector::y*Vector::y+Vector::z*Vector::z;
}

template<typename T>
double Vector<T>::Len() {
}

template<typename T>
Vector Vector::operator+(Vector other) {
    Vector temp;
    temp.x=Vector::x+other.x;
    temp.y=Vector::y+other.y;
    temp.z=Vector::z+other.z;
    return temp;
}

template<typename T>
double Vector::operator*(Vector &other) {//dot product
    return Vector::x * other.x + Vector::y * other.y + Vector::z * other.z;
}


template<typename T>
Vector Vector::operator^( Vector &other) {//cross product
    Vector temp;
    temp.x = Vector::y * other.z - Vector::z * other.y;
    temp.y=Vector::x * other.z - Vector::z * other.x;
    temp.z=Vector::x * other. y - Vector::y * other.x;
    return temp;
}

template<typename T>
Vector Vector::operator*( double t) {
    Vector temp;
    temp.x=Vector::x * t;
    temp.y=Vector::y * t;
    temp.z=Vector::z * t;
    return temp;
}

template<typename T>
void Vector::PrintVector() {
    std::cout << "("<<Vector::x <<"; "<< Vector::y<<"; "<< Vector::z<<' ' <<')'<< std::endl;
}


template<typename T>
Segment::Segment() {
    Segment::start=Vector();
    Segment::end=Vector();
}

template<typename T>
Segment::Segment(Vector start,Vector end) {
    Segment::start=start;
    Segment::end=end;
}

template<typename T>
double Segment::Len() {
    return (end + (start * -1.f)).Len() ;
}

template<typename T>
bool Segment::IsBelong(Vector t) {
    const double eps = 0.995;
    Vector a = t + start * -1;
    Vector b = end + t * -1;
    double len_prod = a.Len() * b.Len();
    return a * b > len_prod * eps;
}

template<typename T>
void Segment::PrintSegment() {
    std::cout << "start: ";
    start.PrintVector();
    std::cout << "end: ";
    end.PrintVector();
}
