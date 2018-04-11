#pragma once

#include <string>

class IShape
{
public:
	virtual ~IShape() = 0;

	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString() = 0;
	virtual std::string GetOutlineColor() = 0;
};
