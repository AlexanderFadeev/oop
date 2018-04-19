#pragma once

class CRational final
{
public:
	CRational();
	CRational(int&& value);
	CRational(int numerator, int denominator);

	operator double() const;

	const CRational operator+() const;
	const CRational operator-() const;


	const CRational operator+(const CRational&) const;
	const CRational operator-(const CRational&) const;

	bool operator==(const CRational&) const;
	bool operator!=(const CRational&) const;
	bool operator<(const CRational&) const;
	bool operator>(const CRational&) const;
	bool operator<=(const CRational&) const;
	bool operator>=(const CRational&) const;

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	int m_numerator;
	int m_denominator;
};
