#include "prime.hpp"

std::vector<bool> GenerateEratosthenesSieve(size_t upperBound)
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
	std::vector<bool> sieve = GenerateEratosthenesSieve(upperBound);

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
