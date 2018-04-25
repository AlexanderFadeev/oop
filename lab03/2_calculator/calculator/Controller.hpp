#pragma once

#include "Calculator.hpp"
#include "Function.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <string>

class CController final
{
public:
	CController(CCalculator&, std::istream& input = std::cin, std::ostream& output = std::cout);

	void HandleCommands();
	void HandleUserCommands();

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream&)>>;

	std::optional<std::string> GetCommandLine();
	std::optional<std::string> GetUserCommandLine();
	void HandleCommandLine(const std::string&);
	void Var(std::istream&);
	void Let(std::istream&);
	void Func(std::istream&);
	void Print(std::istream&);
	void PrintVars(std::istream&);
	void PrintFuncs(std::istream&);
	static std::optional<double> TryToParseNumber(const std::string&);

	static const std::regex m_letRegex;
	static const std::regex m_fnRegex;

	const ActionMap m_actionMap;
	static const std::map<std::string, CFunction::Operator> m_stringToOperator;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};

