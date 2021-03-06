#include "SFMLCanvas.hpp"
#include "Shapes.hpp"
#include <vector>

void ProcessShapes(std::istream& input, std::ostream& output);
void PrintShapesInfo(std::ostream& output, ShapePtrs& shapes);
void PrintShapesInfoImpl(std::ostream& output, ShapePtrs& shapes);
void Visualize(ShapePtrs& shapes);
void AddDrawables(CSFMLCanvas& canvas, const ShapePtrs& ptrs);

int main() try
{
	ProcessShapes(std::cin, std::cout);
	return 0;
}
catch (std::exception& e)
{
	std::cerr << e.what();
	return 1;
}
catch (...)
{
	std::cerr << "Unknown exception";
	return 1;
}

void ProcessShapes(std::istream& input, std::ostream& output)
{
	auto shapes = GetAllShapes(input);

	PrintShapesInfo(output, shapes);
	Visualize(shapes);
}

void PrintShapesInfo(std::ostream& output, ShapePtrs& shapes)
{
	if (shapes.empty())
	{
		output << "There are no shapes\n";
	}
	else
	{
		PrintShapesInfoImpl(output, shapes);
	}


	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output");
	}
}

void PrintShapesInfoImpl(std::ostream& output, ShapePtrs& shapes)
{
	auto shapeWithLargestArea = FindShapeWithLargestArea(shapes);
	auto shapeWithSmallestPerimeter = FindShapeWithSmallestPerimeter(shapes);

	output << "Shape with largest area:\n"
		<< shapeWithLargestArea->ToString() << '\n'
		<< "Shape with smallest perimeter:\n"
		<< shapeWithSmallestPerimeter->ToString() << '\n';
}

void Visualize(ShapePtrs& shapes)
{
	CSFMLCanvas canvas(800, 450, "Shapes");
	AddDrawables(canvas, shapes);
	canvas.Redraw();
	canvas.RunEventLoop();
}

void AddDrawables(CSFMLCanvas& canvas, const ShapePtrs& shapePtrs)
{
	for (auto ptr : shapePtrs)
	{
		canvas.AddDrawable(ptr);
	}
}
