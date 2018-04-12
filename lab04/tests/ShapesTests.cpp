#include "LineSegment.hpp"
#include "Point.hpp"
#include "catch.hpp"

const std::string expectedLineToString =
	R"(LineSegment {
	area: 0,
	perimeter: 10,
	outline color: ffffff,
	point A: ( 0.5, 0.5 ),
	point B: ( 3.5, 4.5 ),
	length: 5,
}
)";

SCENARIO("Line Segment")
{
	GIVEN("A Line Segment")
	{
		const CPoint a{ .5, .5 };
		const CPoint b{ 3.5, 4.5 };
		const std::string color = "ffffff";
		const auto len = 5;

		CLineSegment line(a, b, color);

		THEN("It is properly initialized")
		{
			CHECK(a == line.GetPointA());
			CHECK(b == line.GetPointB());
			CHECK(color == line.GetOutlineColor());

			AND_THEN("It has correct properties values")
			{
				CHECK(len == line.GetLength());
				CHECK(2 * len == line.GetPerimeter());
				CHECK(0 == line.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{

				CHECK(expectedLineToString == line.ToString());
			}
		}
	}
}
