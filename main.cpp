#include <iostream>
#include <vector>
#include <ctime>
#include "bigfloat.h"
#include <limits>


using std::cout;
using std::endl;

void calc_pi(uint32_t precision) {
    std::clock_t c_start = std::clock();
    BigFloat zero = BigFloat(std::vector<unsigned char>(1, 0), 1, precision + 10, BigFloat::Positive);
    BigFloat pi_raw = {};
    BigFloat k = {}, sixteen_pow_k = 1_bf;
    BigFloat num, den;
    uint32_t i = precision + 1;
    do {
        num = k * (k * 120_bf + 151_bf) + 47_bf;
        den = k * (k * (k * (k * 512_bf + 1024_bf) + 712_bf) + 194_bf) + 15_bf;
        pi_raw = pi_raw + num.shift(precision + 10) / (sixteen_pow_k * den);
        sixteen_pow_k = sixteen_pow_k * 16_bf;
        k = k + 1_bf;
    } while (--i);
    pi_raw = pi_raw.shift(-1 * (pi_raw.size() - precision - 1));
    std::cout << "pi: " << endl;
    BigFloat pi(pi_raw.as_array(), pi_raw.size(), precision, BigFloat::Positive);
    cout << pi << endl;
    cout << "Time spend: " << 1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "ms" << endl;
}

int main() {
    cout << "How about calc Pi?" << endl;
    cout << "1. Yes" << endl;
    cout << "(Any other answer). No, exit" << endl;
    cout << "Your answer: ";
    std::string s;
    std::cin >> s;
    if (s == "1") {
        cout << "Enter precision: ";
        uint32_t precision;
        std::cin >> precision;
        calc_pi(precision);
    } else {
        cout << "Bye" << endl;
    }
    return 0;
}