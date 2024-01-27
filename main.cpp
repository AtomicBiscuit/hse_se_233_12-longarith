#include <iostream>
#include <vector>
#include "lib/bigfloat.h"

void calc_pi(uint32_t precision) {
    BigFloat zero = BigFloat(std::vector<unsigned char>(1, 0), 1, precision, BigInt::Positive);
    std::cout << zero;
}

using std::cout;
using std::endl;

int main() {
    cout << "How about calc Pi?" << endl;
    cout << "1. Yes" << endl;
    cout << "(Any other answer). No, exit" << endl;
    cout << "Your answer: ";
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