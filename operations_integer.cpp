#include "big_integer.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

big_integer::big_integer() {
    negative = false;
}

big_integer::big_integer(std::string str) {
    if (str.length() == 0) {
        negative = false;
    }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            negative = true;
        }
        else {
            negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                numbers.push_back(atoi(str.substr(0, i).c_str()));
            else
                numbers.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        del_zeroes();
    }
}

void big_integer::del_zeroes() {
    while (numbers.size() > 1 && numbers.back() == 0) {
        numbers.pop_back();
    }

    if (numbers.size() == 1 && numbers[0] == 0) negative = false;
}

std::ostream& operator <<(std::ostream& os, const big_integer& bi) {
    if (bi.numbers.empty()) os << 0;
    else {
        if (bi.negative) os << '-';
        os << bi.numbers.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi.numbers.size()) - 2; i >= 0; --i) os << std::setw(9) << bi.numbers[i];
        os.fill(old_fill);
    }

    return os;
}

bool operator ==(const big_integer& left, const big_integer& right) {
    if (left.negative != right.negative) return false;
    if (left.numbers.empty()) {
        if (right.numbers.empty() || (right.numbers.size() == 1 && right.numbers[0] == 0)) return true;
        else return false;
    }

    if (right.numbers.empty()) {
        if (left.numbers.size() == 1 && left.numbers[0] == 0) return true;
        else return false;
    }

    if (left.numbers.size() != right.numbers.size()) return false;
    for (size_t i = 0; i < left.numbers.size(); ++i) if (left.numbers[i] != right.numbers[i]) return false;

    return true;
}

const big_integer big_integer::operator +() const {
    return big_integer(*this);
}

const big_integer big_integer::operator -() const {
    big_integer copy(*this);
    copy.negative = !copy.negative;
    return copy;
}

bool operator <(const big_integer& left, const big_integer& right) {
    if (left == right) return false;
    if (left.negative) {
        if (right.negative) return ((-right) < (-left));
        else return true;
    }
    else if (right.negative) return false;
    else {
        if (left.numbers.size() != right.numbers.size()) {
            return left.numbers.size() < right.numbers.size();
        }
        else {
            for (long long i = left.numbers.size() - 1; i >= 0; --i) {
                if (left.numbers[i] != right.numbers[i]) return left.numbers[i] < right.numbers[i];
            }

            return false;
        }
    }
}

bool operator !=(const big_integer& left, const big_integer& right) {
    return !(left == right);
}

bool operator <=(const big_integer& left, const big_integer& right) {
    return (left < right || left == right);
}

bool operator >(const big_integer& left, const big_integer& right) {
    return !(left <= right);
}

bool operator >=(const big_integer& left, const big_integer& right) {
    return !(left < right);
}

const big_integer operator +(big_integer left, const big_integer& right) {
    if (left.negative) {
        if (right.negative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right.negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left.numbers.size(), right.numbers.size()) || carry != 0; ++i) {
        if (i == left.numbers.size()) left.numbers.push_back(0);
        left.numbers[i] += carry + (i < right.numbers.size() ? right.numbers[i] : 0);
        carry = left.numbers[i] >= big_integer::BASE;
        if (carry != 0) left.numbers[i] -= big_integer::BASE;
    }

    return left;
}

big_integer& big_integer::operator +=(const big_integer& value) {
    return *this = (*this + value);
}

const big_integer big_integer::operator++() {
    return (*this += 1);
}

big_integer::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

big_integer::big_integer(signed int i) {
    if (i < 0) negative = true;
    else negative = false;
    numbers.push_back(std::abs(i) % big_integer::BASE);
    i /= big_integer::BASE;
    if (i != 0) numbers.push_back(std::abs(i));
}

const big_integer big_integer::operator ++(int) {
    *this += 1;
    return *this - 1;
}

const big_integer big_integer::operator --() {
    return *this -= 1;
}

const big_integer big_integer::operator --(int) {
    *this -= 1;
    return *this + 1;
}

const big_integer operator -(big_integer left, const big_integer& right) {
    if (right.negative) return left + (-right);
    else if (left.negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right.numbers.size() || carry != 0; ++i) {
        left.numbers[i] -= carry + (i < right.numbers.size() ? right.numbers[i] : 0);
        carry = left.numbers[i] < 0;
        if (carry != 0) left.numbers[i] += big_integer::BASE;
    }

    left.del_zeroes();
    return left;
}

big_integer& big_integer::operator -=(const big_integer& value) {
    return *this = (*this - value);
}

const big_integer operator *(const big_integer& left, const big_integer& right) {
    big_integer result;
    result.numbers.resize(left.numbers.size() + right.numbers.size());
    for (size_t i = 0; i < left.numbers.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.numbers.size() || carry != 0; ++j) {
            long long cur = result.numbers[i + j] +
                            left.numbers[i] * 1LL * (j < right.numbers.size() ? right.numbers[j] : 0) + carry;
            result.numbers[i + j] = static_cast<int>(cur % big_integer::BASE);
            carry = static_cast<int>(cur / big_integer::BASE);
        }
    }

    result.negative = left.negative != right.negative;
    result.del_zeroes();
    return result;
}

big_integer& big_integer::operator *=(const big_integer& value) {
    return *this = (*this * value);
}

void big_integer::shift() {
    if (numbers.size() == 0) {
        numbers.push_back(0);
        return;
    }
    numbers.push_back(numbers[numbers.size() - 1]);
    for (size_t i = numbers.size() - 2; i > 0; --i) numbers[i] = numbers[i - 1];
    numbers[0] = 0;
}

const big_integer operator /(const big_integer& left, const big_integer& right) {
    if (right == 0) throw big_integer::divide_by_zero();
    big_integer b = right;
    b.negative = false;
    big_integer result, current;
    result.numbers.resize(left.numbers.size());
    for (long long i = static_cast<long long>(left.numbers.size()) - 1; i >= 0; --i) {
        current.shift();
        current.numbers[0] = left.numbers[i];
        current.del_zeroes();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result.numbers[i] = x;
        current = current - b * x;
    }

    result.negative = left.negative != right.negative;
    result.del_zeroes();
    return result;
}

big_integer& big_integer::operator /=(const big_integer& value) {
    return *this = (*this / value);
}

const big_integer operator %(const big_integer& left, const big_integer& right) {
    big_integer result = left - (left / right) * right;
    if (result.negative) result += right;
    return result;
}

big_integer& big_integer::operator %=(const big_integer& value) {
    return *this = (*this % value);
}

std::string big_integer::to_string() const {
    std::string result = negative ? "-" : "";

    result += std::to_string(numbers.empty() ? 0 : numbers.back());
    for (int i = (int)numbers.size() - 2; i >= 0; --i) {
        std::string tmp = std::to_string(numbers[i]);
        for (int j = 0; j < BASE - tmp.size(); ++j) result.append("0");
        result += tmp;
    }
    return result;
}
