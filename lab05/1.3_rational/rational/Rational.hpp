#pragma once

class CRational final
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	const CRational operator+() const;
	const CRational operator-() const;

	friend const CRational operator+(const CRational&, const CRational&);
	friend const CRational operator-(const CRational&, const CRational&);

	friend bool operator==(const CRational&, const CRational&);
	friend bool operator!=(const CRational&, const CRational&);
	friend bool operator< (const CRational&, const CRational&);
	friend bool operator> (const CRational&, const CRational&);
	friend bool operator<=(const CRational&, const CRational&);
	friend bool operator>=(const CRational&, const CRational&);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	int m_numerator;
	int m_denominator;
};
