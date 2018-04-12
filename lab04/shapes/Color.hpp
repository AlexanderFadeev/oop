#pragma once

#include <cstdint>
#include <regex>
#include <string>

class CColor final
{
public:
	CColor(const std::string&);
	CColor(int r, int g, int b);

	bool operator==(const CColor&) const;
	bool operator==(const std::string&) const;

	std::string ToString() const;

private:
	static const std::regex m_colorRegex;

	int m_r;
	int m_g;
	int m_b;

	static bool IsValidRGBComponent(int);
	static void ValidateRGBComponent(int);
};

bool operator==(const std::string&, const CColor&);
