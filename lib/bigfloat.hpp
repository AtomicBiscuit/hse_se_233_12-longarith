#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "bigint.hpp"

using digit_t = unsigned char;

class BigFloat : BigInt {
protected:
    uint32_t _pre;
public:
    BigFloat();

    BigFloat(const long double);

    BigFloat(const std::vector<digit_t>&, const uint32_t, const  uint32_t, const uint8_t);

    BigFloat(const BigInt&);

    BigFloat(const BigFloat&);

    const uint32_t precision() const;

    const uint32_t size() const;

    const uint8_t sign() const;

    std::string as_string() const;

    BigInt as_integer() const;

    BigFloat shift(const int32_t) const;

    BigFloat normalized(const BigFloat&) const;

    void clear();

    friend BigFloat operator+(const BigFloat&, const BigFloat&);

    friend BigFloat operator-(const BigFloat&);

    friend BigFloat operator-(const BigFloat&, const BigFloat&);

    friend BigFloat operator*(const BigFloat&, const BigFloat&);

    friend BigFloat operator/(const BigFloat&, const BigFloat&);

    friend std::ostream& operator<<(std::ostream&, const BigFloat&);

    BigFloat& operator=(const BigFloat&);

    friend bool operator>(const BigFloat&, const BigFloat&);

    friend bool operator>=(const BigFloat&, const BigFloat&);

    friend bool operator<(const BigFloat&, const BigFloat&);

    friend bool operator<=(const BigFloat&, const BigFloat&);

    friend bool operator==(const BigFloat& lh, const BigFloat& rh);
};

BigFloat operator ""_bf(long double);

BigFloat operator""_bf(unsigned long long);