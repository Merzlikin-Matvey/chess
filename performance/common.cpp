#include "main.h"


std::string round(std::string s) {
    if (s.find('.') == std::string::npos) {
        return s;
    }

    auto res = s.substr(0, s.find('.') + 2);
    if (res[res.size() - 1] == '0') {
        res.pop_back();
        res.pop_back();
    }

    return res;
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

std::string pretty_time(std::chrono::duration<double> duration){
    const double ms = std::chrono::duration<double, std::milli>(duration).count();
    if (ms < 1'000) {
        return round(std::to_string(ms)) + " ms";
    }
    const double s = ms / 1'000;
    if (s < 60) {
        return round(std::to_string(s)) + " s";
    }
    const double m = s / 60;
    return round(std::to_string(m)) + " min";
}