#include "Vector.h"
#include <cmath>
#include <iostream>
Vector::Vector() {
    Vector::x=0;
    Vector::y=0;
    Vector::z=0;
}

Vector::Vector(double x, double y, double z) {
    Vector::x=x;
    Vector::y=y;
    Vector::z=z;
}

Vector Vector::Change(double x, double y, double z) {
    Vector::x = x;
    Vector::y = y;
    Vector::z = z;
}

Vector Vector::GetCopy() {
    Vector temp;
    temp.x = Vector::x;
    temp.y = Vector::y;
    temp.z = Vector::z;
    return temp;

}

double Vector::Len() {

    return sqrt(Vector::x*Vector::x+Vector::y*Vector::y+Vector::z*Vector::z);
}

Vector Vector::operator+(Vector other) {
    Vector temp;
    temp.x=Vector::x+other.x;
    temp.y=Vector::y+other.y;
    temp.z=Vector::z+other.z;
    return temp;
}

double Vector::operator*(Vector &other) {//dot product
    return Vector::x * other.x + Vector::y * other.y + Vector::z * other.z;
}


Vector Vector::operator^( Vector &other) {//cross product
    Vector temp;
    temp.x = Vector::y * other.z - Vector::z * other.y;
    temp.y=Vector::x * other.z - Vector::z * other.x;
    temp.z=Vector::x * other. y - Vector::y * other.x;
    return temp;
}

Vector Vector::operator*( double t) {
    Vector temp;
    temp.x=Vector::x * t;
    temp.y=Vector::y * t;
    temp.z=Vector::z * t;
    return temp;
}

void Vector::PrintVector() {
    std::cout << "("<<Vector::x <<"; "<< Vector::y<<"; "<< Vector::z<<' ' <<')'<< std::endl;
}

Segment::Segment() {
    Segment::start=Vector();
    Segment::end=Vector();
}

Segment::Segment(Vector start,Vector end) {
    Segment::start=start;
    Segment::end=end;
}

double Segment::Len() {
    return (end + (start * -1.f)).Len() ;
}

bool Segment::IsBelong(Vector t) {
    const double eps = 0.995;
    Vector a = t + start * -1;
    Vector b = end + t * -1;
    double len_prod = a.Len() * b.Len();
    return a * b > len_prod * eps;
}

void Segment::PrintSegment() {
    std::cout << "start: ";
    start.PrintVector();
    std::cout << "end: ";
    end.PrintVector();
}
