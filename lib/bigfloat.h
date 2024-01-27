#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "bigint.h"

class BigFloat : BigInt {
protected:
    uint32_t _pre;
public:
    BigFloat();

    explicit BigFloat(long double);

    explicit BigFloat(unsigned long long);

    BigFloat(const std::vector<unsigned char>&, uint32_t,  uint32_t, uint8_t);

    explicit BigFloat(const BigInt&);

    BigFloat(const BigFloat&);

    uint32_t precision() const;

    uint32_t size() const;

    uint8_t sign() const;

    std::string as_string() const;

    const std::vector<unsigned char>& as_array() const;

    BigInt as_integer() const;

    BigInt shift(int32_t) const;

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
