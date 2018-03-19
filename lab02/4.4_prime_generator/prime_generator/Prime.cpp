#include "Prime.hpp"
#include <sstream>

void ThrowIfLargerThanMaxUpperBound(int upperBound)
{
	if (upperBound > MAX_UPPER_BOUND)
	{
		std::stringstream buf;
		buf << "Value in bigger than " << MAX_UPPER_BOUND;
		throw std::invalid_argument(buf.str());
	}
}

std::vector<bool> GenerateEratosthenesSieve(int upperBound)
{
	ThrowIfLargerThanMaxUpperBound(upperBound);

	if (upperBound < 0)
	{
		return std::vector<bool>{};
	}

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

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	ThrowIfLargerThanMaxUpperBound(upperBound);

	std::vector<bool> sieve = GenerateEratosthenesSieve(upperBound);

	std::set<int> primes;
	for (size_t index = 0; index < sieve.size(); index++)
	{
		if (sieve[index])
		{
			primes.insert(primes.end(), static_cast<int>(index));
		}
	}

	return primes;
}
