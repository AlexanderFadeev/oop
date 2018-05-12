#pragma once

#include "ShapeFactory.hpp"
#include <vector>

using ShapePtr = CShapeFactory::ShapePtr;
using ShapePtrs = std::vector<ShapePtr>;

ShapePtr FindShapeWithLargestArea(ShapePtrs&);
ShapePtr FindShapeWithSmallestPerimeter(ShapePtrs&);
ShapePtrs GetAllShapes(std::istream& input);
