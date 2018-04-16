#pragma once

#include "ShapeFactory.hpp"

using ShapePtr = CShapeFactory::ShapePtr;
using ShapePtrs = CShapeFactory::ShapePtrs;

ShapePtr FindShapeWithLargestArea(ShapePtrs&);
ShapePtr FindShapeWithLargestPerimeter(ShapePtrs&);
