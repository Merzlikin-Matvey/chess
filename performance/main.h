#pragma once

#include "chess-lib.hpp"

std::string pretty_number(long long n);
std::string pretty_number(double n);

// tests
void run_perft();
void run_alpha_beta();