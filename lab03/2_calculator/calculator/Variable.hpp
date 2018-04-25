#pragma once

#include "Identifier.hpp"
#include <limits>

class CVariable : public CIdentifier
{
public:
	static std::shared_ptr<CVariable> New();
	static std::shared_ptr<CVariable> New(double value);

	void SetValue(double value);

private:
	CVariable();
	CVariable(double value);

	double CalcValue() const;

	double m_value;

};