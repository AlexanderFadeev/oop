#include "LineSegment.hpp"
#include <iomanip>
#include <sstream>

CLineSegment::CLineSegment(const CPoint& a, const CPoint& b, const std::string& outlineColor)
	: m_a(a)
	, m_b(b)
	, IShape(outlineColor)
{
}

std::string CLineSegment::ToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision);

	buf << "LineSegment {\n"
		<< FieldsToString(precision)
		<< "\tpoint A: " << m_a.ToString(precision) << ",\n"
		<< "\tpoint B: " << m_b.ToString(precision) << ",\n"
		<< "\tlength: " << GetLength() << ",\n"
		<< "}\n";

	return buf.str();
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return 2 * GetLength();
}

double CLineSegment::GetLength() const
{
	return Dist(m_a, m_b);
}

CPoint CLineSegment::GetPointA() const
{
	return m_a;
}

CPoint CLineSegment::GetPointB() const
{
	return m_b;
}
