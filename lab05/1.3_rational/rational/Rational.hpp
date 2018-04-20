#pragma once

#include <iostream>

class CRational final
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	const CRational operator+() const;
	const CRational operator-() const;

	CRational& operator+=(const CRational&);
	CRational& operator-=(const CRational&);
	CRational& operator*=(const CRational&);
	CRational& operator/=(CRational);

	friend const CRational operator+(CRational, const CRational&);
	friend const CRational operator-(CRational, const CRational&);
	friend const CRational operator*(CRational, const CRational&);
	friend const CRational operator/(CRational, const CRational&);

	friend bool operator==(const CRational&, const CRational&);
	friend bool operator!=(const CRational&, const CRational&);
	friend bool operator< (const CRational&, const CRational&);
	friend bool operator> (const CRational&, const CRational&);
	friend bool operator<=(const CRational&, const CRational&);
	friend bool operator>=(const CRational&, const CRational&);

	friend std::istream& operator>>(std::istream&, CRational&);
	friend std::ostream& operator<<(std::ostream&, const CRational&);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	int m_numerator;
	int m_denominator;
};
