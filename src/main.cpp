#include <iostream>
#include "pi.h"

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
        cout << "Enter precision: ";
        uint32_t precision;
        std::cin >> precision;
        long double time_spend = calc_pi(precision);
        std::cout << "Time spend: " << time_spend << "s" << std::endl;
    } else {
        cout << "Bye" << endl;
    }
    return 0;
}