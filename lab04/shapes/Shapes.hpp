#pragma once

#include "Canvas.hpp"
#include "ShapeFactory.hpp"

using ShapePtr = CShapeFactory::ShapePtr;
using ShapePtrs = CShapeFactory::ShapePtrs;

ShapePtr FindShapeWithLargestArea(ShapePtrs&);
ShapePtr FindShapeWithLargestPerimeter(ShapePtrs&);
void DrawAll(ICanvas& canvas, const ShapePtrs& ptrs);
void ProcessShapes(std::istream& input, std::ostream& output);
