#pragma once

#include "Canvas.hpp"
#include "ShapeFactory.hpp"

using ShapePtr = CShapeFactory::ShapePtr;
using ShapePtrs = CShapeFactory::ShapePtrs;

void DrawAll(ICanvas&, const ShapePtrs&);

template <typename PropertyFn>
ShapePtr FindShapeWithLargestProperty(ShapePtrs& ptrs, PropertyFn fn)
{
	return *std::max_element(ptrs.begin(), ptrs.end(), [&fn](auto a, auto b) {
		return std::invoke(fn, *a) < std::invoke(fn, *b);
	});
}
