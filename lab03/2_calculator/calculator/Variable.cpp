#include "Variable.hpp"

std::shared_ptr<CVariable> CVariable::New()
{
	return std::shared_ptr<CVariable>(new CVariable());
}

std::shared_ptr<CVariable> CVariable::New(double value)
{
	return std::shared_ptr<CVariable>(new CVariable(value));
}

CVariable::CVariable()
	: m_value(std::numeric_limits<double>::quiet_NaN())
{
}

CVariable::CVariable(double value)
	: m_value(value)
{
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
