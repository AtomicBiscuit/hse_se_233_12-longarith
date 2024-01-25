#include <iostream>
#include <vector>
#include "../lib/longarithmetic.hpp"

using namespace std;

int main() {
    vector<digit_t> a = { 9, 8, 4, 3, 5, 7, 1, 2, 3 };
    BigInt A(a, 9, BigInt::Positive);
    vector<digit_t> num = { 1, 5, 6, 8 };
    BigInt B(num, 4, BigInt::Negative);
    BigInt C = B - A;
    cout << C + A + A << endl;
    cout << A << " * " << B << " = " << B * A << endl;
    cout << A << " - " << B << " = " << A - B << endl;
    return 0;
}