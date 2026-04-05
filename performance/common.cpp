#include "main.h"


std::string round(std::string s) {
    if (s.find('.') == std::string::npos) {
        return s;
    }
    return s.substr(0, s.find('.') + 2);
}

std::string pretty_number(double n) {
    if (n < 1'000) {
        return round(std::to_string(n));
    }
    if (n < 1'000'000) {
        n = n / 1'000;
        return round(std::to_string(n)) + "K";
    }
    if (n < 1'000'000'000) {
        n = n / 1'000'000;
        return round(std::to_string(n)) + "M";
    }
    if (n < 1'000'000'000'000) {
        n = n / 1'000'000'000;
        return round(std::to_string(n)) + "B";
    }
    if (n < 1'000'000'000'000'000) {
        n = n / 1'000'000'000'000;
        return round(std::to_string(n)) + "T";
    }
    return "TOO MUCH";
}

std::string pretty_number(long long n) {
    return pretty_number(static_cast<double>(n));
}

std::string pretty_number(uint64_t n) {
    return pretty_number(static_cast<long long>(n));
}