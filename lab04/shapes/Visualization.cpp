#include "Visualization.hpp"

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
