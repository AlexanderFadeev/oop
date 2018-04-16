#include "Point.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>

bool CPoint::operator==(const CPoint& other) const
{
	return x == other.x && y == other.y;
}

double CPoint::Dist(const CPoint& other) const
{
	auto dx = x - other.x;
	auto dy = y - other.y;
	return std::hypot(dx, dy);
}

std::string CPoint::ToString(int precision) const
{
	std::ostringstream buf;
	buf << std::setprecision(precision) << std::fixed;

	buf << "( " << x << ", " << y << " )";

	return buf.str();
}

std::istream& operator>>(std::istream& input, CPoint& point)
{
	input >> point.x >> point.y;
	return input;
}

double Dist(const CPoint& a, const CPoint& b)
{
	return a.Dist(b);
}
