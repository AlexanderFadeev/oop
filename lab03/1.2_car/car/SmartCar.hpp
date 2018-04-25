#pragma once

#include "Car.hpp"
#include <iostream>
#include <map>
#include <optional>
#include <string>

class CSmartCar : public CCar
{
public:
	CSmartCar(std::istream& input = std::cin, std::ostream& output = std::cout);

	void HandleCommands();

private:
	enum class Command;

	static const std::map<std::string, CSmartCar::Command> m_stringToCommand;
	static const std::map<MovingDirection, std::string> m_movingDirectionToString;
	std::string GetMovingDirectionString() const;

	std::istream& m_input;
	std::ostream& m_output;

	void ShowUsage() const;
	bool GetCommandLine(std::string& commandLine);
	void HandleCommandLine(const std::string& commandLine);
	void HandleCommand(Command command, std::optional<int> param = std::nullopt);
	static Command ParseCommand(const std::string& command);
	static bool CommandNeedsParameter(Command command);

	void Info();
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
};

enum class CSmartCar::Command
{
	Info,
	EngineOn,
	EngineOff,
	SetGear,
	SetSpeed,
	Unknown,
};
