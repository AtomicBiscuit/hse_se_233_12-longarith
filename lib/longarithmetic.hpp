#pragma once

#include <vector>
#include <cstdint>

using namespace std;

using digit_t = unsigned char;

class BigInt {
    BigInt();

    BigInt(const vector<digit_t>&, const uint32_t, const uint8_t);

    BigInt(const BigInt&);

    const uint32_t size() const;

    const uint8_t sign() const;

    const vector<digit_t>& as_array() const;

    friend BigInt operator+(const BigInt&, const BigInt&);
};