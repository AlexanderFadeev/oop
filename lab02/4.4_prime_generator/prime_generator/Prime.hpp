#pragma once

#include <set>
#include <vector>

const int MAX_UPPER_BOUND = static_cast<int>(1E+8);
std::vector<bool> GenerateEratosthenesSieve(int upperBound);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
