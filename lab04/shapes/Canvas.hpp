#pragma once

#include "Color.hpp"
#include "Point.hpp"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(const CPoint&, const CPoint&, const CColor&) = 0;
	virtual void FillPolygon(const std::vector<CPoint>&, const CColor&) = 0;
	virtual void DrawCircle(const CPoint&, double, const CColor&) = 0;
	virtual void FillCircle(const CPoint&, double, const CColor&) = 0;
};
