#include <iostream>
#include <vector>
#include "../lib/longarithmetic.hpp"

using namespace std;

int main() {
    vector<digit_t> a = { 5, 5, 5 };
    BigInt A(a, 3, BigInt::Negative);
    vector<digit_t> num = { 1, 5, 6, 8 };
    BigInt B(num, 4, BigInt::Negative);
    cout << (A + B).as_string() << endl;
    return 0;
}