#pragma once

#include "SolidShape.hpp"

class CCircle final
	: public CSolidShape
{
public:
	CCircle(const CPoint&, double, const CColor&, const CColor&);

	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

	virtual void Draw(ICanvas&) override;

protected:
	std::string GetName() const override;
	std::string SolidFieldsToString(int precision = 2) const override;

private:
	static double GetPi();

	CPoint m_center;
	double m_radius;
};
