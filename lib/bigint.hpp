#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

using digit_t = unsigned char;

class BigInt {
protected:
    std::vector<digit_t> digits;
    uint32_t _size;
    uint8_t _sign;
    friend BigInt _add(const BigInt&, const BigInt&);
public:
    BigInt();

    BigInt(const std::vector<digit_t>&, const uint32_t, const uint8_t);

    BigInt(const BigInt&);

    const uint32_t MAX_SIZE = 50000;

    enum eSign { Positive, Negative };

    const uint32_t size() const;

    const uint8_t sign() const;

    const std::vector<digit_t>& as_array() const;

    std::string as_string() const;

    BigInt shift(const int32_t) const;

    void clear();

    friend BigInt operator+(const BigInt&, const BigInt&);

    friend BigInt operator-(const BigInt&);

    friend BigInt operator-(const BigInt&, const BigInt&);

    friend BigInt operator*(const BigInt&, const BigInt&);

    friend BigInt operator*(const BigInt&, const uint8_t&);

    friend BigInt operator/(const BigInt&, const BigInt&);

    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    BigInt& operator=(const BigInt&);

    friend bool operator>(const BigInt&, const BigInt&);

    friend bool operator==(const BigInt& lh, const BigInt& rh);

    friend bool greater_with_absolute(const BigInt&, const BigInt&);
};