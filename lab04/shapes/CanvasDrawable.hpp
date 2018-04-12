#pragma once

#include "Canvas.hpp"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() = default;

	virtual void Draw(ICanvas&) = 0;
};
