#include "catch.hpp"
#include "Rational.hpp"

namespace
{

void CheckRational(const CRational& r, int expectedNumerator, int expectedDenominator, double expectedToDouble)
{
	CHECK(expectedNumerator == r.GetNumerator());
	CHECK(expectedDenominator == r.GetDenominator());
	CHECK(expectedToDouble == r.ToDouble());
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

} // namespace

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

		THEN("Ints can be checked for equality with rational")
		{
			CheckNotEqual(a, m);
			CheckEqual(a, n);
		}
	}

	GIVEN("Rational number and double numbers")
	{
		CRational a(25, 4);
		double x = 5.0;
		double y = 6.25;

		THEN("Doubles can be checked for equality with rational")
		{
			CheckNotEqual(a, x);
			CheckEqual(a, y);
		}
	}
}