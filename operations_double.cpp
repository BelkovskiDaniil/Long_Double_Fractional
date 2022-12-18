#include <iostream>
#include "big_integer.h"
#include "utilites.h"
#include "big_double.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

big_double::big_double() {
    negative = false;
}

big_double::big_double(std::string str) {
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

        int point = str.find('.');
        int number = str.length() - point - 1;
        std::string denum = "1";
        for (int i = 0; i < number; i++) {
            denum += "0";
        }

        denominator = denum;
        str.erase(str.find('.'), 1);
        numerator = str;
    }
}


std::ostream& operator <<(std::ostream& os, const big_double& bd) {
    std::cout << to_decimal(bd.numerator, bd.denominator, bd.negative);
    return os;
}

bool operator ==(const big_double& left, const big_double& right) {
    if ((left.numerator * left.denominator) == (right.numerator * right.denominator)) return true;
    else return false;
}

const big_double big_double::operator +() const {
    return big_double(*this);
}

const big_double big_double::operator -() const {
    big_double copy(*this);
    copy.negative = !copy.negative;
    return copy;
}

bool operator <(const big_double& left, const big_double& right) {
    if ((left.numerator * left.denominator) < (right.numerator * right.denominator)) return true;
    else return false;
}

bool operator !=(const big_double& left, const big_double& right) {
    return !(left == right);
}

bool operator <=(const big_double& left, const big_double& right) {
    return (left < right || left == right);
}

bool operator >(const big_double& left, const big_double& right) {
    return !(left <= right);
}

bool operator >=(const big_double& left, const big_double& right) {
    return !(left < right);
}

const big_double operator +(big_double left, const big_double& right) {

    big_integer lcm_local = lcm(left.denominator, right.denominator);
    big_integer multer_left = (lcm_local / left.denominator) * left.numerator;
    big_integer multer_right = (lcm_local / right.denominator) * right.numerator;
    left.denominator = lcm_local;
    left.numerator = multer_left + multer_right;
    return left;
}

const big_double operator -(big_double left, const big_double& right) {
    if (right.negative) return left + (-right);
    else if (left.negative) return -(-left + right);
    else if (left < right) return -(right - left);

    big_integer lcm_local = lcm(left.denominator, right.denominator);
    big_integer multer_left = (lcm_local / left.denominator) * left.numerator;
    big_integer multer_right = (lcm_local / right.denominator) * right.numerator;
    left.denominator = lcm_local;
    left.numerator = multer_left - multer_right;
    return left;
}

const big_double operator *(const big_double& left, const big_double& right) {
    big_double result;
    result.numerator = left.numerator * right.numerator;
    result.denominator = left.denominator * right.denominator;
    result.negative = left.negative != right.negative;
    return result;
}

const big_double operator /(const big_double& left, const big_double& right) {
    if (right == big_double("0.0")) throw big_double::divide_by_zero();
    big_double result;
    result.numerator = left.numerator * right.denominator;
    result.denominator = left.denominator * right.numerator;
    result.negative = left.negative != right.negative;
    return result;
}

big_double big_double::operator +=(const big_double &number) {
    return *this = *this + number;
}

big_double big_double::operator -=(const big_double &number) {
    return *this = *this - number;
}

big_double big_double::operator *=(const big_double &number) {
    return *this = *this - number;
}

big_double big_double::operator /=(const big_double &number) {
    return *this = *this - number;
}

const big_double big_double::operator++() {
    big_double number("1.0");
    return (*this += number);
}

const big_double big_double::operator ++(int) {
    big_double number("1.0");
    *this += number;
    return *this - number;
}

const big_double big_double::operator --() {
    big_double number("1.0");
    return *this -= number;
}

const big_double big_double::operator --(int) {
    big_double number("1.0");
    *this -= number;
    return *this + number;
}