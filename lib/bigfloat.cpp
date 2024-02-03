#include "bigfloat.h"
#include <cmath>
#include <deque>
#include <iostream>

BigFloat::BigFloat() : digits({0}), _size(1), _sign(Positive), _pre(0) {}

BigFloat::BigFloat(const long long val, uint32_t precision) {
    this->_sign = val < 0 ? Negative : Positive;
    this->_pre = (precision + _base_log10 - 1) / _base_log10;
    BigFloat temp = BigFloat(static_cast<unsigned long long>(std::abs(val)));
    for (int i = 0; i < this->precision() - precision; i++) {
        temp = temp * 10_bf;
    }
    this->digits = temp.digits;
    this->_size = temp._size;
}

BigFloat::BigFloat(const long double val) {
    this->_sign = val < 0 ? Negative : Positive;
    this->_size = 0;
    this->_pre = float_conversion_digits / _base_log10;
    this->digits = std::vector<digit_t>();
    long double _integral;
    long double fraction = modfl(fabsl(val), &_integral);
    auto integral = static_cast<unsigned long long>(floorl(_integral));
    std::vector<digit_t> temp;
    while (integral) {
        this->_size++;
        temp.push_back(integral % _base);
        integral /= _base;
    }
    this->digits = std::vector<digit_t>(temp.rbegin(), temp.rend());
    temp.clear();

    for (int32_t i = 0; i < float_conversion_digits + 1; i++) {
        fraction *= 10;
    }
    auto frac = static_cast<unsigned long long>(fraction + 1);
    frac /= 10;
    int32_t i = float_conversion_digits / _base_log10;
    while (i--) {
        temp.push_back(frac % _base);
        frac /= _base;
        this->_size++;
    }
    this->digits.insert(this->digits.end(), temp.rbegin(), temp.rend());
}

BigFloat::BigFloat(const unsigned long long val) {
    unsigned long long num = val;
    this->_sign = Positive;
    this->_size = 0;
    this->_pre = 0;
    std::vector<digit_t> temp;
    while (num) {
        this->_size++;
        temp.push_back(num % _base);
        num /= _base;
    }
    if (this->_size == 0) {
        this->_size = 1;
        temp.push_back(0);
    }
    this->digits = std::vector<digit_t>(temp.rbegin(), temp.rend());
}

BigFloat::BigFloat(const std::vector<digit_t> &dig, const uint32_t size, const uint32_t pre, const int8_t sign)
        : digits(dig), _size(size), _sign(sign), _pre(pre) {}

BigFloat::BigFloat(const BigFloat &obj) : digits(obj.digits), _size(obj._size), _sign(obj._sign), _pre(obj._pre) {}

uint32_t BigFloat::precision() const {
    return this->_pre * _base_log10;
}

uint32_t BigFloat::size() const {
    return this->_size * _base_log10;
}

int8_t BigFloat::sign() const {
    return this->_sign;
}

std::string BigFloat::as_string() const {
    std::string s_num;
    for (auto it = this->digits.begin(); it != this->digits.end(); it++) {
        if (it == this->digits.begin()) {
            s_num.append(std::to_string(*it));
        } else {
            auto temp = std::to_string(*it);
            temp.insert(temp.begin(), _base_log10 - temp.size(), '0');
            s_num.append(temp);
        }
    }
    if (_base_log10 * this->_pre > s_num.size()) {
        s_num.insert(s_num.begin(), _base_log10 * this->_pre - s_num.size(), '0');
    }
    s_num.insert(s_num.end() - _base_log10 * this->_pre, '.');
    return this->_sign == Positive ? s_num : "-" + s_num;
}

