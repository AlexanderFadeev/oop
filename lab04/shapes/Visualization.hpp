#pragma once

#include "SFMLCanvas.hpp"
#include "ShapeFactory.hpp"

using ShapePtr = CShapeFactory::ShapePtr;
using ShapePtrs = CShapeFactory::ShapePtrs;

void DrawAll(ICanvas& canvas, const ShapePtrs& ptrs);
void Visualize(ShapePtrs& shapes);
