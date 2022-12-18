#include <iostream>
#include "big_integer.h"
#include "big_double.h"

int main() {

    big_double a("-10.0");

    big_double b("15.0");

    big_double d("0.0");

    big_double c = a / b;

    std::cout << c << std::endl;

    big_double v = c * b;

    std::cout << (c * b) << std::endl;

    std::cout << (d / b) << std::endl;

    return 0;
}