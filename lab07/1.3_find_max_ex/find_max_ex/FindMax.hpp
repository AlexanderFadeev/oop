#pragma once

#include <functional>
#include <vector>

template <typename T, typename Less = std::less<T>>
bool FindMax(const std::vector<T>& vec, T& maxValue, const Less& less = Less());

#include "FindMax.ipp"
