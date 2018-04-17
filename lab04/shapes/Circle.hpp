#pragma once

#include "SolidShape.hpp"

class CCircle final
	: public ISolidShape
{
public:
	CCircle(const CPoint&, double, const CColor&, const CColor&);

	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

	std::string ToString(int precision = 2) const override;

	virtual void Draw(ICanvas&) override;

private:
	static double GetPi();

	CPoint m_center;
	double m_radius;
};