const std::vector<digit_t> &BigFloat::as_array() const {
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
            temp.digits = std::vector<digit_t>(temp.digits.begin(), temp.digits.begin() + temp._size);
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
    signed_digit_t sum = 0;
    signed_digit_t r;
    std::deque<digit_t> result(L._size, 0);
    for (int32_t i = 0; i < L._size; ++i) {
        sum += L._sign * static_cast<signed_digit_t>(L.digits[L._size - i - 1]);
        if (i < R._size) {
            sum += R._sign * static_cast<signed_digit_t>(R.digits[R._size - i - 1]);
        }
        r = sum % _base;
        result[L._size - i - 1] = (r * L._sign >= 0 ? std::abs(r) : _base - std::abs(r));
        sum = ((r * L._sign) < 0 ? (L._sign * -1) : (sum / _base));
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
    return {std::vector<digit_t>(result.begin(), result.end()), size, pre, sign};
}

BigFloat BigFloat::_pure_mul_dig(const BigFloat &lh, const digit_t &rh) {
    if (rh == 0) {
        return {};
    }
    digit_t sum = 0;
    uint32_t size = lh._size;
    std::deque<digit_t> result(size, 0);
    for (int32_t i = 0; i < size; ++i) {
        sum += static_cast<unsigned long long>(lh.digits[size - i - 1]) * rh;
        result[size - i - 1] = sum % _base;
        sum /= _base;
    }
    if (sum) {
        result.push_front(sum);
        size++;
    }
    return {std::vector<digit_t>(result.begin(), result.end()), size, lh._pre, BigFloat::Positive};
}

BigFloat BigFloat::_pure_mul(const BigFloat &lh, const BigFloat &rh) {
    int8_t sign = lh._sign == rh._sign ? BigFloat::Positive : BigFloat::Negative;
    BigFloat sum{};
    for (int32_t i = 0; i < rh._size; i++) {
        sum = sum + _pure_mul_dig(lh, rh.digits[rh._size - i - 1]).shift(i);
    }
    sum._sign = sign;
    sum._pre = std::max(lh._pre, rh._pre);
    return sum.shift(-1 * static_cast<int32_t>(std::min(lh._pre, rh._pre)));
}

BigFloat BigFloat::invert() const{
    if (this->_size == 1 && this->digits[0] == 0) {
        return {};
    }
    uint32_t dif = this->_size > this->_pre ? this->_size - this->_pre : 0;
    BigFloat D = {this->digits, this->_size, dif + this->_pre, Positive};
    BigFloat Xk = 1_bf + BigFloat(0, D.precision() + 10);
    BigFloat prev = 1_bf;
    do {
        prev = Xk;
        Xk = Xk + Xk * (1_bf - D * Xk);
    } while (Xk != prev);
    BigFloat answer = Xk.shift(-1 * static_cast<int32_t >(dif)).round(this->precision());
    return {answer.digits, answer._size, answer._pre, this->_sign};
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
    BigFloat res = lh * (rh + BigFloat(0, lh.precision() + BigFloat::_base_log10)).invert();
    return res.round(std::max(rh.precision(), lh.precision()));
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
        return std::strong_ordering::equal;
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
    uint32_t convert_precision = (precision + _base_log10 - 1) / _base_log10;
    if (convert_precision >= this->_pre) {
        return *this;
    }
    BigFloat tmp = this->shift(convert_precision + 1).as_integer();
    if (2 * tmp.digits.back() >= _base) {
        tmp = tmp + BigFloat(static_cast<unsigned long long>(_base));
    }
    return {tmp.shift(-1).as_array(), std::max(1u, tmp._size - 1), convert_precision, tmp._sign};
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
    BigFloat precision(0, num.precision() + 10);
    BigFloat eps(1, num.precision());
    BigFloat Xk = 1_bf + precision;
    BigFloat prev = 1_bf;
    BigFloat dec_deg = BigFloat(static_cast<unsigned long long>(deg - 1));
    BigFloat inv_deg = (1_bf + precision) / BigFloat(static_cast<unsigned long long>(deg));
    do {
        prev = Xk;
        Xk = inv_deg * (dec_deg * Xk + A / Xk.power(deg - 1));
    } while ((Xk - prev).abs() >= eps);
    BigFloat answer = Xk.round(num.precision());
    return answer.abs() * BigFloat(answer.sign(), 0);
}