#include "Car.hpp"
#include "catch.hpp"
#include <functional>
#include <vector>

using namespace std::placeholders;
using Direction = CCar::MovingDirection;

void ExpectSuccess(CCar& car, const std::function<bool(CCar&)>& op,
	bool expectedEngineState, int expectedGear, int expectedSpeed, Direction expectedDirection)
{
	REQUIRE(std::invoke(op, car));

	CHECK(car.IsTurnedOn() == expectedEngineState);
	CHECK(car.GetGear() == expectedGear);
	CHECK(car.GetSpeed() == expectedSpeed);
	CHECK(car.GetMovingDirection() == expectedDirection);
}

void ExpectSuccess(CCar& car, const std::function<bool(CCar&, int)>& op, int param,
	bool expectedEngineState, int expectedGear, int expectedSpeed, Direction expectedDirection)
{
	ExpectSuccess(car, std::bind(op, _1, param), expectedEngineState, expectedGear, expectedSpeed, expectedDirection);
}

void ExpectFailure(CCar& car, const std::function<bool(CCar&)>& op)
{
	auto negatedOp = [&op](CCar& car) {
		return !std::invoke(op, car);
	};

	ExpectSuccess(car, negatedOp, car.IsTurnedOn(), car.GetGear(), car.GetSpeed(), car.GetMovingDirection());
}

void ExpectFailure(CCar& car, const std::function<bool(CCar&, int)>& op, int param)
{
	ExpectFailure(car, std::bind(op, _1, param));
}

SCENARIO("Car engine", "[car][engine]")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("Is created")
		{
			THEN("Is turned off")
			{
				REQUIRE(!car.IsTurnedOn());
			}
		}

		WHEN("Is turned off")
		{
			THEN("Can't be turned off")
			{
				ExpectFailure(car, &CCar::TurnOffEngine);
			}
		}

		WHEN("Turned on")
		{
			ExpectSuccess(car, &CCar::TurnOnEngine, true, 0, 0, Direction::Stopped);

			THEN("Is turned on")
			{
				REQUIRE(car.IsTurnedOn());
			}
			THEN("Can't be turned on again")
			{
				ExpectFailure(car, &CCar::TurnOnEngine);
			}
			THEN("Can be turned off")
			{
				ExpectSuccess(car, &CCar::TurnOffEngine, false, 0, 0, Direction::Stopped);
			}
		}
	}
}

SCENARIO("Car gears", "[car][gears]")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("Is turned off")
		{
			THEN("Is in neutral gear")
			{
				REQUIRE(car.GetGear() == 0);
			}
			THEN("Gear can be changed only to neutral")
			{
				ExpectSuccess(car, &CCar::SetGear, 0, false, 0, 0, Direction::Stopped);
				ExpectFailure(car, &CCar::SetGear, -1);
				ExpectFailure(car, &CCar::SetGear, 1);
			}
		}

		WHEN("Is turned on")
		{
			car.TurnOnEngine();

			THEN("Is in neutral gear")
			{
				REQUIRE(car.GetGear() == 0);
			}

			AND_WHEN("Is stanging still")
			{
				THEN("Gears can be changed only to -1, 0 or 1")
				{
					ExpectSuccess(car, &CCar::SetGear, -1, true, -1, 0, Direction::Stopped);
					ExpectSuccess(car, &CCar::SetGear, 0, true, 0, 0, Direction::Stopped);
					ExpectSuccess(car, &CCar::SetGear, 1, true, 1, 0, Direction::Stopped);
					ExpectFailure(car, &CCar::SetGear, 2);
				}
			}
		}
	}
}

