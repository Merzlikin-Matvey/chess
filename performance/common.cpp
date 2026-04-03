#include "main.h"

std::string pretty_number(long long n) {
    if (n < 10'000) {
        return std::to_string(n);
    }
    if (n < 10'000'000) {
        return std::to_string(n / 1'000) + "K";
    }
    if (n < 10'000'000'000) {
        return std::to_string(n / 1'000'000) + "M";
    }
    return std::to_string(n / 1'000'000'000) + "B";
}

std::string pretty_number(double n) {
    return pretty_number(static_cast<long long>(n));
}