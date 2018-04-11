#pragma once

#include "Shape.hpp"

class ISolidShape
	: public IShape
{
public:
	virtual std::string GetFillColor() const = 0;
};
