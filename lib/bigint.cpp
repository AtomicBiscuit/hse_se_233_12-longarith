#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cmath>

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

BigInt::BigInt() :digits({ 0 }), _size(1), _sign(Positive) {}

BigInt::BigInt(const vector<digit_t>& dig, const uint32_t size, const uint8_t sign) {
    cout << "check: dig = " << dig.size() << ", vector(dig) = " << vector<digit_t>(dig).size() << endl;
    this->digits = vector<digit_t>(dig);
    this->_size = size;
    this->_sign = sign;
}

BigInt::BigInt(const BigInt& obj) {
    if (obj._size > BigInt::MAX_SIZE) {
        throw length_error("Number is too big");
    }
    this->_size = obj.size();
    this->_sign = obj.sign();
    this->digits = vector<digit_t>(obj.digits);
}

const uint32_t BigInt::size() const {
    return this->_size;
}

const uint8_t BigInt::sign() const {
    return this->_sign;
}

const vector<digit_t>& BigInt::as_array() const {
    return this->digits;
}

string BigInt::as_string() const {
    string s = this->_sign == BigInt::Positive ? "" : "-";
    for (auto element : this->digits) {
        s.append(1, char(element) + '0');
    }
    return s;
}

BigInt _add(const BigInt& lh, const BigInt& rh) {
    int8_t sign1 = lh._sign == BigInt::Positive ? 1 : -1;
    int8_t sign2 = rh._sign == BigInt::Positive ? 1 : -1;
    int8_t sum = 0;
    int8_t r;
    uint32_t size = max(lh._size, rh._size);
    deque<digit_t> result(size, 0);
    for (int32_t i = 0; i < size; ++i) {
        if (i < lh._size) {
            sum += sign1 * lh.digits[lh._size - i - 1];
        }
        if (i < rh._size) {
            sum += sign2 * rh.digits[rh._size - i - 1];
        }
        r = sum % 10;
        result[size - i - 1] = (r * sign1 >= 0 ? abs(r) : 10 - abs(r));
        sum /= 10;
    }
    if (sum) {
        result.push_front(abs(sum));
        ++size;
    }
    while (size && result.front() == 0) {
        result.pop_front();
        --size;
    }
    return BigInt(vector<digit_t>(result.begin(), result.end()), size, sign1 == 1 ? BigInt::Positive : BigInt::Negative);
}

BigInt operator+(const BigInt& lh, const BigInt& rh) {
    if (greater_with_absolute(lh, rh)) {
        return _add(lh, rh);
    } else {
        return _add(rh, lh);
    }
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
    uint32_t size = max(lh._size, rh._size);
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