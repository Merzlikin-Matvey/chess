#pragma once

#include "chess-lib.hpp"

std::string pretty_number(double n);
std::string pretty_number(long long n);
std::string pretty_number(uint64_t n);

std::string pretty_time(std::chrono::duration<double> duration);

// tests
void run_perft();
void run_alpha_beta();