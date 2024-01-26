#include <iostream>
#include <vector>
#include <algorithm>
#include "../lib/bigfloat.hpp"

int main() {
    BigFloat zero = BigFloat(std::vector<digit_t>(1, 0), 1, 20, BigInt::Positive);
    BigFloat a = 3.0_bf, b = 15.0_bf;
    std::cout << b << " " << b / a << std::endl;
    std::cout << 15.01_bf / 3_bf << std::endl;
    return 0;
}