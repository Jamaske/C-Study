#pragma once
#include <cmath>
#include <fstream>

template<typename T>
class Vector {
    friend T triple_prod(const Vector<T>& a, const Vector<T>& b, const Vector<T>& c);

public:
    T x;
    T y;
    T z;

public:
    Vector(T x, T y, T z);
    Vector();
    ~Vector();
    Vector(const Vector<T> &src);
    Vector<T>& operator=(const Vector<T> &src);
    //T operator[](unsigned char which);
    T Len2();
    Vector<T> operator+(const Vector<T>& other);
    Vector<T> operator-(const Vector<T>& other);
    T operator*(const Vector<T>& other);//dot product
    Vector<T> operator^(const Vector<T>& other);//cross product
    Vector<T> operator*(T t);//scalar multiplying
    void PrintVector(std::ostream out);//unchecked
};
template<typename T>
T triple_prod(const Vector<T>& a, const Vector<T>& b, const Vector<T>& c);

template<typename T>
class Line {

public:
    Vector<T> base;
    Vector<T> dir;

public:
    Line(const Vector<T>& base, const Vector<T>& dir);
    Line(const Plane<T>& a, const Plane<T>& b);
    Line(const Line<T>& src);
    ~Line();
    Line<T>& operator=(const Line<T>& src);

    bool IsBelong(const Vector<T>& some_point);
    bool IsParallel(const Vector<T>& other_Line);


};


template<typename T>
class Segment {
public:
    Vector<T> p0;
    Vector<T> p1;

public:
    Segment(Vector<T> point0, Vector<T> point1);
    Segment();
    ~Segment();
    Segment(Segment<T> &src);
    Segment<T>& operator=(const Segment<T> &src);

    Vector<T> Get_Dir_Vec();
    T Len2();
    bool IsBelong(const Vector<T>& some_point);
//    bool IsIntersects(Segment<T> other_segment);
//    T crossing_dist(Segment<T> other_segment);
//    Vector<T> Intersection(Segment<T> other_segment);
    void PrintSegment();
};

template<typename T>
class Plane {
public:
    // Ax + By + C*z + D = 0
    Vector<T> norm;// (A,B,C)
    T offset;// D


public:
    Plane(Vector<T> normal, T offset);
    Plane(Vector<T> normal, Vector<T> any_point);
    Plane(Vector<T> A, Vector<T> B, Vector<T> C);
    ~Plane();
    Plane(const Plane<T>& src);
    Plane<T>& operator=(const Plane<T>& src);

    bool IsBelong(const Vector<T>& some_point);
    bool Dist_to_Point(const Vector<T>& some_point, T& dist);



    bool IsParallel(const Plane<T>& other_plane);
    bool Intersection(const Plane<T>& other_plane, Vector<T>& intersection = Vector<T>(), T& dist = 0);

};


#include"Vector.tpp"