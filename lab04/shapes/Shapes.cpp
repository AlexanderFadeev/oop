#include "Shapes.hpp"

ShapePtr FindShapeWithLargestArea(ShapePtrs& shapes)
{
	return *std::max_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetArea() < b->GetArea();
	});
	;
}

ShapePtr FindShapeWithSmallestPerimeter(ShapePtrs& shapes)
{
	return *std::max_element(shapes.begin(), shapes.end(), [](auto a, auto b) {
		return a->GetPerimeter() < b->GetPerimeter();
	});
}
