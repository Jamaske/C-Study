#include <iostream>
#include "Vector.h"

using namespace std;
int main() {

    Vector X(3,3,3);
    Vector Y(8,6,1);
    X.PrintVector();
    Y.PrintVector();
    cout << "X len: "<<X.Len() << endl;
    cout << "Y len: "<<Y.Len() << endl;

    Vector Sum = X + Y;
    cout << "sum of X, Y";
    Sum.PrintVector();

    double t = 3;
    Vector Scaled=Sum * t;
    cout << "C*t=";
    Scaled.PrintVector();

    cout << "creating segment" << endl;
    Segment A(X,Y) ;
    cout << "A is: "; A.PrintSegment();
    cout << "Len of A: "<<A.Len() << endl;
    cout <<"check if sum is part of A" << endl;
    cout << "Answer: " <<A.IsBelong(Sum);
    return 0;

}
