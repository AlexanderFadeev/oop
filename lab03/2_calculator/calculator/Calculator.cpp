#include "Calculator.hpp"

namespace
{
	
template <typename IDMappingSPtr>
bool IsIdentifierDefined(const std::string& id, const IDMappingSPtr& where)
{
	return where->find(id) != where->end();
}

template <typename IDMappingSPtr>
void ThrowIfDefined(const std::string& id, const IDMappingSPtr& where)
{
	if (IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is already defined");
	}
}

template <typename IDMappingSPtr>
void ThrowIfNotDefined(const std::string& id, const IDMappingSPtr& where)
{
	if (!IsIdentifierDefined(id, where))
	{
		throw std::exception("Identifier is not defined");
	}
}

const std::regex IDENTIFIER_REGEX(R"(^[_A-Za-z]\w*$)");

bool IsIdentifierValid(const std::string& id)
{
	return std::regex_match(id, IDENTIFIER_REGEX);
}

void ThrowIfNotValid(const std::string& id)
{
	if (!IsIdentifierValid(id))
	{
		throw std::exception("Identifier is not valid");
	}
}

} // namespace

CCalculator::CCalculator()
	: m_variables(std::make_shared<IDMapping<CVariable>>())
	, m_functions(std::make_shared<IDMapping<CFunction>>())
{
}

std::optional<double> CCalculator::GetValue(const std::string& id) const
{
	if (!IsIdentifierDefined(id))
	{
		return std::nullopt;
	}

	return GetID(id)->GetValue();
}

void CCalculator::Var(const std::string& id)
{
	ThrowIfNotValid(id);
	ThrowIfDefined(id);

	auto variable = CVariable::New();
	m_variables->insert({ id, variable });
}

void CCalculator::Let(const std::string& id, double value)
{
	if (!::IsIdentifierDefined(id, m_variables))
	{
		Var(id);
	}

	m_variables->at(id)->SetValue(value);
}

void CCalculator::Let(const std::string& id1, const std::string& id2)
{
	ThrowIfNotDefined(id2);

	double value = *GetValue(id2);
	Let(id1, value);
}

void CCalculator::Func(const std::string& fnID, const std::string& id)
{
	ThrowIfNotValid(fnID);
	ThrowIfDefined(fnID);
	ThrowIfNotDefined(id);

	auto function = CFunction::New(GetID(id));
	m_functions->insert({ fnID, function });
}

using Operator = CFunction::Operator;

void CCalculator::Func(const std::string& fnID, const std::string& id1, Operator op, const std::string& id2)
{
	ThrowIfNotValid(fnID);
	ThrowIfDefined(fnID);
	ThrowIfNotDefined(id1);
	ThrowIfNotDefined(id2);

	auto function = CFunction::New(GetID(id1), op, GetID(id2));
	m_functions->insert({ fnID, function });
}

CCalculator::IDMappingSPtr<CVariable> CCalculator::GetVariables()
{
	return m_variables;
}

CCalculator::IDMappingSPtr<CFunction> CCalculator::GetFunctions()
{
	return m_functions;
}

CCalculator::IDSPtr CCalculator::GetID(const std::string& id) const
{
	if (::IsIdentifierDefined(id, m_functions))
	{
		return m_functions->at(id);
	}

	return m_variables->at(id);
}

bool CCalculator::IsIdentifierDefined(const std::string& id) const
{
	return ::IsIdentifierDefined(id, m_functions)
		|| ::IsIdentifierDefined(id, m_variables);
}

void CCalculator::ThrowIfDefined(const std::string& id) const
{
	::ThrowIfDefined(id, m_functions);
	::ThrowIfDefined(id, m_variables);
}

void CCalculator::ThrowIfNotDefined(const std::string& id) const
{
	if (!IsIdentifierDefined(id))
	{
		throw std::exception("Identifier is not defined");
	}
}
