#pragma once

#include "Identifier.hpp"
#include <limits>

class CVariable : public CIdentifier
{
public:
	CVariable();

	void SetValue(double value);

private:
	double m_value;

	void InitRelationsImpl() const override;
	double CalcValue() const;
};
