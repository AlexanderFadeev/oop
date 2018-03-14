#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

template <typename T>
void ReadVector(std::istream& input, std::vector<T>& vec)
{
	vec = {};
	std::copy(std::istream_iterator<T>(input), {}, std::back_inserter(vec));
}

template <typename T>
auto Printer(std::ostream& output, const std::string& separator)
{
	return [&](const T& value) {
		output << value << separator;
	};
}

template <typename T>
void PrintVector(std::ostream& output, const std::vector<T>& vec)
{
	output << std::setprecision(3) << std::fixed;

	std::for_each(vec.begin(), vec.end(), Printer<double>(output, " "));
	output << std::endl;

	if (!(output))
	{
		throw std::runtime_error("Failed to flush output");
	}
}

template <typename T>
void PrintVectorSorted(std::ostream& output, std::vector<T> vec)
{
	std::sort(vec.begin(), vec.end());
	PrintVector(output, vec);
}

const size_t LEAST_ELEMENTS_COUNT = 3;

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

int main()
{
	try
	{
		std::vector<double> vec;
		ReadVector(std::cin, vec);
		ProcessVector(vec);
		PrintVectorSorted(std::cout, vec);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return 1;
	}

	return 0;
}
