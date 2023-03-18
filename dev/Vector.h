//
// Created by Egor on 16.03.2023.
//

#ifndef CLASS_VECTOR_VECTOR_H
#define CLASS_VECTOR_VECTOR_H




class Vector {
    friend class Segment;
protected:
    double x;
    double y;
    double z;

public:
    Vector();

    Vector(double x, double y, double z);

    Vector GetCopy();
    Vector Change(double x, double y, double z);
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

#endif //CLASS_VECTOR_VECTOR_H
