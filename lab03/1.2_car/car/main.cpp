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
		if (!car.SetGear(parameter))
		{
			output << "Failed to set gear to " << parameter << std::endl;
		}
		break;
	case Command::SetSpeed:
		if (!car.SetSpeed(parameter))
		{
			output << "Failed to set speed to " << parameter << std::endl;
		}
		break;
	default:
		throw std::logic_error("Unknown command with parameter");
	}
}

const std::map<CCar::MovingDirection, std::string> MOVING_DIRECTION_TO_STRING{
	{ CCar::MovingDirection::Forwards, "Forwards" },
	{ CCar::MovingDirection::Stopped, "Stopped" },
	{ CCar::MovingDirection::Backwards, "Backwards" },
};

void Info(std::ostream& output, const CCar& car)
{
	auto state = car.GetState();
	output << "Engine: " << (state.isTurnedOn ? "ON" : "OFF") << std::endl
		   << "Gear: " << state.gear << std::endl
		   << "Moving direction: " << MOVING_DIRECTION_TO_STRING.at(state.movingDirection) << std::endl
		   << "Speed: " << state.speed;
}

void RunCommand(std::ostream& output, CCar& car, Command command)
{
	switch (command)
	{
	case Command::Info:
		Info(output, car);
		break;
	case Command::EngineOn:
		if (!car.TurnOnEngine())
		{
			output << "Failed to turn the engine on" << std::endl;
		}
		break;
	case Command::EngineOff:
		if (!car.TurnOffEngine())
		{
			output << "Failed to turn the engine off" << std::endl;
		}
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
			output << "Unknown command: " << commandStr << std::endl;
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
			output << "Failed to read parameter" << std::endl;
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
