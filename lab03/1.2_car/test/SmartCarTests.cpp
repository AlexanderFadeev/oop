#include "SmartCar.hpp"
#include "catch.hpp"
#include <algorithm>
#include <iterator>
#include <sstream>

const std::string INPUT_DATA =
	R"(EngineOn foo 
	EngineOn
	Info
	SetGear 5
	SetGear
	SetGear 1
	SetSpeed 100
	SetSpeed 30
	EngineOff
	SetGear 0
	SetSpeed 0
	EngineOff)";

const std::string EXPECTED_OUTPUT =
	R"(>  -Engine: ON
>  *Failed to turn the engine on
>  -Engine: ON
 -Gear: 0
 -Moving direction: Stopped
 -Speed: 0
>  *Failed to set gear to 5
>  *Command needs a parameter
 *Usage:
    Info
    EngineOn
    EngineOff
    SetGear <gear>
    SetSpeed <speed>
>  -Gear: 1
>  *Failed to set speed to 100
>  -Speed: 30
>  *Failed to turn the engine off
>  -Gear: 0
>  -Speed: 0
>  -Engine: OFF
> )";

SCENARIO("Smart car")
{
	GIVEN("A smart car with stringstream input and output")
	{
		std::stringstream input(INPUT_DATA);
		std::stringstream output;
		CSmartCar car(input, output);

		THEN("Input is handled propery")
		{
			car.HandleCommands();
			REQUIRE(output.str() == EXPECTED_OUTPUT);
		}
	}
}
