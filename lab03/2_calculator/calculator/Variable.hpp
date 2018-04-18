#pragma once

#include "Identifier.hpp"
#include <limits>

class CVariable : public CIdentifier
{
public:
	template <typename... Args>
	static std::shared_ptr<CVariable> New(Args&&... args);

	CVariable();
	CVariable(double value);

	void SetValue(double value);

private:
	double CalcValue() const;

	double m_value;

};

template <typename... Args>
inline std::shared_ptr<CVariable> CVariable::New(Args&&... args)
{
	return std::make_shared<CVariable>(std::forward<Args>(args)...);
}
