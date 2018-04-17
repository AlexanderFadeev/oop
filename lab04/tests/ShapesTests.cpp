#include "Canvas.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include "LineSegment.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"
#include "ShapeFactory.hpp"
#include "Triangle.hpp"
#include "catch.hpp"
#include <sstream>

#pragma warning(push)
#pragma warning(disable : 4100)
#include "fakeit.hpp"
#pragma warning(pop)

using namespace fakeit;

void InitCanvasMock(Mock<ICanvas>& mock)
{
	Fake(Method(mock, DrawLine));
	Fake(Method(mock, FillPolygon));
	Fake(Method(mock, DrawCircle));
	Fake(Method(mock, FillCircle));
}

const std::string g_expectedLineToString =
	R"(LineSegment {
	area: 0.00,
	perimeter: 10.00,
	outline color: #FFFFFF,
	point A: ( 0.50, 0.50 ),
	point B: ( 3.50, 4.50 ),
	length: 5.00,
})";

const std::string g_expectedTriangleToString =
	R"(Triangle {
	area: 6.00,
	perimeter: 12.00,
	outline color: #FFFFFF,
	fill color: #ABCDEF,
	vertex A: ( 0.50, 0.50 ),
	vertex B: ( 3.50, 4.50 ),
	vertex C: ( 0.50, 4.50 ),
})";

const std::string g_expectedRectangleToString =
	R"(Rectangle {
	area: 50.00,
	perimeter: 30.00,
	outline color: #777777,
	fill color: #BEEF42,
	left top vertex: ( 0.50, 5.50 ),
	right bottom vertex: ( 5.50, 15.50 ),
	width: 5.00,
	height: 10.00,
})";

const std::string g_expectedCircleToString =
	R"(Circle {
	area: 314.16,
	perimeter: 62.83,
	outline color: #112233,
	fill color: #FFF111,
	center point: ( 100500.00, 42.00 ),
	radius: 10.00,
})";

SCENARIO("Colors")
{
	GIVEN("Valid hex colors")
	{
		std::string redHex = "Ff0000";
		std::string cyanHex = "00fFFf";
		std::string sampleHex = "#010203";

		THEN("They can be used to create color objects")
		{
			CColor red(redHex);
			CColor cyan(cyanHex);
			CColor sample(sampleHex);

			AND_THEN("Objects can be correctly converted back to strings")
			{
				CHECK(red.ToString() == "#FF0000");
				CHECK(cyan.ToString() == "#00FFFF");
				CHECK(sample.ToString() == "#010203");
			}
			AND_THEN("Objects can be correctly converted to uint32")
			{
				CHECK(red.ToUInt32() == 0xFF0000FFu);
				CHECK(cyan.ToUInt32() == 0x00FFFFFFu);
				CHECK(sample.ToUInt32() == 0x010203FFu);
			}
		}
	}

	GIVEN("A color created from RGB int values")
	{
		CColor color(1, 42, 255);

		THEN("It can be properly converted to string")
		{
			CHECK(color.ToString() == "#012AFF");
		}
		THEN("It can be properly converted to uint32")
		{
			CHECK(color.ToUInt32() == 0x012AFFFFu);
		}
	}

	SECTION("Cannot create colors from invalid args")
	{
		CHECK_THROWS(CColor(256, 0, 0));
		CHECK_THROWS(CColor(0, 256, 0));
		CHECK_THROWS(CColor(0, 0, 256));
		CHECK_THROWS(CColor("12345"));
		CHECK_THROWS(CColor("1234567"));
		CHECK_THROWS(CColor("G00000"));
		CHECK_THROWS(CColor("##123456"));
	}
}

