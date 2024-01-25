#pragma once

#include <vector>
#include <cstdint>

using namespace std;

using digit_t = unsigned char;

class BigInt {
private:
    vector<digit_t> digits;
    uint32_t _size;
    uint8_t _sign;
    friend BigInt _add(const BigInt&, const BigInt&);
public:
    BigInt();

    BigInt(const vector<digit_t>&, const uint32_t, const uint8_t);

    BigInt(const BigInt&);

    const uint32_t MAX_SIZE = 50000;

    enum eSign { Positive, Negative };

    const uint32_t size() const;

    const uint8_t sign() const;

    const vector<digit_t>& as_array() const;

    string as_string() const;

    friend BigInt operator+(const BigInt&, const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);

    friend bool greater_with_absolute(const BigInt&, const BigInt&);
};