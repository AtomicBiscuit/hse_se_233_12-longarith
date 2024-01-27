#include <iostream>
#include <vector>
#include "bigfloat.h"

void calc_pi(uint32_t precision) {
    BigFloat zero = BigFloat(std::vector<unsigned char>(1, 0), 1, precision, BigInt::Positive);
    std::cout << "0";
}

using std::cout;
using std::endl;

int main() {
    std::cout << "How about calc Pi?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "\"something else\". No, exit" << std::endl;
    std::cout << "Your answer: ";
    std::string s;
    std::cin >> s;
    if (s == "1") {
        std::cout << "Enter precision: ";
        uint32_t precision;
        std::cin >> precision;
        if (precision > BigInt::MAX_SIZE) {
            std::cout << "Too big" << std::endl;
            return 0;
        }
        calc_pi(precision);
    } else {
        std::cout << "Bye" << std::endl;

    }
    return 0;
}