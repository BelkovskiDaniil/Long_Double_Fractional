#ifndef LONG_DOUBLE_BIG_DOUBLE_H
#define LONG_DOUBLE_BIG_DOUBLE_H

#include <iostream>
#include "big_integer.h"
#include "utilites.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class big_double {
    static const int BASE = 1000000000;

    big_integer numerator;
    big_integer denominator;

    bool negative;

public:
    class divide_by_zero: public std::exception {  };

    big_double();
    big_double(std::string);

    friend std::ostream& operator <<(std::ostream&, const big_double&);
    operator std::string() const;
    const big_double operator +() const;
    const big_double operator -() const;
    friend bool operator ==(const big_double&, const big_double&);
    friend bool operator <(const big_double&, const big_double&);
    friend bool operator !=(const big_double&, const big_double&);
    friend bool operator <=(const big_double&, const big_double&);
    friend bool operator >(const big_double&, const big_double&);
    friend bool operator >=(const big_double&, const big_double&);
    friend const big_double operator +(big_double, const big_double&);
    friend const big_double operator -(big_double, const big_double&);
    friend const big_double operator *(const big_double&, const big_double&);
    friend const big_double operator /(const big_double&, const big_double&);
};

#endif //LONG_DOUBLE_BIG_DOUBLE_H
