#include "bigfloat.h"
#include <cmath>
#include <deque>
#include <iostream>

BigFloat::BigFloat() : digits({0}), _size(1), _sign(Positive), _pre(0) {}

BigFloat::BigFloat(const long double val) {
    this->_sign = val < 0 ? BigFloat::Negative : BigFloat::Positive;
    this->_size = 0;
    this->_pre = 0;
    this->digits = std::vector<unsigned char>();
    long double _integral;
    long double fraction = modfl(fabsl(val), &_integral);
    auto integral = static_cast<unsigned long long>(floorl(_integral));
    std::vector<unsigned char> temp;
    while (integral) {
        this->_size++;
        temp.push_back(integral % 10);
        integral /= 10;
    }
    this->digits = std::vector<unsigned char>(temp.rbegin(), temp.rend());
    temp.clear();
    for (int32_t i = 0; i < BigFloat::float_conversion_digits + 1; i++) {
        fraction *= 10;
    }
    auto frac =  static_cast<unsigned long long>(fraction + 0.1);
    frac /= 10;
    while (frac) {
        temp.push_back(frac % 10);
        frac /= 10;
        this->_size++;
        this->_pre++;
    }

    this->digits.insert(this->digits.end(), temp.rbegin(), temp.rend());
}

BigFloat::BigFloat(const unsigned long long val) {
    unsigned long long num = val;
    this->_sign = BigFloat::Positive;
    this->_size = 0;
    this->_pre = 0;
    std::vector<unsigned char> temp;
    while (num) {
        this->_size++;
        temp.push_back(num % 10);
        num /= 10;
    }
    if (this->_size == 0) {
        this->_size = 1;
        temp.push_back(0);
    }
    this->digits = std::vector<unsigned char>(temp.rbegin(), temp.rend());
}

BigFloat::BigFloat(const std::vector<unsigned char> &dig, const uint32_t size, const uint32_t pre, const int8_t sign)
        : digits(dig), _size(size), _sign(sign), _pre(pre) {}

BigFloat::BigFloat(const BigFloat &obj) : digits(obj.digits), _size(obj._size), _sign(obj._sign), _pre(obj._pre) {}

uint32_t BigFloat::precision() const {
    return this->_pre;
}

uint32_t BigFloat::size() const {
    return this->_size;
}

int8_t BigFloat::sign() const {
    return this->_sign;
}

std::string BigFloat::as_string() const {
    std::string s = this->_sign == BigFloat::Positive ? "" : "-";
    s.append(std::string(this->_pre > this->_size ? this->_pre - this->_size : 0, '0'));
    for (auto element: this->digits) {
        s.push_back(static_cast<char>(element + '0'));
    }
    s.insert(s.end() - this->_pre, '.');
    return s;
}

const std::vector<unsigned char> &BigFloat::as_array() const {
    return this->digits;
}

BigFloat BigFloat::as_integer() const {
    if (this->_pre >= this->_size) {
        return {};
    }
    return {std::vector(this->digits.begin(), this->digits.end() - this->_pre), this->_size - this->_pre, 0,
            this->_sign};
}

void BigFloat::clear() {
    this->_size = 1;
    this->_pre = 0;
    this->_sign = BigFloat::Positive;
    this->digits.clear();
    this->digits.push_back(0);
}

BigFloat BigFloat::shift(int32_t count) const {
    BigFloat temp(*this);
    if (count == 0) {
        return temp;
    }
    if (count > 0) {
        temp._size += count;
        temp.digits.insert(temp.digits.end(), count, 0);
    } else {
        if (temp._size <= std::abs(count)) {
            temp.clear();
            return temp;
        }
        temp._size += count;
        if (count == -1) {
            temp.digits.pop_back();
        } else {
            temp.digits = std::vector<unsigned char>(temp.digits.begin(), temp.digits.begin() + temp._size);
        }
    }
    return temp;
}

BigFloat BigFloat::normalized(const BigFloat &other) const {
    return this->shift(static_cast<int32_t>(std::max(this->_pre, other._pre))).as_integer();
}

BigFloat BigFloat::abs() const {
    return {this->digits, this->_size, this->_pre, BigFloat::Positive};
}

