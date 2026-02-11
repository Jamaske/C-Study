#include <iostream>
#include <fstream>
using namespace std;

int main() {
#ifdef LOCAL_DEBUG
    ifstream fin("test_input.txt");
#define cin fin  // Redirect cin to read from the file
#endif
    return 0;
}