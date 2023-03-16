#include <iostream>
#include "Vector.h"
#include <iostream>

using namespace std;

int main() {

    Vector A(1,3,5);
    Vector B(3,6,5);
    A.PrintVector();
    B.PrintVector();
    cout << "A length is: "<<A.Len() << endl;
    cout << "B length is: "<<B.Len() << endl;

    Vector C = A + B;
    cout << "A+B=C";
    C.PrintVector();

    double t=10;
    C=C*t;
    cout << "C*t=";
    C.PrintVector();
///////////////////////////////////////////////////////////////
    Segment Alpha(A,B) ;
    cout << "Alpha.L0enght= "<<Alpha.Len() << endl;
    cout <<"Now we are going to know is point C belong Alpha" << endl;
    cout << "Alpha is: "; Alpha.PrintSegment();
    cout << "point C: "; C.PrintVector();
    cout << "Answer: " <<Alpha.IsBelong(C);
    return 0;

}
