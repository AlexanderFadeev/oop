#include "SmartCar.hpp"
#include <sstream>

CSmartCar::CSmartCar(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CSmartCar::HandleCommands()
{
	std::string commandLine;

	while (m_output << "> " && std::getline(m_input, commandLine) && !commandLine.empty())
	{
		try
		{
			HandleCommand(commandLine);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
		catch (...)
		{
			m_output << "Unknown exception" << std::endl;
		}
	}
}

void CSmartCar::HandleCommand(const std::string& commandLine)
{
	std::istringstream buf(commandLine);
	std::string action;
	if (!(buf >> action))
	{
		throw std::exception("Failed to read command action");
	}

	auto command = ParseCommand(action);

	int value;
	if (buf >> value)
	{
		std::optional<int> param = value;
		HandleCommand(command, param);
		return;
	}

	HandleCommand(command);
}

void CSmartCar::HandleCommand(CSmartCar::Command command, std::optional<int> param)
{
	if (CommandNeedsParameter(command) && !param)
	{
		throw std::exception("Command needs a parameter");
	}

	switch (command)
	{
	case CSmartCar::Command::Info:
		Info();
		break;
	case CSmartCar::Command::EngineOn:
		TurnOnEngine();
		break;
	case CSmartCar::Command::EngineOff:
		TurnOffEngine();
		break;
	case CSmartCar::Command::SetGear:
		SetGear(*param);
		break;
	case CSmartCar::Command::SetSpeed:
		SetSpeed(*param);
		break;
	default:
		throw std::exception("Unknown command");
		break;
	}
}

const std::map<std::string, CSmartCar::Command> CSmartCar::m_stringToCommand = {
	{ "Info", Command::Info },
	{ "EngineOn", Command::EngineOn },
	{ "EngineOff", Command::EngineOff },
	{ "SetGear", Command::SetGear },
	{ "SetSpeed", Command::SetSpeed },
};

CSmartCar::Command CSmartCar::ParseCommand(const std::string& command)
{
	auto& mapping = m_stringToCommand;
	auto result = mapping.find(command);

	if (result == mapping.end())
	{
		return Command::Unknown;
	}

	return result->second;
}

const std::map<CCar::MovingDirection, std::string> CSmartCar::m_movingDirectionToString{
	{ MovingDirection::Forwards, "Forwards" },
	{ MovingDirection::Stopped, "Stopped" },
	{ MovingDirection::Backwards, "Backwards" },
};

void CSmartCar::Info()
{
	auto state = GetState();
	m_output << " -Engine: " << (state.isTurnedOn ? "ON" : "OFF") << std::endl
			 << " -Gear: " << state.gear << std::endl
			 << " -Moving direction: " << m_movingDirectionToString.at(state.movingDirection) << std::endl
			 << " -Speed: " << state.speed << std::endl;
}

void CSmartCar::TurnOnEngine()
{
	if (!CCar::TurnOnEngine())
	{
		m_output << "Failed to turn the engine on" << std::endl;
		return;
	}

	m_output << " -Engine: ON" << std::endl;
}

void CSmartCar::TurnOffEngine()
{
	if (!CCar::TurnOffEngine())
	{
		m_output << "Failed to turn the engine off" << std::endl;
		return;
	}

	m_output << " -Engine: OFF" << std::endl;
}

void CSmartCar::SetGear(int gear)
{
	if (!CCar::SetGear(gear))
	{
		m_output << "Failed to set gear to " << gear << std::endl;
		return;
	}

	m_output << " -Gear: " << gear << std::endl;
}

void CSmartCar::SetSpeed(int speed)
{
	if (!CCar::SetSpeed(speed))
	{
		m_output << "Failed to set speed to " << speed << std::endl;
		return;
	}

	m_output << " -Speed: " << speed << std::endl;
}

bool CSmartCar::CommandNeedsParameter(CSmartCar::Command command)
{
	return command == Command::SetGear || command == Command::SetSpeed;
}
