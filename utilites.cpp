#include "big_integer.h"
#include "big_double.h"
#include <map>

 big_integer gcd(big_integer a, big_integer b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return gcd(a % b, b);
    return gcd(a, b % a);
}

big_integer lcm(big_integer a, big_integer b) {
    return (a * b) / lcm(a, b);
}

std::string to_decimal(big_integer numerator, big_integer denominator, bool negative) {
    std::string answer = "";
    if (numerator == 0) {
        answer = "0";
        return answer;
    }
    typedef std::pair<big_integer, big_integer> key;
    big_integer reminder = numerator * 10, div = denominator;
    std::vector<key> counter;
    size_t index = -1;
    while (true) {
        key act(reminder / div, reminder);
        for (size_t i = 0; i < counter.size(); ++i)
            if (counter[i].first == act.first && counter[i].second == act.second) {
                index = i;
                break;
            }
        if (index != -1) break;
        counter.push_back(act);
        reminder = (reminder % div) * 10;
    }

    big_integer before_dot = numerator / denominator;
    std::string string_before_dot = before_dot.to_string();
    std::string string_old;
    for (size_t i = 0; i < std::min(index, counter.size()); ++i)
        string_old += counter[i].first.to_string();
    
    std::string period;
    for (size_t i = index; i < counter.size(); ++i) {
        period += counter[i].first.to_string();
    }

    if (string_old.empty()) {
        if (negative == true) answer = "-" + string_before_dot + ".";
        else answer = string_before_dot + ".";
    }

    else {
        if (negative == true) answer = "-" + string_before_dot + "." + string_old.substr(string_before_dot.length());
        else answer = string_before_dot + "." + string_old.substr(string_before_dot.length());
    }
    if (period != "0") answer += "(" + period + ")";
    return answer;
}


