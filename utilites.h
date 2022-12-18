#ifndef LONG_DOUBLE_UTILITES_H
#define LONG_DOUBLE_UTILITES_H

#include "big_integer.h"

big_integer gcd(big_integer a, big_integer b);

big_integer lcm(big_integer a, big_integer b);

std::string to_decimal(big_integer numerator, big_integer denominator, bool negative);

#endif //LONG_DOUBLE_UTILITES_H
