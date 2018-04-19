#include "Rational.hpp"
#include <cmath>
#include <limits>
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

template <typename T, typename Ret = T>
Ret LCM(T a, T b)
{
	return Ret(1) * a / GCD(a, b) * b;
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


template <typename T1, typename T2>
bool Overflows(T2 value)
{
	return value > std::numeric_limits<T1>::max()
		|| value < std::numeric_limits<T1>::min();
}

const std::overflow_error EXCEPTION_NUMERATOR_OVERFLOW("Numerator overflow");
const std::overflow_error EXCEPTION_DENOMINATOR_OVERFLOW("Denominator overflow");

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

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	if (m_numerator == INT_MIN)
	{
		throw EXCEPTION_NUMERATOR_OVERFLOW;
	}

	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+(const CRational& other) const
{
	long long denominator = LCM<long long>(m_denominator, other.m_denominator);
	long long numerator = m_numerator * (denominator / m_denominator)
		+ other.m_numerator * (denominator / other.m_denominator);
	
	Normalize(numerator, denominator);
	if (Overflows<int>(numerator))
	{
		throw EXCEPTION_NUMERATOR_OVERFLOW;
	}
	if (Overflows<int>(denominator))
	{
		throw EXCEPTION_DENOMINATOR_OVERFLOW;
	}

	return CRational(static_cast<int>(numerator), static_cast<int>(denominator));
}

const CRational CRational::operator-(const CRational& other) const
{
	return operator+(-other);
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

bool CRational::operator<(const CRational& other) const
{
	return 1ll * m_numerator * other.m_denominator < 1ll * other.m_numerator * m_denominator;
}

bool CRational::operator>(const CRational& other) const
{
	return other.operator<(*this);
}

bool CRational::operator<=(const CRational& other) const
{
	return !operator>(other);
}

bool CRational::operator>=(const CRational& other) const
{
	return !operator<(other);
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
