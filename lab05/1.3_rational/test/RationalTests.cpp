#include "catch.hpp"
#include "Rational.hpp"

void CheckRational(const CRational& r, int expectedNumerator, int expectedDenominator, double expectedToDouble)
{
	CHECK(expectedNumerator == r.GetNumerator());
	CHECK(expectedDenominator == r.GetDenominator());
	CHECK(expectedToDouble == r.ToDouble());
}

SCENARIO("Construction")
{
	GIVEN("A rational created with () constructor")
	{
		CRational r;

		THEN("It is properly initialized")
		{
			CheckRational(r, 0, 1, 0.0);
		}
	}

	GIVEN("A rational created with (int) constructor")
	{
		CRational r(42);

		THEN("It is properly initialized")
		{
			CheckRational(r, 42, 1, 42.0);
		}
	}

	GIVEN("A rational created with (int, int) constructor")
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