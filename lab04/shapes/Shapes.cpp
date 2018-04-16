#include "Shapes.hpp"

template <typename PropertyFn>
ShapePtr FindShapeWithLargestProperty(ShapePtrs& ptrs, PropertyFn fn)
{
	return *std::max_element(ptrs.begin(), ptrs.end(), [&fn](auto a, auto b) {
		return std::invoke(fn, *a) < std::invoke(fn, *b);
	});
}

ShapePtr FindShapeWithLargestArea(ShapePtrs& shapes)
{
	return FindShapeWithLargestProperty(shapes, &IShape::GetArea);
	;
}

ShapePtr FindShapeWithLargestPerimeter(ShapePtrs& shapes)
{
	return FindShapeWithLargestProperty(shapes, &IShape::GetPerimeter);
}

void PrintLargest(std::ostream& output, ShapePtrs& shapes)
{
	auto shapeWithLargestArea = FindShapeWithLargestArea(shapes);
	auto shapeWithLargestPerimeter = FindShapeWithLargestPerimeter(shapes);

	output << "Shape with largest area:\n"
		   << shapeWithLargestArea->ToString() << '\n'
		   << "Shape with largest perimeter:\n"
		   << shapeWithLargestPerimeter->ToString() << std::endl;

	if (!output)
	{
		throw std::runtime_error("Failed to write to output");
	}
}
