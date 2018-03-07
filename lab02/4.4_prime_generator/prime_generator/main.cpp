#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::vector<bool> GenerateErotosthenesSieve(size_t upperBound)
{
	if (upperBound < 2)
	{
		return std::vector<bool>(upperBound + 1, false);
	}

	std::vector<bool> sieve(upperBound + 1, true);
	sieve[0] = false;
	sieve[1] = false;

	for (size_t i = 2; i * i <= upperBound; i++)
	{
		if (!sieve[i])
		{
			continue;
		}

		for (size_t j = i * i; j <= upperBound; j += i)
		{
			sieve[j] = false;
		}
	}

	return sieve;
}

std::set<int> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::vector<bool> sieve = GenerateErotosthenesSieve(upperBound);

	std::set<int> primes;
	for (size_t index = 0; index <= upperBound; index++)
	{
		if (sieve[index])
		{
			primes.insert(primes.end(), static_cast<int>(index));
		}
	}

	return primes;
}

template <typename T>
auto Printer(std::ostream& output, const std::string& separator)
{
	return [&](const T& value) {
		output << value << separator;
	};
}

bool GeneratePrimeNumbers(std::ostream& output, int upperBound)
{
	if (upperBound >= 0)
	{
		auto primes = GeneratePrimeNumbersSet(upperBound);
		std::for_each(primes.begin(), primes.end(), Printer<int>(output, " "));
	}

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
const int MAX_UPPER_BOUND = static_cast<int>(1E+8);

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
