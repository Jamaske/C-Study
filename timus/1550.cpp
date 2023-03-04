#include <iostream>
#include <iomanip>

using namespace std;
const double Pi=3.14159'26535'89793'23846;

int main(){
    double H, W, x, y, r;
    cin >> H >> W >> x >> y >> r;
    cout << fixed << setprecision(5);
    cout << H*( (W * W / 3.0) + (Pi * r * r * (2 * max(abs(x), abs(y)) / W - 1)) );
}