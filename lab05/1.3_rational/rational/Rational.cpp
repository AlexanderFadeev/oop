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

CRational::CRational(int value)
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

CRational& CRational::operator+=(const CRational& rhs)
{
	long long denominator = LCM<long long>(m_denominator, rhs.m_denominator);
	long long numerator = m_numerator * (denominator / m_denominator)
		            + rhs.m_numerator * (denominator / rhs.m_denominator);

	Normalize(numerator, denominator);
	if (Overflows<int>(numerator))
	{
		throw EXCEPTION_NUMERATOR_OVERFLOW;
	}
	if (Overflows<int>(denominator))
	{
		throw EXCEPTION_DENOMINATOR_OVERFLOW;
	}

	m_numerator = static_cast<int>(numerator);
	m_denominator = static_cast<int>(denominator);

	return *this;
}

CRational& CRational::operator-=(const CRational& rhs)
{
	return *this += -rhs;
}

CRational& CRational::operator*=(const CRational& rhs)
{
	long long numerator = 1ll * m_numerator * rhs.m_numerator;
	long long denominator = 1ll * m_denominator * rhs.m_denominator;

	Normalize(numerator, denominator);
	if (Overflows<int>(numerator))
	{
		throw EXCEPTION_NUMERATOR_OVERFLOW;
	}
	if (Overflows<int>(denominator))
	{
		throw EXCEPTION_DENOMINATOR_OVERFLOW;
	}

	m_numerator = static_cast<int>(numerator);
	m_denominator = static_cast<int>(denominator);

	return *this;
}

const CRational operator+(CRational lhs, const CRational& rhs)
{
	return lhs += rhs;
}

const CRational operator-(CRational lhs, const CRational& rhs)
{
	return lhs -= rhs;
}

const CRational operator*(CRational lhs, const CRational& rhs)
{
	return lhs *= rhs;
}

bool operator==(const CRational& lhs, const CRational& rhs)
{
	return lhs.m_numerator == rhs.m_numerator
		&& lhs.m_denominator == rhs.m_denominator;
}

bool operator!=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const CRational& lhs, const CRational& rhs)
{
	return 1ll * lhs.m_numerator * rhs.m_denominator < 1ll * rhs.m_numerator * lhs.m_denominator;
}

bool operator>(const CRational& lhs, const CRational& rhs)
{
	return rhs < lhs;
}

bool operator<=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const CRational& lhs, const CRational& rhs)
{
	return !(lhs < rhs);
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
	return 1.0 * m_numerator / m_denominator;
}
