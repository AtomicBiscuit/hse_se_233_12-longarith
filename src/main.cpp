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
        calc_pi(precision);
    } else {
        cout << "Bye" << endl;
    }
    return 0;
}