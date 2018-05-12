#include "SFMLCanvas.hpp"
#include "Shapes.hpp"

void ProcessShapes(std::istream& input, std::ostream& output);
void PrintShapesInfo(std::ostream& output, ShapePtrs& shapes);
void PrintShapesInfoImpl(std::ostream& output, ShapePtrs& shapes);
void Visualize(ShapePtrs& shapes);
void DrawAll(ICanvas& canvas, const ShapePtrs& ptrs);

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
	CShapeFactory factory(input);
	auto shapes = factory.GetAllShapes();

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
	DrawAll(canvas, shapes);
	canvas.Display();
	canvas.RunEventLoop();
}

void DrawAll(ICanvas& canvas, const ShapePtrs& shapePtrs)
{
	for (auto ptr : shapePtrs)
	{
		ptr->Draw(canvas);
	}
}
