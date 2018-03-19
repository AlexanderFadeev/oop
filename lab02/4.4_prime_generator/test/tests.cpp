#include "../prime_generator/Prime.hpp"
#include "catch.hpp"

TEST_CASE("0 and 1 are not prime numbers", "[sieve]")
{
	auto sieve = GenerateEratosthenesSieve(2);
	REQUIRE(!sieve[0]);
	REQUIRE(!sieve[1]);
}

TEST_CASE("2, 3, 5 and 7 are primes", "[primes]")
{
	auto primes = std::set<int>{ 2, 3, 5, 7 };
	auto result = GeneratePrimeNumbersSet(10);
	CHECK(result == primes);
}

TEST_CASE("25 prime number not greater than 100", "[primes]")
{
	auto result = GeneratePrimeNumbersSet(100);
	CHECK(result.size() == 25);
}

TEST_CASE("5761455 prime numbers not greater than 100000000", "[primes]")
{
	auto result = GeneratePrimeNumbersSet(100000000);
	CHECK(result.size() == 5761455);
}

TEST_CASE("Functions work with negative upper bounds", "[sieve][primes]")
{
	std::vector<bool> sieve;
	REQUIRE_NOTHROW(sieve = GenerateEratosthenesSieve(-42));
	CHECK(sieve.empty());

	std::set<int> primes;
	REQUIRE_NOTHROW(primes = GeneratePrimeNumbersSet(-42));
	CHECK(primes.empty());
}

TEST_CASE("Upper bound can be a prime number", "[primes]")
{
	auto primes = GeneratePrimeNumbersSet(17);
	CHECK(primes.find(17) != primes.end());

	auto sieve = GenerateEratosthenesSieve(17);
	CHECK(sieve[17]);
}

TEST_CASE("Fails on upper bound larger than 100000000", "[sieve][primes]")
{
	CHECK_THROWS(GeneratePrimeNumbersSet(100000001));
	CHECK_THROWS(GenerateEratosthenesSieve(100000001));
}
