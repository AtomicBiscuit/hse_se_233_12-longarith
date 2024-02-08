#include <iostream>
#include <ctime>
#include "bigfloat.h"

void calc_pi(uint32_t precision) {
    std::clock_t c_start = std::clock();
    BigFloat zero = BigFloat(0, precision + 10);
    BigFloat eps = BigFloat(1, precision + 10);
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
    std::cout << "PI with " << pi.precision() << " digits:" << std::endl;
    std::cout << pi << std::endl;
    std::cout << "Time spend: " << static_cast<double>(std::clock() - c_start) / CLOCKS_PER_SEC << "s" << std::endl;
}
