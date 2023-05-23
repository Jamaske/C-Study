#pragma once


template<typename T>
class Vector {
    friend class Segment;
protected:
    T x;
    T y;
    T z;

public:
    Vector(T x, T y, T z);
    Vector();
    ~Vector();
    Vector(const Vector<T> &src);
    Vector<T> operator=(Vector<T> &src);
    T Len2();
    double Len();
    Vector operator+(Vector other);
    double operator*(Vector& other);
    Vector operator^(Vector& other);
    Vector operator*(double t);
    void PrintVector();
};

class Segment {
protected:
    Vector start;
    Vector end;
public:
    Segment();
    Segment(Vector start,Vector end);
    double Len();
    bool IsBelong(Vector t);
    void PrintSegment();

};

#include"Vector.tpp"