SCENARIO("Line Segment")
{
	GIVEN("A Line Segment")
	{
		const CPoint a{ .5, .5 };
		const CPoint b{ 3.5, 4.5 };
		const CColor color("ffffff");
		const auto len = 5;

		CLineSegment line(a, b, color);

		THEN("It is properly initialized")
		{
			CHECK(a == line.GetPointA());
			CHECK(b == line.GetPointB());
			CHECK(color == line.GetOutlineColor());

			AND_THEN("It has correct property values")
			{
				CHECK(len == line.GetLength());
				CHECK(2 * len == line.GetPerimeter());
				CHECK(0 == line.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{
				CHECK(g_expectedLineToString == line.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			line.Draw(mock.get());

			Verify(Method(mock, DrawLine).Using(a, b, color)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}

SCENARIO("Triangle")
{
	GIVEN("A Triangle")
	{
		const CPoint a{ .5, .5 };
		const CPoint b{ 3.5, 4.5 };
		const CPoint c{ .5, 4.5 };
		const CColor outlineColor("ffffff");
		const CColor fillColor("abcdef");
		const auto perimeter = 12;
		const auto area = 6;

		CTriangle triangle(a, b, c, outlineColor, fillColor);

		THEN("It is properly initialized")
		{
			CHECK(a == triangle.GetVertexA());
			CHECK(b == triangle.GetVertexB());
			CHECK(c == triangle.GetVertexC());
			CHECK(outlineColor == triangle.GetOutlineColor());
			CHECK(fillColor == triangle.GetFillColor());

			AND_THEN("It has correct property values")
			{
				CHECK(perimeter == triangle.GetPerimeter());
				CHECK(area == triangle.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{
				CHECK(g_expectedTriangleToString == triangle.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			triangle.Draw(mock.get());

			Verify(Method(mock, FillPolygon).Using(std::vector<CPoint>{ a, b, c }, fillColor)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}

SCENARIO("Rectangle")
{
	GIVEN("A Rectangle")
	{
		const CPoint a{ 0.5, 15.5 };
		const CPoint b{ 5.5, 5.5 };
		const CPoint leftTop{ .5, 5.5 };
		const CPoint rightBot{ 5.5, 15.5 };
		const CColor outlineColor("777777");
		const CColor fillColor("beef42");
		const auto perimeter = 30;
		const auto area = 50;
		const auto width = 5;
		const auto heigth = 10;

		CRectangle rectangle(a, b, outlineColor, fillColor);

		THEN("It is properly initialized")
		{
			CHECK(leftTop == rectangle.GetLeftTop());
			CHECK(rightBot == rectangle.GetRightBottom());
			CHECK(outlineColor == rectangle.GetOutlineColor());
			CHECK(fillColor == rectangle.GetFillColor());

			AND_THEN("It has correct property values")
			{
				CHECK(perimeter == rectangle.GetPerimeter());
				CHECK(area == rectangle.GetArea());
				CHECK(width == rectangle.GetWidth());
				CHECK(heigth == rectangle.GetHeigth());
			}
			AND_THEN("It is properly converted to string")
			{
				CHECK(g_expectedRectangleToString == rectangle.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			rectangle.Draw(mock.get());

			Verify(Method(mock, FillPolygon).Using(std::vector<CPoint>{ leftTop, b, rightBot, a }, fillColor)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}

SCENARIO("Circle")
{
	GIVEN("A Circle")
	{
		const double pi = std::atan(1) * 4;
		const CPoint center{ 100500, 42 };
		const double radius = 10;
		const CColor outlineColor("112233");
		const CColor fillColor("fff111");
		const auto perimeter = 2 * pi * radius;
		const auto area = pi * radius * radius;

		CCircle circle(center, radius, outlineColor, fillColor);

		THEN("It is properly initialized")
		{
			CHECK(center == circle.GetCenter());
			CHECK(radius == circle.GetRadius());
			CHECK(outlineColor == circle.GetOutlineColor());
			CHECK(fillColor == circle.GetFillColor());

			AND_THEN("It has correct property values")
			{
				CHECK(perimeter == circle.GetPerimeter());
				CHECK(area == circle.GetArea());
			}
			AND_THEN("It is properly converted to string")
			{
				CHECK(g_expectedCircleToString == circle.ToString());
			}
		}

		THEN("It is drawn properly")
		{
			Mock<ICanvas> mock;
			InitCanvasMock(mock);

			circle.Draw(mock.get());

			Verify(Method(mock, FillCircle).Using(center, radius, fillColor)).Once();
			VerifyNoOtherInvocations(mock);
		}
	}
}

SCENARIO("Shape Factory")
{
	GIVEN("A Shape Factory with valid input data")
	{

		const std::string validFactoryInputData =
			R"(line 0.5 .5 3.5 4.5 #FFFFFF
			   triangle .5 .5 3.5 4.5 .5 4.5 ffffff abcdef
			   rectangle 5.5 15.5 .5 5.5 777777 beef42
			   circle 100500.0 42 10 112233 fff111)";

		const std::vector<std::string> expectedShapesToString{
			g_expectedLineToString,
			g_expectedTriangleToString,
			g_expectedRectangleToString,
			g_expectedCircleToString,
		};
		auto shapesCount = expectedShapesToString.size();

		std::istringstream iss(validFactoryInputData);
		CShapeFactory factory(iss);

		THEN("It can create shapes")
		{
			CShapeFactory::ShapePtrs shapes;
			REQUIRE_NOTHROW(shapes = factory.GetAllShapes());

			AND_THEN("It creates right amount of shapes")
			{
				REQUIRE(shapes.size() == shapesCount);

				AND_THEN("All shapes are initialized with correct property values")
				{
					for (size_t index = 0; index < shapesCount; index++)
					{
						CHECK(shapes[index]->ToString() == expectedShapesToString[index]);
					}
				}
			}
		}
	}
}
