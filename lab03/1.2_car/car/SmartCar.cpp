#include "SmartCar.hpp"
#include <sstream>

CSmartCar::CSmartCar(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

bool CSmartCar::GetCommandLine(std::string& commandLine)
{
	m_output << "> ";
	if (!std::getline(m_input, commandLine))
	{
		return false;
	}

	return !commandLine.empty();
}

void CSmartCar::HandleCommands()
{
	std::string commandLine;

	while (GetCommandLine(commandLine))
	{
		HandleCommandLine(commandLine);
	}
}

void CSmartCar::ShowUsage() const
{
	m_output << " *Usage:" << std::endl
			 << "    Info" << std::endl
			 << "    EngineOn" << std::endl
			 << "    EngineOff" << std::endl
			 << "    SetGear <gear>" << std::endl
			 << "    SetSpeed <speed>" << std::endl;
}

template <typename T>
std::optional<T> ReadValue(std::istream& input)
{
	T value;
	if (!(input >> value))
	{
		return {};
	}

	return { value };
}

void CSmartCar::HandleCommandLine(const std::string& commandLine)
{
	std::istringstream buf(commandLine);
	std::string commandStr;
	if (!(buf >> commandStr))
	{
		m_output << " *Failed to read command" << std::endl;
		ShowUsage();
		return;
	}

	auto command = ParseCommand(commandStr);
	if (command == CSmartCar::Command::Unknown)
	{
		m_output << " *Unknown command: " << commandStr << std::endl;
		ShowUsage();
		return;
	}

	auto param = ReadValue<int>(buf);
	HandleCommand(command, param);
}

void CSmartCar::HandleCommand(CSmartCar::Command command, std::optional<int> param)
{
	if (CommandNeedsParameter(command) && !param)
	{
		m_output << " *Command needs a parameter" << std::endl;
		ShowUsage();
		return;
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
		m_output << " *Unknown command" << std::endl;
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

std::string CSmartCar::GetMovingDirectionString() const
{
	return m_movingDirectionToString.at(GetMovingDirection());
}

void CSmartCar::Info()
{
	m_output << " -Engine: " << (IsTurnedOn() ? "ON" : "OFF") << std::endl
			 << " -Gear: " << GetGear() << std::endl
			 << " -Moving direction: " << GetMovingDirectionString() << std::endl
			 << " -Speed: " << GetSpeed() << std::endl;
}

void CSmartCar::TurnOnEngine()
{
	if (!CCar::TurnOnEngine())
	{
		m_output << " *Failed to turn the engine on" << std::endl;
		return;
	}

	m_output << " -Engine: ON" << std::endl;
}

void CSmartCar::TurnOffEngine()
{
	if (!CCar::TurnOffEngine())
	{
		m_output << " *Failed to turn the engine off" << std::endl;
		return;
	}

	m_output << " -Engine: OFF" << std::endl;
}

void CSmartCar::SetGear(int gear)
{
	if (!CCar::SetGear(gear))
	{
		m_output << " *Failed to set gear to " << gear << std::endl;
		return;
	}

	m_output << " -Gear: " << gear << std::endl;
}

void CSmartCar::SetSpeed(int speed)
{
	if (!CCar::SetSpeed(speed))
	{
		m_output << " *Failed to set speed to " << speed << std::endl;
		return;
	}

	m_output << " -Speed: " << speed << std::endl;
}

bool CSmartCar::CommandNeedsParameter(CSmartCar::Command command)
{
	return command == Command::SetGear || command == Command::SetSpeed;
}
