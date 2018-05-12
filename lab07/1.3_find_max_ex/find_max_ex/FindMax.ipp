#pragma once

#include "FindMax.hpp"

template <typename T, typename Less>
bool FindMax(const std::vector<T>& vec, T& maxValue, const Less& less)
{
	if (vec.empty())
	{
		return false;
	}

	size_t maxIndex = 0;
	auto greater = std::not_fn(less);
	for (size_t index = 1; index < vec.size(); index++)
	{
		auto& max = vec[maxIndex];
		auto& value = vec[index];
		if (greater(value, max))
		{
			maxIndex = index;
		}
	}

	maxValue = vec[maxIndex];
	return true;
}
