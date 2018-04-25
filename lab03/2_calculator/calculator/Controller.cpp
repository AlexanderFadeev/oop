#include "Controller.hpp"
#include <sstream>
#include <iomanip>

namespace ph = std::placeholders;

namespace
{

template <typename MappingSPtr>
void PrintIDs(std::ostream& output, const MappingSPtr& mappingSPtr)
{
	output << std::setprecision(2) << std::fixed;

	for (auto& relation : *mappingSPtr)
	{
		output << relation.first << ':' << relation.second->GetValue() << '\n';
	}

	if (!output.flush())
	{
		throw std::runtime_error("Failed to write to output");
	}
}

} // namespace

CController::CController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap{
		{ "var", std::bind(&CController::Var, this, ph::_1) },
		{ "let", std::bind(&CController::Let, this, ph::_1) },
		{ "fn", std::bind(&CController::Func, this, ph::_1) },
		{ "print", std::bind(&CController::Print, this, ph::_1) },
		{ "printvars", std::bind(&CController::PrintVars, this, ph::_1) },
		{ "printfns", std::bind(&CController::PrintFuncs, this, ph::_1) },
	}
{
}

void CController::HandleCommands()
{
	while (auto commandLine = GetCommandLine())
	{
		HandleCommandLine(*commandLine);
	}
}

std::optional<std::string> CController::GetCommandLine()
{
	std::string result;
	if (!std::getline(m_input, result))
	{
		return std::nullopt;
	}

	return result;
}

void CController::HandleUserCommands()
{
	while (auto commandLine = GetUserCommandLine())
	{
		HandleCommandLine(*commandLine);
	}
}

std::optional<std::string> CController::GetUserCommandLine()
{
	m_output << " >";
	return GetCommandLine();
}

void CController::HandleCommandLine(const std::string& line) try
{
	std::istringstream iss(line);
	std::string command;

	if (!(iss >> command))
	{
		throw std::invalid_argument("Failed to read command");
	}

	auto actionIt = m_actionMap.find(command);
	if (actionIt == m_actionMap.end())
	{
		std::ostringstream buf;
		buf << "Invalid command: " << command;
		throw std::invalid_argument(buf.str());
	}

	actionIt->second.operator()(iss);
}
catch (const std::exception& e)
{
	m_output << e.what() << std::endl;
}
catch (...)
{
	m_output << "Unknown exception" << std::endl;
}

void CController::Var(std::istream& input)
{
	std::string id;
	input >> id;
	m_calculator.Var(id);
}

const std::regex CController::m_letRegex(R"(\s*(\w+)\s*=\s*(\S+)\s*$)");

void CController::Let(std::istream& input)
{
	std::string params;
	std::getline(input, params);

	std::smatch match;
	if (!std::regex_match(params, match, m_letRegex))
	{
		throw std::invalid_argument("Invalid parameters");
	}

	if (auto number = TryToParseNumber(match[2]))
	{
		m_calculator.Let(match[1], *number);
		return;
	}

	m_calculator.Let(match[1], match[2]);
}

using Operator = CFunction::Operator;

const std::regex CController::m_fnRegex(R"(^\s*(\w+)\s*=\s*(\w+)(?:\s*([+\-*\/])\s*(\w+))?\s*$)");
const std::map<std::string, CFunction::Operator> CController::m_stringToOperator{
	{ "+", Operator::Sum },
	{ "-", Operator::Diff },
	{ "*", Operator::Mul },
	{ "/", Operator::Div },
};

void CController::Func(std::istream& input)
{
	std::string params;
	std::getline(input, params);

	std::smatch match;
	if (!std::regex_match(params, match, m_fnRegex))
	{
		throw std::invalid_argument("Invalid parameters");
	}

	if (match.length(3) == 0)
	{
		m_calculator.Func(match[1], match[2]);
		return;
	}

	auto op = m_stringToOperator.at(match[3]);
	m_calculator.Func(match[1], match[2], op, match[4]);
}

void CController::Print(std::istream& input)
{
	std::string id;
	input >> id;

	auto valueOpt = m_calculator.GetValue(id);
	if (!valueOpt)
	{
		m_output << "Identifier `" << id << "` is not defined\n";
		return;
	}

	m_output << std::setprecision(2) << std::fixed;
	m_output << *valueOpt << '\n';
}

void CController::PrintVars(std::istream&)
{
	auto vars = m_calculator.GetVariables();
	PrintIDs(m_output, vars);
}

void CController::PrintFuncs(std::istream&)
{
	auto funcs = m_calculator.GetFunctions();
	PrintIDs(m_output, funcs);
}

std::optional<double> CController::TryToParseNumber(const std::string& str) 
{
	try
	{
		return std::stod(str);
	}
	catch (...)
	{
		return std::nullopt;
	}
}