#include <iostream>
#include <vector>
#include "../lib/longarithmetic.hpp"

using namespace std;

int main() {
    vector<digit_t> a = { 5, 5, 5 };
    BigInt A(a, 3, BigInt::Negative);
    vector<digit_t> num = { 1, 5, 6, 8 };
    BigInt B(num, 4, BigInt::Negative);
    BigInt C = B - A;
    cout << C + A + A << endl;
    cout << A << " + " << B << " = " << A + B << endl;
    cout << A << " - " << B << " = " << A - B << endl;
    return 0;
}