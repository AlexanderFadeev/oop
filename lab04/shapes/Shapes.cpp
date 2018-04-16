#include "Shapes.hpp"
#include "SFMLCanvas.hpp"

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

void PrintLargest(std::ostream& output, ShapePtrs shapes)
{
	auto shapeWithLargestArea = FindShapeWithLargestArea(shapes);
	auto shapeWithLargestPerimeter = FindShapeWithLargestPerimeter(shapes);

	output << "Shape with larges area:\n"
		   << shapeWithLargestArea->ToString() << '\n'
		   << "Shape with larges perimeter:\n"
		   << shapeWithLargestPerimeter->ToString() << std::endl;

	if (!output)
	{
		throw std::runtime_error("Failed to write to output");
	}
}

void DrawAll(ICanvas& canvas, const ShapePtrs& ptrs)
{
	for (auto ptr : ptrs)
	{
		ptr->Draw(canvas);
	}
}

void Visualize(ShapePtrs& shapes)
{
	CSFMLCanvas canvas(800, 450, "Shapes");
	DrawAll(canvas, shapes);
	canvas.Display();
	canvas.WaitForCloseEvent();
}

void ProcessShapes(std::istream& input, std::ostream& output)
{
	CShapeFactory factory(input);
	auto shapes = factory.GetAllShapes();

	PrintLargest(output, shapes);
	Visualize(shapes);
}
