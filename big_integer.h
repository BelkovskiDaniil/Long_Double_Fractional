#ifndef LONG_DOUBLE_BIG_INTEGER_H
#define LONG_DOUBLE_BIG_INTEGER_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class big_integer {
    static const int BASE = 1000000000;

    std::vector<int> numbers;

    bool negative;

    void del_zeroes();
    void shift();

public:
    class divide_by_zero: public std::exception {  };

    big_integer();
    big_integer(std::string);
    big_integer(signed int);

    friend std::ostream& operator <<(std::ostream&, const big_integer&);
    operator std::string() const;
    const big_integer operator +() const;
    const big_integer operator -() const;
    const big_integer operator ++();
    const big_integer operator ++(int);
    const big_integer operator --();
    const big_integer operator --(int);
    friend bool operator ==(const big_integer&, const big_integer&);
    friend bool operator <(const big_integer&, const big_integer&);
    friend bool operator !=(const big_integer&, const big_integer&);
    friend bool operator <=(const big_integer&, const big_integer&);
    friend bool operator >(const big_integer&, const big_integer&);
    friend bool operator >=(const big_integer&, const big_integer&);
    friend const big_integer operator +(big_integer, const big_integer&);
    big_integer& operator +=(const big_integer&);
    friend const big_integer operator -(big_integer, const big_integer&);
    big_integer& operator -=(const big_integer&);
    friend const big_integer operator *(const big_integer&, const big_integer&);
    big_integer& operator *=(const big_integer&);
    friend const big_integer operator /(const big_integer&, const big_integer&);
    big_integer& operator /=(const big_integer&);
    friend const big_integer operator %(const big_integer&, const big_integer&);
    big_integer& operator %=(const big_integer&);
    std::string to_string() const;
};

#endif //LONG_DOUBLE_BIG_INTEGER_H
