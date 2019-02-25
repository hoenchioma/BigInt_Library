#include <iostream>
#include "BigInt.h"
#include <limits>

using namespace std;
using namespace rxh;

int main() {
    BigInt a = 23, b = "55555555555555555555555555555555555555555557777777777";
    cout << a + b << endl;
    cout << (long double) b << endl;
    cout << b*b << endl;
    cout << pow(a, 50) << endl;
    return 0;
}