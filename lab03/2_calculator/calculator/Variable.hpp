#pragma once

#include "Identifier.hpp"
#include <limits>

class CVariable : public CIdentifier
{
public:
	CVariable();

	double GetValue() const override;
	void SetValue(double value);

private:
	double m_value;
};
