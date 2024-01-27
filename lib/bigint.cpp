#include "bigint.h"
#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

BigInt::BigInt() :digits({ 0 }), _size(1), _sign(Positive) {}

BigInt::BigInt(const std::vector<unsigned char>& dig, const uint32_t size, const uint8_t sign) {
    if (size > BigInt::MAX_SIZE) {
        throw std::length_error("Number is too big");
    }
    this->digits = dig;
    this->_size = size;
    this->_sign = sign;
}

BigInt::BigInt(const BigInt& obj) :_size(obj._size), _sign(obj._sign), digits(obj.digits) {}

uint32_t BigInt::size() const {
    return this->_size;
}

uint8_t BigInt::sign() const {
    return this->_sign;
}

const std::vector<unsigned char>& BigInt::as_array() const {
    return this->digits;
}

std::string BigInt::as_string() const {
    std::string s = this->_sign == BigInt::Positive ? "" : "-";
    for (auto element : this->digits) {
        s.append(1, static_cast<char>(element + '0'));
    }
    return s;
}

BigInt BigInt::shift(const int32_t count) const {
    BigInt temp(*this);
    if (count == 0) {
        return temp;
    }
    if (count > 0) {
        temp._size += count;
        if (temp._size > BigInt::MAX_SIZE) {
            throw std::length_error("Number is too big");
        }
        temp.digits.insert(temp.digits.end(), count, 0);
    } else {
        if (temp._size <= abs(count)) {
            temp.clear();
            return temp;
        }
        temp._size += count;
        temp.digits = std::vector<unsigned char>(temp.digits.begin(), temp.digits.begin() + temp._size);
    }
    return temp;
}

void BigInt::clear() {
    this->_size = 1;
    this->_sign = BigInt::Positive;
    this->digits.clear();
    this->digits.push_back(0);
}

BigInt add(const BigInt& lh, const BigInt& rh) {
    int32_t sign1 = lh._sign == BigInt::Positive ? 1 : -1;
    int32_t sign2 = rh._sign == BigInt::Positive ? 1 : -1;
    int32_t sum = 0;
    int32_t r;
    uint32_t size = std::max(lh._size, rh._size);
    std::deque<unsigned char> result(size, 0);
    for (int32_t i = 0; i < size; ++i) {
        if (i < lh._size) {
            sum += sign1 * lh.digits[lh._size - i - 1];
        }
        if (i < rh._size) {
            sum += sign2 * rh.digits[rh._size - i - 1];
        }
        r = sum % 10;
        result[size - i - 1] = (r * sign1 >= 0 ? abs(r) : 10 - abs(r));
        if (r * sign1 < 0) {
            sum = sign1 * -1;
        } else {
            sum = sum / 10;
        }
    }
    if (sum) {
        result.push_front(abs(sum));
        ++size;
    }
    while (size && result.front() == 0) {
        result.pop_front();
        --size;
    }
    if (size == 0) {
        size = 1;
        sign1 = 1;
        result.push_back(0);
    }
    uint8_t sign = sign1 == 1 ? BigInt::Positive : BigInt::Negative;
    return {std::vector<unsigned char>(result.begin(), result.end()), size, sign};
}

BigInt operator+(const BigInt& lh, const BigInt& rh) {
    if (greater_with_absolute(lh, rh)) {
        return add(lh, rh);
    } else {
        return add(rh, lh);
    }
}

BigInt operator*(const BigInt& lh, const uint8_t& rh) {
    if (rh >= 10) {
        throw std::domain_error("numeric operand must be in [0, 9]");
    }
    if (rh == 0) {
        return {};
    }
    uint8_t sum = 0;
    uint32_t size = lh._size;
    std::deque<unsigned char> result(size, 0);
    for (int32_t i = 0; i < size; ++i) {
        sum += lh.digits[size - i - 1] * rh;
        result[size - i - 1] = sum % 10;
        sum /= 10;
    }
    if (sum) {
        result.push_front(sum);
        size++;
    }
    return {std::vector<unsigned char>(result.begin(), result.end()), size, lh._sign};
}

