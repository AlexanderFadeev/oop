#pragma once

#include "Function.hpp"
#include "Identifier.hpp"
#include "Variable.hpp"
#include <map>
#include <memory>
#include <regex>
#include <string>

class CCalculator
{
public:
	template <typename T>
	using IDMapping = std::map<std::string, std::shared_ptr<T>>;
	template <typename T>
	using IDMappingSPtr = std::shared_ptr<IDMapping<T>>;

	CCalculator();

	std::optional<double> GetValue(const std::string& id) const;
	void Var(const std::string& id);
	void Let(const std::string& id, double value);
	void Let(const std::string& id1, const std::string& id2);
	void Func(const std::string& fnID, const std::string& id);
	void Func(const std::string& fnID, const std::string& id1, CFunction::Operator op, const std::string& id2);

	IDMappingSPtr<CVariable> GetVariables();
	IDMappingSPtr<CFunction> GetFunctions();

private:
	static const std::regex m_identifierRegex;
	using IDSPtr = std::shared_ptr<CIdentifier>;

	IDMappingSPtr<CVariable> m_variables;
	IDMappingSPtr<CFunction> m_functions;

	IDSPtr GetID(const std::string& id) const;
	bool IsIdentifierDefined(const std::string& id) const;
	void ThrowIfDefined(const std::string& id) const;
	void ThrowIfNotDefined(const std::string& id) const;
};
