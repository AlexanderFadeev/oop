#pragma once

#include "IShape.hpp"

class ISolidShape
	: public virtual IShape
{
public:
	virtual CColor GetFillColor() const = 0;
};
