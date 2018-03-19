#include "prime.hpp"
#include <algorithm>
#include <iostream>
#include <string>

template <typename T>
auto Printer(std::ostream& output, const std::string& separator)
{
	return [&](const T& value) {
		output << value << separator;
	};
}

bool GeneratePrimeNumbers(std::ostream& output, int upperBound)
{
	auto primes = GeneratePrimeNumbersSet(upperBound);
	std::for_each(primes.begin(), primes.end(), Printer<int>(output, " "));

	output << std::endl;
	return static_cast<bool>(output);
}

long StrToLong(char* str, bool& wasErr)
{
	char* pEnd = NULL;
	long value = strtol(str, &pEnd, 10);
	wasErr = ((*str == '\0') || (*pEnd != '\0'));
	return value;
}

const int ARGS_COUNT = 1;

void ShowUsage()
{
	std::cerr << "Usage: prime_generator.exe <upper bound>\n"
			  << "upper bound <= " << MAX_UPPER_BOUND << "\n";
}

int main(int argc, char* argv[])
{
	if (argc != ARGS_COUNT + 1)
	{
		std::cout << "Invalid arguments count\n";
		ShowUsage();
		return 1;
	}

	bool wasErr = false;
	long upperBound = StrToLong(argv[1], wasErr);
	if (wasErr || upperBound > MAX_UPPER_BOUND)
	{
		std::cout << "Wrong upper bound: " << argv[1] << '\n';
		ShowUsage();
		return 1;
	}

	bool ok = GeneratePrimeNumbers(std::cout, upperBound);
	return ok ? 0 : 1;
}
