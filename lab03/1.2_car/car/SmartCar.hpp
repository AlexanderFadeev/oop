#pragma once

#include "Car.hpp"
#include <iostream>
#include <map>
#include <optional>
#include <string>

class CSmartCar : CCar
{
public:
	CSmartCar(std::istream& input = std::cin, std::ostream& output = std::cout);

	void HandleCommands();

private:
	enum class Command;

	static const std::map<std::string, CSmartCar::Command> m_stringToCommand;
	static const std::map<MovingDirection, std::string> m_movingDirectionToString;

	std::istream& m_input;
	std::ostream& m_output;

	void ShowUsage() const;
	bool GetCommandLine(std::string& commandLine);
	void HandleCommandLine(const std::string& commandLine);
	void HandleCommand(Command command, std::optional<int> param = {});
	Command ParseCommand(const std::string& command) const;
	bool CommandNeedsParameter(Command command) const;

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