SCENARIO("Car speed", "[car][speed][gears]")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("Is turned off")
		{
			THEN("Is standing still")
			{
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.GetMovingDirection() == CCar::MovingDirection::Stopped);
			}

			THEN("Can't be sped up")
			{
				ExpectFailure(car, &CCar::SetSpeed, 5);
			}
		}

		WHEN("Is turned on")
		{
			car.TurnOnEngine();

			AND_WHEN("Is in neutral gear")
			{
				THEN("Can't be sped up")
				{
					ExpectFailure(car, &CCar::SetSpeed, 1);
				}

				THEN("Speed can be set to 0")
				{
					ExpectSuccess(car, &CCar::SetSpeed, 0, true, 0, 0, Direction::Stopped);
				}
			}

			AND_WHEN("Is in first gear")
			{
				ExpectSuccess(car, &CCar::SetGear, 1, true, 1, 0, Direction::Stopped);

				THEN("Can be sped up")
				{
					ExpectSuccess(car, std::bind(&CCar::SetSpeed, _1, 15), true, 1, 15, Direction::Forwards);

					AND_THEN("Can be turned off only in neutral gear after full stop")
					{
						ExpectFailure(car, &CCar::TurnOffEngine);
						ExpectSuccess(car, &CCar::SetGear, 0, true, 0, 15, Direction::Forwards);
						ExpectFailure(car, &CCar::TurnOffEngine);
						ExpectSuccess(car, &CCar::SetSpeed, 0, true, 0, 0, Direction::Stopped);
						ExpectSuccess(car, &CCar::TurnOffEngine, false, 0, 0, Direction::Stopped);
					}
				}
			}

			THEN("All forward gears have proper speed ranges")
			{
				const std::vector<std::pair<int, int>> ranges{
					{ 0, 30 },
					{ 20, 50 },
					{ 30, 60 },
					{ 40, 90 },
					{ 50, 150 },
				};

				for (size_t index = 0; index < ranges.size(); index++)
				{
					int gear = static_cast<int>(index + 1);
					auto& range = ranges[index];

					ExpectSuccess(car, &CCar::SetGear, gear, true, gear, car.GetSpeed(), car.GetMovingDirection());

					ExpectSuccess(car, &CCar::SetSpeed, range.first, true, gear, range.first, car.GetMovingDirection());
					ExpectSuccess(car, &CCar::SetSpeed, range.second, true, gear, range.second, car.GetMovingDirection());

					ExpectFailure(car, &CCar::SetSpeed, range.first - 1);
					ExpectFailure(car, &CCar::SetSpeed, range.second + 1);
				}

				AND_THEN("Sixth gear doesn't exist")
				{
					ExpectFailure(car, &CCar::SetGear, 6);
				}
			}
		}
	}
}

SCENARIO("Car reverse gear", "[car][reverse][gear][speed]")
{
	GIVEN("A car with engine turned on")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("Is standing still")
		{
			THEN("Gear can be changed to reverse")
			{
				ExpectSuccess(car, &CCar::SetGear, -1, true, -1, 0, Direction::Stopped);
			}
		}

		WHEN("In reverse gear")
		{
			car.SetGear(-1);

			THEN("Can be sped up")
			{
				ExpectSuccess(car, &CCar::SetSpeed, 10, true, -1, 10, Direction::Backwards);
			}

			THEN("Can have speed in range 0 - 20")
			{
				ExpectSuccess(car, &CCar::SetSpeed, 0, true, -1, 0, Direction::Stopped);
				ExpectSuccess(car, &CCar::SetSpeed, 20, true, -1, 20, Direction::Backwards);
				ExpectFailure(car, &CCar::SetSpeed, -1);
				ExpectFailure(car, &CCar::SetSpeed, 21);
			}

			AND_WHEN("Has speed")
			{
				car.SetSpeed(10);

				THEN("Gear can be changed to neutral")
				{
					ExpectSuccess(car, &CCar::SetGear, 0, true, 0, 10, Direction::Backwards);

					AND_THEN("Gear can't be changed back to reverse without full stop")
					{
						ExpectFailure(car, &CCar::SetGear, -1);
						ExpectSuccess(car, &CCar::SetSpeed, 0, true, 0, 0, Direction::Stopped);
						ExpectSuccess(car, &CCar::SetGear, -1, true, -1, 0, Direction::Stopped);
					}
				}

				THEN("Gear can be changed to first gear only at 0 speed")
				{
					ExpectFailure(car, &CCar::SetGear, 1);
					ExpectSuccess(car, &CCar::SetSpeed, 0, true, -1, 0, Direction::Stopped);
					ExpectSuccess(car, &CCar::SetGear, 1, true, 1, 0, Direction::Stopped);
				}
			}

			THEN("Can't change gear further")
			{
				ExpectSuccess(car, &CCar::SetSpeed, 20, true, -1, 20, Direction::Backwards);
				ExpectFailure(car, &CCar::SetGear, -2);
			}
		}
	}
}
