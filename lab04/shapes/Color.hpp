#pragma once

#include <cstdint>
#include <regex>
#include <string>

class CColor final
{
public:
	CColor(const std::string&);
	CColor(unsigned r, unsigned g, unsigned b);

	bool operator==(const CColor&) const;
	bool operator==(const std::string&) const;

	std::string ToString() const;
	uint32_t ToUInt32() const;

private:
	static const std::regex m_colorRegex;

	unsigned m_r;
	unsigned m_g;
	unsigned m_b;

	static bool IsValidRGBComponent(int);
	static void ValidateRGBComponent(int);
};

bool operator==(const std::string&, const CColor&);
