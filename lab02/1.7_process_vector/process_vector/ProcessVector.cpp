#include "ProcessVector.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>

void ProcessVector(std::vector<double>& vec)
{
	if (vec.size() < LEAST_ELEMENTS_COUNT)
	{
		std::stringstream buf;
		buf << "Expected at least " << LEAST_ELEMENTS_COUNT << " elements";
		throw std::runtime_error(buf.str());
	}

	std::vector<double> smallestElements(LEAST_ELEMENTS_COUNT);
	std::partial_sort_copy(vec.begin(), vec.end(), smallestElements.begin(), smallestElements.end());
	double sum = std::accumulate(smallestElements.begin(), smallestElements.end(), 0.0);

	std::transform(vec.begin(), vec.end(), vec.begin(), [sum](double value) -> double {
		return value + sum;
	});
}
