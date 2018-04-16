#include "Shapes.hpp"

void DrawAll(ICanvas& canvas, const ShapePtrs& ptrs)
{
	for (auto ptr : ptrs)
	{
		ptr->Draw(canvas);
	}
}
