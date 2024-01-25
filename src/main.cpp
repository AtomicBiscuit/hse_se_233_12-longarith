#include <iostream>
#include <vector>
#include <algorithm>
#include "../lib/longarithmetic.hpp"

using namespace std;

int main() {
    vector<digit_t> a = { 3,0,6,5,0,5,6,0,6,0,6,1,6,1,6,1,6,5,1 };
    vector<digit_t> b = { 1,3,2,1,6,5,1,3,7,9 };
    BigInt Sh(a, 18, BigInt::Negative);
    BigInt A(b, 9, BigInt::Negative);
    cout<< Sh / A << endl;
    return 0;
}