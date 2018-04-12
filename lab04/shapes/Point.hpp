#pragma once

#include <string>

class CPoint final
{
public:
	double x;
	double y;

	bool operator==(const CPoint& other) const;
	double Dist(const CPoint& other) const;
	std::string ToString(int precision = 2) const;
};

double Dist(const CPoint&, const CPoint&);
