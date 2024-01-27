#include <iostream>
#include <vector>
#include <ctime>
#include "bigfloat.h"


using std::cout;
using std::endl;

void calc_pi(uint32_t precision) {
    std::clock_t c_start = std::clock();
    BigFloat zero = BigFloat(std::vector<unsigned char>(1, 0), 1, precision + 10, BigInt::Positive);
    BigInt pi_raw = {};
    BigInt k = {}, sixteen_pow_k = 1_bi;
    BigInt num, den;
    uint32_t i = precision;
    do{
        num = k * (k * 120_bi + 151_bi) + 47_bi;
        den = k * (k * (k * (k * 512_bi + 1024_bi) + 712_bi) + 194_bi) + 15_bi;
        pi_raw = pi_raw + num.shift(precision + 10) / (sixteen_pow_k * den);
        sixteen_pow_k = sixteen_pow_k * 16_bi;
        k = k + 1_bi;
    } while(--i);
    pi_raw = pi_raw.shift(-1 * (pi_raw.size() - precision - 1));
    std::cout << "pi: "<<endl;
    BigFloat pi(pi_raw.as_array(), pi_raw.size(), precision, BigInt::Positive);
    cout << pi << endl;
    cout <<"Time spend: "<<1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "ms" << endl;
}

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