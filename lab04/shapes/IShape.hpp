#pragma once

#include "CanvasDrawable.hpp"
#include "Color.hpp"
#include <string>

class IShape
	: public ICanvasDrawable
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString(int precision = 2) const = 0;
	virtual CColor GetOutlineColor() const = 0;
};
