#include "Rational.hpp"
#include "catch.hpp"

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

} // namespace
