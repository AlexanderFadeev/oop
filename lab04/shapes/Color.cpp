#include "Color.hpp"
#include <iomanip>
#include <sstream>

const std::regex CColor::m_colorRegex(R"(^#?([\da-fA-F]{2})([\da-fA-F]{2})([\da-fA-F]{2})$)");

CColor::CColor(const std::string& color)
{
	*this = color;
}

CColor::CColor(unsigned r, unsigned g, unsigned b)
	: m_r(r)
	, m_g(g)
	, m_b(b)
{
	ValidateRGBComponent(r);
	ValidateRGBComponent(g);
	ValidateRGBComponent(b);
}

CColor& CColor::operator=(const std::string& color)
{
	std::smatch match;
	if (!std::regex_match(color, match, m_colorRegex))
	{
		std::ostringstream buf;
		buf << "Invalid color format: " << color;
		throw std::invalid_argument(buf.str());
	}

	std::stringstream ss;

	ss << match[1] << ' ' << match[2] << ' ' << match[3];
	ss >> std::hex >> m_r >> m_g >> m_b;

	return *this;
}

bool CColor::operator==(const CColor& other) const
{
	return m_r == other.m_r
		&& m_g == other.m_g
		&& m_b == other.m_b;
}

bool CColor::operator==(const std::string& other) const
{
	return operator==(CColor(other));
}

std::string CColor::ToString() const
{
	std::ostringstream buf;
	buf << "#";
	buf << std::hex << std::uppercase << std::right << std::setfill('0');
	buf << std::setw(2) << m_r
		<< std::setw(2) << m_g
		<< std::setw(2) << m_b;
	return buf.str();
}

uint32_t CColor::ToUInt32() const
{
	return (m_r << 24)
		+ (m_g << 16)
		+ (m_b << 8)
		+ (0xFFu << 0);
}

bool CColor::IsValidRGBComponent(int x)
{
	return 0 <= x && x <= 255;
}

void CColor::ValidateRGBComponent(int x)
{
	if (!IsValidRGBComponent(x))
	{
		std::ostringstream buf;
		buf << "Invalid RGB component: " << x;
		throw std::invalid_argument(buf.str());
	}
}

std::istream& operator>>(std::istream& input, CColor& color)
{
	std::string colorStr;
	input >> colorStr;
	color = colorStr;
	return input;
}

bool operator==(const std::string& str, const CColor& color)
{
	return color == str;
}
