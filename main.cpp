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
    BigFloat eps = BigFloat(std::vector<unsigned char>(1, 1), 1, precision + 10, BigFloat::Positive);
    BigFloat cnst = 426880_bf * (10005_bf + zero).root(2);
    BigFloat cnst_a = (640320_bf + zero).power(3) / 24_bf;
    BigFloat as = 1_bf + zero;
    BigFloat bs = zero;
    BigFloat ak = 1_bf + zero;
    BigFloat k = 1_bf;
    do {
        ak = -ak * ((k * 6_bf - 5_bf) * (k * 2_bf - 1_bf) * (k * 6_bf - 1_bf));
        ak = ak / (k.power(3) * cnst_a);
        as = as + ak;
        bs = bs + k * ak;
        k = k + 1_bf;
    } while (ak.abs() >= eps);
    BigFloat num = 13591409_bf * as + 545140134_bf * bs;
    BigFloat pi = (cnst / num).round(precision);
    std::cout << "pi: " << endl;
    cout << pi << endl;
    cout << "Time spend: " << 1.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "s" << endl;
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