BigFloat BigFloat::_pure_add(const BigFloat &lh, const BigFloat &rh, const uint32_t &pre) {
    BigFloat L, R;
    if (lh.abs() > rh.abs()) {
        L = lh;
        R = rh;
    } else {
        R = lh;
        L = rh;
    }
    int32_t sum = 0;
    int32_t r;
    std::deque<unsigned char> result(L._size, 0);
    for (int32_t i = 0; i < L._size; ++i) {
        sum += L._sign * L.digits[L._size - i - 1];
        if (i < R._size) {
            sum += R._sign * R.digits[R._size - i - 1];
        }
        r = sum % 10;
        result[L._size - i - 1] = (r * L._sign >= 0 ? std::abs(r) : 10 - std::abs(r));
        sum = ((r * L._sign) < 0 ? (L._sign * -1) : (sum / 10));
    }
    uint32_t size = L._size;
    if (sum) {
        result.push_front(std::abs(sum));
        size++;
    }
    while (size && result.front() == 0) {
        result.pop_front();
        --size;
    }
    int8_t sign = L._sign;
    if (size == 0) {
        size = 1;
        sign = 1;
        result.push_back(0);
    }
    return {std::vector<unsigned char>(result.begin(), result.end()), size, pre, sign};
}

BigFloat BigFloat::_pure_mul_dig(const BigFloat &lh, const uint8_t &rh) {
    if (rh == 0) {
        return {};
    }
    int8_t sum = 0;
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
    return {std::vector<unsigned char>(result.begin(), result.end()), size, lh._pre, lh._sign};
}

BigFloat BigFloat::_pure_mul(const BigFloat &lh, const BigFloat &rh) {
    int8_t sign = lh._sign == rh._sign ? BigFloat::Positive : BigFloat::Negative;
    BigFloat sum{};
    sum._sign = lh._sign;
    for (int32_t i = 0; i < rh._size; i++) {
        sum = sum + _pure_mul_dig(lh, rh.digits[rh._size - i - 1]).shift(i);
    }
    sum._sign = sign;
    sum._pre = std::max(lh._pre, rh._pre);
    return sum.shift(-1 * static_cast<int32_t>(std::min(lh._pre, rh._pre)));
}

BigFloat BigFloat::div(const BigFloat &lh, const BigFloat &rh) {
    BigFloat num = lh.abs().as_integer();
    BigFloat den = rh.abs().as_integer();

    if (den._size > num._size) {
        return {};
    }
    if (den._size == 1 && den.digits[0] == 0) {
        return {};
    }
    BigFloat sum{};
    BigFloat add = BigFloat(std::vector<unsigned char>(1, 1), 1, 0, BigFloat::Positive);

    add = add.shift(static_cast<int32_t>(num._size - den._size));
    den = den.shift(static_cast<int32_t>(num._size - den._size));

    while (den._size != 1 || den.digits[0] != 0) {
        num = num - den;
        if (num._sign == BigFloat::Positive) {
            sum = sum + add;
        } else {
            num = num + den;
            den = den.shift(-1);
            add = add.shift(-1);
        }
    }

    sum._sign = lh._sign == rh._sign ? BigFloat::Positive : BigFloat::Negative;
    return sum;
}


BigFloat operator+(const BigFloat &lh, const BigFloat &rh) {
    return BigFloat::_pure_add(lh.normalized(rh), rh.normalized(lh), std::max(lh._pre, rh._pre));
}

BigFloat operator-(const BigFloat &lh) {
    return {lh.digits, lh._size, lh._pre, static_cast<int8_t>(lh._sign * -1)};
}

BigFloat operator-(const BigFloat &lh, const BigFloat &rh) {
    return BigFloat::_pure_add(lh.normalized(rh), -rh.normalized(lh), std::max(lh._pre, rh._pre));
}

BigFloat operator*(const BigFloat &lh, const BigFloat &rh) {
    return BigFloat::_pure_mul(lh, rh);
}

