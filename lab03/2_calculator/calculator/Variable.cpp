#include "Variable.hpp"

CVariable::CVariable()
	: m_value(std::numeric_limits<double>::quiet_NaN())
{
}

void CVariable::InitRelationsImpl() const
{
	// Do nothing
}

double CVariable::CalcValue() const
{
	return m_value;
}

void CVariable::SetValue(double value)
{
	m_value = value;
	Expire();
}
