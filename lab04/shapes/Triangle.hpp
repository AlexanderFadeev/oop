#pragma once

#include "SolidShape.hpp"

class CTriangle final
	: public CSolidShape
{
public:
	CTriangle(const CPoint&, const CPoint&, const CPoint&, const CColor&, const CColor&);

	double GetArea() const override;
	double GetPerimeter() const override;
	CPoint GetVertexA() const;
	CPoint GetVertexB() const;
	CPoint GetVertexC() const;

	void Draw(ICanvas&) override;

protected:
	std::string GetName() const override;
	std::string SolidFieldsToString(int precision = 2) const override;

private:
	std::tuple<double, double, double> GetSides() const;

	CPoint m_a;
	CPoint m_b;
	CPoint m_c;
};
