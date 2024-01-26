#include <iostream>
#include <vector>
#include <algorithm>
#include "../lib/bigfloat.hpp"

using namespace std;

int main() {
    BigFloat precision(vector<digit_t>(1, 0), 1, 100, BigInt::Positive);
    BigFloat one(vector<digit_t>(1, 1), 1, 0, BigInt::Positive);
    BigFloat other = BigFloat();
    for (int i = 0; i < 100; i++) {
        cout << (other + precision).inversed() << endl;
        other = other + one;
    }
    return 0;
}