BigFloat operator/(const BigFloat &lh, const BigFloat &rh) {
    BigFloat L = lh.normalized(rh).shift(static_cast<int32_t>(std::max(lh._pre, rh._pre)));
    BigFloat R = rh.normalized(lh);
    BigFloat res = BigFloat::div(L, R);
    res._pre = std::max(lh._pre, rh._pre);
    return res;
}

std::ostream &operator<<(std::ostream &_os, const BigFloat &obj) {
    return _os << obj.as_string();
}

BigFloat &BigFloat::operator=(const BigFloat &rh) {
    this->_sign = rh._sign;
    this->_size = rh._size;
    this->_pre = rh._pre;
    this->digits = rh.digits;
    return *this;
}

std::strong_ordering BigFloat::operator<=>(const BigFloat &rh) const {
    if (this->_sign != rh._sign) {
        if (this->_sign == BigFloat::Positive) {
            return std::strong_ordering::greater;
        }
        return std::strong_ordering::less;
    }
    BigFloat L = this->normalized(rh);
    BigFloat R = rh.normalized(*this);
    if (L._size > R._size) {
        return std::strong_ordering::greater;
    } else if (L._size < R._size) {
        return std::strong_ordering::less;
    }
    int8_t bigger = 0;
    for (uint32_t i = 0; i < L._size; ++i) {
        if (this->digits[i] > rh.digits[i]) {
            bigger = BigFloat::Positive;
            break;
        } else if (this->digits[i] < rh.digits[i]) {
            bigger = BigFloat::Negative;
            break;
        }
    }
    if (bigger == 0) {
        return std::strong_ordering::equivalent;
    }
    if (bigger == this->_sign) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::less;
}

bool BigFloat::operator==(const BigFloat &rh) const {
    if (this->_sign != rh._sign) {
        return false;
    }
    BigFloat L = this->normalized(rh);
    BigFloat R = rh.normalized(*this);
    if (L._size != R._size) {
        return false;
    }
    for (uint32_t i = 0; i < L._size; ++i) {
        if (this->digits[i] != rh.digits[i]) {
            return false;
        }
    }
    return true;
}

BigFloat BigFloat::power(const uint32_t &deg) const {
    return ::power(*this, deg);
}

BigFloat BigFloat::root(const uint32_t &deg) const {
    return ::root(*this, deg);
}

BigFloat BigFloat::round(const uint32_t &precision) const {
    if (precision >= this->_pre) {
        return *this;
    }
    BigFloat tmp = this->shift(precision + 1).as_integer();
    if(tmp.digits.back() >= 5){
        tmp = tmp + 10_bf;
    }
    return {tmp.shift(-1).as_array(), std::max(1u, tmp._size - 1), precision, tmp._sign};
}

BigFloat operator ""_bf(long double data) {
    return BigFloat(data);
}

BigFloat operator ""_bf(unsigned long long data) {
    return BigFloat(data);
}

BigFloat power(const BigFloat &num, const uint32_t &deg) {
    if (deg == 0) {
        return 1_bf;
    } else if (deg == 1) {
        return num;
    } else if (deg % 2 == 0) {
        BigFloat tmp = power(num, deg / 2);
        return tmp * tmp;
    }
    return num * power(num, deg - 1);
}

BigFloat root(const BigFloat &num, const uint32_t &deg) {
    if (num.sign() == BigFloat::Negative && deg % 2 == 0) {
        return {};
    }
    if (deg == 0) {
        return 1_bf;
    }
    if (deg == 1) {
        return num;
    }
    BigFloat A = num.abs();
    BigFloat precision({0}, 1, num.precision() + 10, BigFloat::Positive);
    BigFloat Xk = 1_bf + precision;
    BigFloat prev = 1_bf;
    BigFloat dec_deg = BigFloat(static_cast<unsigned long long>(deg - 1));
    BigFloat inv_deg = (1_bf + precision) / BigFloat(static_cast<unsigned long long>(deg));
    do {
        prev = Xk;
        Xk = inv_deg * (dec_deg * Xk + A / Xk.power(deg - 1));
    } while (Xk != prev);
    BigFloat answer = Xk.round(num.precision());
    return {answer.as_array(), answer.size(), answer.precision(), num.sign()};
}