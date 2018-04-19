#include "Rational.hpp"
#include <cmath>
#include <stdexcept>

namespace
{

template <typename T>
T GCD(T a, T b)
{
	a = std::abs(a);
	b = std::abs(b);

	while (b)
	{
		T tmp = a % b;
		a = b;
		b = tmp;
	}

	return a ? a : 1;
}

template <typename T>
void Normalize(T& a, T& b)
{
	T gcd = GCD(a, b);
	a /= gcd;
	b /= gcd;

	if (b < 0) {
		a *= -1;
		b *= -1;
	}
}

} // namespace

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int&& value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Zero denominator is not allowed");
	}

	Normalize(m_numerator, m_denominator);
}

CRational::operator double() const
{
	return 1.0 * m_numerator / m_denominator;
}

bool CRational::operator==(const CRational& other) const
{
	return m_numerator == other.m_numerator
		&& m_denominator == other.m_denominator;
}

bool CRational::operator!=(const CRational& other) const
{
	return !operator==(other);
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return double(*this);
}
