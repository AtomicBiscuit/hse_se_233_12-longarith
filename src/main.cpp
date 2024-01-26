#include <iostream>
#include <vector>
#include <algorithm>
#include "../lib/bigfloat.hpp"

using namespace std;

int main() {
    BigFloat zero = BigFloat(vector<digit_t>(1, 0), 1, 20, BigInt::Positive);
    BigFloat a = 3.0_bf, b = 15.0_bf;
    cout << b << " " << b / a << endl;
    cout << 15.01_bf / 3_bf << endl;
    return 0;
}