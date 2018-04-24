#include "Rational.hpp"
#include "catch.hpp"
#include <limits>
#include <vector>
#include <sstream>

namespace
{

void CheckRational(const CRational& r, int expectedNumerator, int expectedDenominator, double expectedToDouble)
{
	CHECK(expectedNumerator == r.GetNumerator());
	CHECK(expectedDenominator == r.GetDenominator());
	CHECK(expectedToDouble == r.ToDouble());
}

SCENARIO("Construction")
{
	GIVEN("A rational number created with () constructor")
	{
		CRational r;

		THEN("It is properly initialized")
		{
			CheckRational(r, 0, 1, 0.0);
		}
	}

	GIVEN("A rational number created with (int) constructor")
	{
		CRational r(42);

		THEN("It is properly initialized")
		{
			CheckRational(r, 42, 1, 42.0);
		}
	}

	GIVEN("A rational number created with (int, int) constructor")
	{
		CRational r(35, -14);

		THEN("It is properly initialized and is normalized")
		{
			CheckRational(r, -5, 2, -2.5);
		}
	}

	SECTION("Throws when zero denominator is passed")
	{
		CHECK_THROWS(CRational(1, 0));
	}
}

template <typename T1, typename T2>
void CheckEqual(const T1& a, const T2& b)
{
	CHECK(a == b);
	CHECK(b == a);
	CHECK_FALSE(a != b);
	CHECK_FALSE(b != a);
}

template <typename T1, typename T2>
void CheckNotEqual(const T1& a, const T2& b)
{
	CHECK(a != b);
	CHECK(b != a);
	CHECK_FALSE(a == b);
	CHECK_FALSE(b == a);
}

SCENARIO("Operators == and !=")
{
	GIVEN("Equal rational numbers")
	{
		CRational a(10, 5);
		CRational b(6, 3);

		THEN("Their equality is checked properly")
		{
			CheckEqual(a, b);
		}
	}

	GIVEN("Unequal rational numbers")
	{
		CRational a(10, 5);
		CRational b(9, 4);

		THEN("Their unequality is checked properly")
		{
			CheckNotEqual(a, b);
		}
	}

	GIVEN("Rational number and int numbers")
	{
		CRational a(48, 8);
		int m = 5;
		int n = 6;

		THEN("Ints are properly checked for equality with rational")
		{
			CheckNotEqual(a, m);
			CheckEqual(a, n);
		}
	}
}

template <typename T1, typename T2>
void CheckComparisonsLess(const T1& a, const T2& b)
{
	CHECK(a < b);
	CHECK(a <= b);
	CHECK(b > a);
	CHECK(b >= a);
	CHECK_FALSE(a > b);
	CHECK_FALSE(a >= b);
	CHECK_FALSE(b < a);
	CHECK_FALSE(b <= a);
}

template <typename T1, typename T2>
void CheckComparisonsEqual(const T1& a, const T2& b)
{
	CHECK(a <= b);
	CHECK(a >= b);
	CHECK(b <= a);
	CHECK(b >= a);
	CHECK_FALSE(a < b);
	CHECK_FALSE(a > b);
	CHECK_FALSE(b < a);
	CHECK_FALSE(b > a);
}

SCENARIO("Operators <, >, <=, >=")
{
	GIVEN("Different rational numbers")
	{
		CRational a(4, 5);
		CRational b(7, 3);

		THEN("Comparison operators are working properly")
		{
			CheckComparisonsLess(a, b);
		}
	}

	GIVEN("Equal rational numbers")
	{
		CRational a(8, 10);
		CRational b(12, 15);

		THEN("Comparison operators are working properly")
		{
			CheckComparisonsEqual(a, b);
		}
		THEN("Comparison of rational number with itself works properly")
		{
			CheckComparisonsEqual(a, a);
		}
	}

	GIVEN("Rational number and int numbers")
	{
		CRational a(48, 8);
		int m = 5;
		int n = 6;
		int k = 7;

		THEN("Ints are properly compared with rational")
		{
			CheckComparisonsLess(m, a);
			CheckComparisonsLess(a, k);
			CheckComparisonsEqual(a, n);
		}
	}
}

SCENARIO("Unary + and -")
{
	GIVEN("A rational number")
	{
		CRational a(6, 8);
		const CRational munusA(-6, 8);

		THEN("Unary + returns same value")
		{
			CHECK(+a == a);
		}
		THEN("Unary - returns opposite value")
		{
			CHECK(-a == munusA);
		}
	}
}

SCENARIO("Operators + and -")
{
	GIVEN("Rational numbers")
	{
		CRational a(1, 6);
		CRational b(1, 3);
		CRational c(5, 6);
		CRational result(1, 2);

		THEN("Sum is calculated properly and is normalized")
		{
			CHECK(a + b == result);
		}
		THEN("Difference is calculated properly and is normalized")
		{
			CHECK(c - b == result);
		}
	}

	GIVEN("Rational number and int")
	{
		CRational a(7, 5);
		int n = 2;

		THEN("Sum and difference are calculated properly")
		{
			CHECK((a + n) == CRational(17, 5));
			CHECK((n + a) == CRational(17, 5));
			CHECK((a - n) == CRational(-3, 5));
			CHECK((n - a) == CRational(3, 5));
		}
	}
}

SCENARIO("Overflows")
{
	SECTION("Unary -")
	{
		CRational r(INT_MIN);
		CHECK_THROWS(-r);
	}

	SECTION("Operators +, -, +=, -= : denominator overflow")
	{
		CRational a(1, 1 << 16);
		CRational b(1, (1 << 16) + 1);
		CHECK_THROWS(a + b);
		CHECK_THROWS(a - b);
		CHECK_THROWS(a += b);
		CHECK_THROWS(a -= b);
	}

	SECTION("Operators +, -, +=, -= : numerator overflow")
	{
		CRational max(INT_MAX);
		CRational min(INT_MIN);
		CHECK_THROWS(max + 1);
		CHECK_THROWS(min - 1);
		CHECK_THROWS(max += 1);
		CHECK_THROWS(min -= 1);
	}

	SECTION("Operators +, -, +=, -= : numerator does not overflow in process of calculations")
	{
		CRational a(INT_MAX, 2);
		CRational b(INT_MIN, 3);
		CRational da(1, 2);
		CRational db(1, 3);
		CHECK_NOTHROW(a + da);
		CHECK_NOTHROW(b - db);
		CHECK_NOTHROW(a += da);
		CHECK_NOTHROW(b -= db);
	}

	SECTION("Operators +, -, +=, -= : denominator does not overflow in process of calculations")
	{
		CRational a(1, 1 << 30);
		CHECK_NOTHROW(a + a);
	}

	SECTION("Operators *, *=, /, /= : denominator overflow")
	{
		CRational a(1, 1 << 16);
		CRational b(1, (1 << 16) + 1);
		CHECK_THROWS(a * b);
		CHECK_THROWS(a *= b);
		CHECK_THROWS(a / (1 / b));
		CHECK_THROWS(a /= (1 / b));
	}

	SECTION("Operators *, *=, /, /= : numerator overflow")
	{
		CRational max(INT_MAX);
		CRational min(INT_MIN);
		CRational half(1, 2);
		CHECK_THROWS(min * -1);
		CHECK_THROWS(min *= -1);
		CHECK_THROWS(min / -1);
		CHECK_THROWS(min /= -1);

		CHECK_THROWS(max * 2);
		CHECK_THROWS(min * 2);
		CHECK_THROWS(max *= 2);
		CHECK_THROWS(min *= 2);

		CHECK_THROWS(max / half);
		CHECK_THROWS(min / half);
		CHECK_THROWS(max /= half);
		CHECK_THROWS(min /= half);
	}

	SECTION("Operators *, *=, /, /= : numerator does not overflow in process of calculations")
	{
		CRational a(INT_MAX, 2);
		CRational b(INT_MIN, 2);
		CRational half(1, 2);

		SECTION("Multiplication")
		{
			CHECK_NOTHROW(a * 2);
			CHECK_NOTHROW(b * 2);
			CHECK_NOTHROW(a *= 2);
			CHECK_NOTHROW(b *= 2);
		}

		SECTION("Division")
		{
			CHECK_NOTHROW(a / half);
			CHECK_NOTHROW(b / half);
			CHECK_NOTHROW(a /= half);
			CHECK_NOTHROW(b /= half);
		}
	}

	SECTION("Operators *, *=, /, /= : denominator does not overflow in process of calculations")
	{
		CRational a(2, 1 << 30);
		CRational k(1, 2);

		SECTION("Multiplication")
		{
			CHECK_NOTHROW(a * k);
			CHECK_NOTHROW(a *= k);
		}

		SECTION("Division")
		{
			CHECK_NOTHROW(a / (1 / k));
			CHECK_NOTHROW(a /= (1 / k));
		}
	}
}

template <typename T>
void CheckIncrementAndDecrement(CRational& a, T d)
{
	CRational orig = a;

	WHEN("Operator += is used")
	{
		(a += d) += d;

		THEN("Object is modified properly")
		{
			CHECK(a == orig + d + d);
		}

		AND_WHEN("Operator -= is used")
		{
			(a -= d) -= d;

			THEN("Object's value is equal to its original value")
			{
				CHECK(a == orig);
			}
		}
	}
}

SCENARIO("Operators += and -=")
{
	GIVEN("Rational numbers")
	{
		CRational a(1, 6);
		CRational d(5, 6);
		CheckIncrementAndDecrement(a, d);
	}

	GIVEN("Rational number and int")
	{
		CRational a(7, 5);
		int d = 2;
		CheckIncrementAndDecrement(a, d);
	}

	SECTION("Exception safety")
	{
		CRational a(INT_MAX - 1, INT_MAX);
		CRational orig = a;
		CHECK_THROWS(a += CRational(1, 2));
		CHECK(a == orig);
		CHECK_THROWS(a += CRational(2, INT_MAX));
		CHECK(a == orig);
	}
}

SCENARIO("Operators * and /")
{
	GIVEN("Rational numbers")
	{
		CRational a(9, 2);
		CRational b(2, 3);
		CRational c(3, 2);
		CRational result(3, 1);

		THEN("Product is calculated properly and is normalized")
		{
			CHECK(a * b == result);
		}

		THEN("Quotient is calculated properly and is normalized")
		{
			CHECK(a / c == result);
		}
	}

	GIVEN("Rational number and int")
	{
		CRational a(3, 10);
		int n = 12;
		CRational product(18, 5);
		CRational quotient1(1, 40);
		CRational quotient2(40);

		THEN("Product is calculated properly and is normalized")
		{
			CHECK((a * n) == product);
			CHECK((n * a) == product);
		}
		THEN("Quotients are calculated properly and are normalized")
		{
			CHECK((a / n) == quotient1);
			CHECK((n / a) == quotient2);
		}
	}
}

template <typename T>
void CheckMultiplicationAndDivisionAssignment(CRational a, T k)
{
	CRational orig = a;

	WHEN("Operator *= is used")
	{
		(a *= k) *= k;

		THEN("Object is modified properly")
		{
			CHECK(a == orig * k * k);
		}

		AND_WHEN("Operator /= is used")
		{
			(a /= k) /= k;

			THEN("Object's value is equal to its original value")
			{
				CHECK(a == orig);
			}
		}
	}
}

SCENARIO("Operators *= and /=")
{
	GIVEN("Rational numbers")
	{
		CRational a(16, 7);
		CRational b(3, 2);
		CheckMultiplicationAndDivisionAssignment(a, b);
	}

	GIVEN("Rational number and int")
	{
		CRational a(7, 6);
		int n = 2;
		CheckMultiplicationAndDivisionAssignment(a, n);
	}

	SECTION("Exception safety")
	{
		CRational a((1 << 30) - 1, (1 << 30) + 1);
		CRational orig = a;
		CHECK_THROWS(a *= 42);
		CHECK(a == orig);
		CHECK_THROWS(a *= CRational(1, 42));
		CHECK(a == orig);
		CHECK_THROWS(a /= 42);
		CHECK(a == orig);
		CHECK_THROWS(a /= CRational(1, 42));
		CHECK(a == orig);
	}
}


struct TestCase
{
	std::string data;
	std::string extraData;
	CRational value;
};

void CheckTestCase(const TestCase& testCase)
{
	GIVEN("An istream with valid rational number")
	{
		std::stringstream ss;
		ss << testCase.data << testCase.extraData;

		THEN("Value is properly read from istream")
		{
			CRational r;
			ss >> r;
			CHECK(r == testCase.value);

			AND_THEN("Extra data is not taken from istream")
			{
				std::string extra;
				std::getline(ss, extra);
				CHECK(extra == testCase.extraData);
			}
		}
	}
}

SCENARIO("Operators >> and <<")
{
	GIVEN("Valid rational string representations and corresponding values")
	{
		std::vector<TestCase> testCases{
			{ "22/7", " ", { 22, 7 } },
			{ "21/7", "#", { 3, 1 } },
			{ "36/8", " 123", { 9, 2 } },
		};

		for (auto& testCase : testCases)
		{
			CheckTestCase(testCase);
		}
	}

	GIVEN("Invalid rational string representations")
	{
		std::vector<std::string> testCases{
			"1/0",
			"/2",
			"100/",
			"42 5",
			"!2/3",
		};

		for (auto& testCase : testCases)
		{
			GIVEN("An istream with invalid data and CRational object")
			{
				std::istringstream is(testCase);
				CRational r(22, 7);
				CRational orig = r;

				WHEN("Data is read from istream to CRational")
				{
					is >> r;

					THEN("Istream's to bool conversion is false")
					{
						CHECK(!is);
						
						AND_THEN("Object is not modified")
						{
							CHECK(r == orig);
						}
					}
				}
			}
		}
	}
}

void CheckCompoundFraction(CRational r, int integral, CRational rational)
{
	auto compound = r.ToCompoundFraction();
	CHECK(compound.first == integral);
	CHECK(compound.second == rational);
}

SCENARIO("Compound fractions")
{
	GIVEN("A rational number")
	{
		CRational r(42, 35);

		THEN("Compound fraction for it is calculated properly")
		{
			CheckCompoundFraction(r, 1, {1, 5});
		}
	}

	GIVEN("A negative rational number")
	{
		CRational r(-42, 15);

		THEN("Compound fraction for it is calculated properly")
		{
			CheckCompoundFraction(r, -2, { -4, 5 });
		}
	}

	GIVEN("An integer rational number")
	{
		CRational n(42);
		auto compound = n.ToCompoundFraction();

		THEN("Integral part is equal to the number itself")
		{
			CHECK(compound.first == n);

			AND_THEN("Rational part is equal to zero")
			{
				CHECK(compound.second == 0);
			}
		}
	}
}

} // namespace
