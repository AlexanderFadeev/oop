#include "Triangle.hpp"
#include <iomanip>
#include <sstream>

CTriangle::CTriangle(const CPoint& a, const CPoint& b, const CPoint& c,
	const CColor& outlineColor, const CColor& fillColor)
	: CSolidShape(outlineColor, fillColor)
	, m_a(a)
	, m_b(b)
	, m_c(c)
{
}

double CTriangle::GetArea() const
{
	auto [ab, bc, ca] = GetSides();
	auto p = GetPerimeter() / 2;
	auto area = std::sqrt(p * (p - ab) * (p - bc) * (p - ca));
	return area;
}

double CTriangle::GetPerimeter() const
{
	auto [ab, bc, ca] = GetSides();
	return ab + bc + ca;
}

CPoint CTriangle::GetVertexA() const
{
	return m_a;
}

CPoint CTriangle::GetVertexB() const
{
	return m_b;
}

CPoint CTriangle::GetVertexC() const
{
	return m_c;
}

std::string CTriangle::GetName() const
{
	return "Triangle";
}

std::string CTriangle::SolidFieldsToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision) << std::fixed;

	buf	<< "\tvertex A: " << m_a.ToString(precision) << ",\n"
		<< "\tvertex B: " << m_b.ToString(precision) << ",\n"
		<< "\tvertex C: " << m_c.ToString(precision) << ",\n";

	return buf.str();
}

void CTriangle::Draw(ICanvas& canvas)
{
	canvas.FillPolygon({ m_a, m_b, m_c }, m_fillColor);
	canvas.DrawLine(m_a, m_b, m_outlineColor);
	canvas.DrawLine(m_b, m_c, m_outlineColor);
	canvas.DrawLine(m_c, m_a, m_outlineColor);
}

std::tuple<double, double, double> CTriangle::GetSides() const
{
	auto ab = Dist(m_a, m_b);
	auto bc = Dist(m_b, m_c);
	auto ca = Dist(m_c, m_a);

	return { ab, bc, ca };
}
