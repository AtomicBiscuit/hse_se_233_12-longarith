#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "bigint.hpp"

using namespace std;

using digit_t = unsigned char;

class BigFloat : BigInt {
protected:
    uint32_t _pre;
public:
    BigFloat();
    BigFloat(const vector<digit_t>&, const uint32_t, const  uint32_t, const uint8_t);
    BigFloat(const BigInt&);
    BigFloat(const BigFloat&);

    const uint32_t precision() const;

    string as_string() const;

    BigFloat inversed() const;

    void clear();

    friend BigFloat operator+(const BigFloat&, const BigFloat&);

    friend BigFloat operator-(const BigFloat&, const BigFloat&);

    friend BigFloat operator*(const BigFloat&, const BigFloat&);

    friend BigFloat operator/(const BigFloat&, const BigFloat&);

    friend ostream& operator<<(ostream&, const BigFloat&);

    BigFloat& operator=(const BigFloat&);

    friend bool operator>(const BigFloat&, const BigFloat&);

    friend bool operator==(const BigFloat& lh, const BigFloat& rh);
};