BigInt operator*(const BigInt& lh, const BigInt& rh) {
    uint8_t sign = lh._sign == rh._sign ? BigInt::Positive : BigInt::Negative;
    BigInt sum = BigInt();
    sum._sign = lh._sign;
    for (int32_t i = 0; i < rh._size; i++) {
        sum = sum + (lh * rh.digits[rh._size - i - 1]).shift(i);
    }
    sum._sign = sign;
    return sum;
}

BigInt& BigInt::operator=(const BigInt& rh) {
    this->_sign = rh.sign();
    this->_size = rh.size();
    this->digits = rh.digits;
    return *this;
}

BigInt operator-(const BigInt& obj) {
    BigInt temp = BigInt(obj);
    temp._sign = (temp._sign == BigInt::Positive ? BigInt::Negative : BigInt::Positive);
    return temp;
}

BigInt operator-(const BigInt& lh, const BigInt& rh) {
    if (greater_with_absolute(lh, rh)) {
        return add(lh, -rh);
    } else {
        return add(-rh, lh);
    }
}

BigInt operator/(const BigInt& lh, const BigInt& rh) {
    if (rh._size > lh._size) {
        return {};
    }
    if (rh._size == 1 && rh.digits[0] == 0) {
        return {};
    }

    BigInt sum = BigInt();
    BigInt addition = BigInt(std::vector<unsigned char>(1, 1), 1, BigInt::Positive);
    BigInt numerator(lh.as_array(), lh.size(), BigInt::Positive);
    BigInt denominator(rh.as_array(), rh.size(), BigInt::Positive);

    denominator = denominator.shift(static_cast<int32_t>(lh._size - rh._size));
    addition = addition.shift(static_cast<int32_t>(lh._size - rh._size));

    while (denominator._size != 1 || denominator.digits[0] != 0) {
        numerator = numerator - denominator;
        if (numerator._sign == BigInt::Positive) {
            sum = sum + addition;
        } else {
            numerator = numerator + denominator;
            denominator = denominator.shift(-1);
            addition = addition.shift(-1);
        }
    }

    sum._sign = lh._sign == rh._sign ? BigInt::Positive : BigInt::Negative;
    return sum;
}

std::ostream& operator<<(std::ostream& _os, const BigInt& obj) {
    return _os << obj.as_string();
}

bool greater_with_absolute(const BigInt& lh, const BigInt& rh) {
    if (lh._size != rh._size) {
        return lh._size > rh._size;
    }
    int8_t bigger = -1;
    uint32_t size = lh._size;
    for (int32_t i = 0; i < size; ++i) {
        if (lh.digits[i] > rh.digits[i]) {
            return true;
        } else if (lh.digits[i] < rh.digits[i]) {
            return false;
        }
    }
    return false;
}

bool operator>(const BigInt& lh, const BigInt& rh) {
    if (lh._sign != rh._sign) {
        return lh._sign == BigInt::Positive;
    }
    if (lh._size != rh._size) {
        if (lh._sign == BigInt::Positive) {
            return lh._size > rh._size;
        } else {
            return lh._size < rh._size;
        }
    }
    int8_t bigger = -1;
    uint32_t size = std::max(lh._size, rh._size);
    for (int32_t i = 0; i < size; ++i) {
        if (lh.digits[i] > rh.digits[i]) {
            bigger = BigInt::Positive;
            break;
        } else if (lh.digits[i] < rh.digits[i]) {
            bigger = BigInt::Negative;
            break;
        }
    }
    if (bigger == -1) {
        return false;
    }
    return bigger == lh._sign;
}

bool operator==(const BigInt& lh, const BigInt& rh) {
    if (lh._sign != rh._sign) {
        return false;
    }
    if (lh._size != rh._size) {
        return false;
    }
    uint32_t size = lh._size;
    for (uint32_t i = 0; i < size; ++i) {
        if (lh.digits[i] != rh.digits[i]) {
            return false;
        }
    }
    return true;
}
