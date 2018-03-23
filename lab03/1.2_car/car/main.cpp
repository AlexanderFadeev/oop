#include "Car.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <string>

enum class Command
{
	Info,
	EngineOn,
	EngineOff,
	SetGear,
	SetSpeed,
	Unknown,
};

const std::map<std::string, Command> STRING_TO_COMMAND{
	{ "Info", Command::Info },
	{ "EngineOn", Command::EngineOn },
	{ "EngineOff", Command::EngineOff },
	{ "SetGear", Command::SetGear },
	{ "SetSpeed", Command::SetSpeed },
};

Command ParseCommand(const std::string& str)
{
	auto& mapping = STRING_TO_COMMAND;
	if (mapping.find(str) == mapping.end())
	{
		return Command::Unknown;
	}
	return mapping.at(str);
}

bool CommandNeedsParameter(Command command)
{
	return command == Command::SetGear || command == Command::SetSpeed;
}

void RunCommand(std::ostream& output, CCar& car, Command command, int parameter)
{
	switch (command)
	{
	case Command::SetGear:
		break;
	case Command::SetSpeed:
		break;
	default:
		throw std::logic_error("Unknown command with parameter");
	}
}

void RunCommand(std::ostream& output, CCar& car, Command command)
{
	switch (command)
	{
	case Command::Info:
		break;
	case Command::EngineOn:
		break;
	case Command::EngineOff:
		break;
	default:
		throw std::logic_error("Unknown command without parameter");
	}
}

void HandleCommands(std::istream& input, std::ostream& output, CCar& car)
{
	std::string commandStr;
	while (input >> commandStr)
	{
		auto command = ParseCommand(commandStr);
		if (command == Command::Unknown)
		{
			continue;
		}

		if (!CommandNeedsParameter(command))
		{
			RunCommand(output, car, command);
			continue;
		}

		int param;
		if (!(input >> param))
		{
			continue;
		}

		RunCommand(output, car, command, param);
	}
}

int main()
{
	try
	{
		CCar car;
		HandleCommands(std::cin, std::cout, car);
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
		return 1;
	}
}
