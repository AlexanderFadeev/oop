#include "Car.hpp"
#include "catch.hpp"

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
				REQUIRE_FALSE(car.TurnOffEngine());
			}
		}

		WHEN("Turned on")
		{
			REQUIRE(car.TurnOnEngine());

			THEN("Is turned on")
			{
				REQUIRE(car.IsTurnedOn());
			}
			THEN("Can't be turned on again")
			{
				REQUIRE_FALSE(car.TurnOnEngine());
			}
			THEN("Can be turned off")
			{
				REQUIRE(car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
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
				CHECK(car.SetGear(0));
				CHECK_FALSE(car.SetGear(-1));
				CHECK_FALSE(car.SetGear(1));
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
					CHECK(car.SetGear(-1));
					CHECK(car.SetGear(0));
					CHECK(car.SetGear(1));
					CHECK_FALSE(car.SetGear(2));
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
				REQUIRE_FALSE(car.SetSpeed(5));
			}
		}

		WHEN("Is turned on")
		{
			car.TurnOnEngine();

			AND_WHEN("Is in neutral gear")
			{
				THEN("Can't be sped up")
				{
					REQUIRE_FALSE(car.SetSpeed(1));
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("Speed can be set to 0")
				{
					REQUIRE(car.SetSpeed(0));
					REQUIRE(car.GetSpeed() == 0);
				}
			}

			AND_WHEN("Is in first gear")
			{
				CHECK(car.SetGear(1));

				THEN("Can be sped up")
				{
					CHECK(car.SetSpeed(15));
					REQUIRE(car.GetSpeed() == 15);
					REQUIRE(car.GetMovingDirection() == CCar::MovingDirection::Forwards);

					AND_THEN("Can be turned off only in neutral gear after full stop")
					{
						REQUIRE_FALSE(car.TurnOffEngine());
						REQUIRE(car.SetGear(0));
						REQUIRE_FALSE(car.TurnOffEngine());
						REQUIRE(car.SetSpeed(0));
						REQUIRE(car.TurnOffEngine());
					}
				}
			}

			THEN("First gear is in range 0 - 30")
			{
				REQUIRE(car.SetGear(1));

				CHECK(car.SetSpeed(0));
				CHECK_FALSE(car.SetSpeed(-1));
				CHECK(car.SetSpeed(30));
				CHECK_FALSE(car.SetSpeed(31));

				AND_THEN("Second gear is in range 20 - 50")
				{

					REQUIRE(car.SetGear(2));

					CHECK(car.SetSpeed(20));
					CHECK_FALSE(car.SetSpeed(19));
					CHECK(car.SetSpeed(50));
					CHECK_FALSE(car.SetSpeed(51));

					AND_THEN("Third gear is in range 30 - 60")
					{

						REQUIRE(car.SetGear(3));

						CHECK(car.SetSpeed(30));
						CHECK_FALSE(car.SetSpeed(29));
						CHECK(car.SetSpeed(60));
						CHECK_FALSE(car.SetSpeed(61));

						AND_THEN("Fourth gear is in range 40 - 90")
						{

							REQUIRE(car.SetGear(4));

							CHECK(car.SetSpeed(40));
							CHECK_FALSE(car.SetSpeed(39));
							CHECK(car.SetSpeed(90));
							CHECK_FALSE(car.SetSpeed(91));

							AND_THEN("Fifth gear is in range 50 - 150")
							{
								REQUIRE(car.SetGear(5));

								CHECK(car.SetSpeed(50));
								CHECK_FALSE(car.SetSpeed(49));
								CHECK(car.SetSpeed(150));
								CHECK_FALSE(car.SetSpeed(151));

								AND_THEN("Sixth gear doesn't exist")
								{
									REQUIRE_FALSE(car.SetGear(6));
								}
							}
						}
					}
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
		REQUIRE(car.TurnOnEngine());

		WHEN("Is standing still")
		{
			THEN("Gear can be changed to reverse")
			{
				REQUIRE(car.SetGear(-1));
			}
		}

		WHEN("In reverse gear")
		{
			REQUIRE(car.SetGear(-1));

			THEN("Can be sped up")
			{
				CHECK(car.SetSpeed(10));
				REQUIRE(car.GetMovingDirection() == CCar::MovingDirection::Backwards);
			}

			THEN("Can have speed in range 0 - 20")
			{
				CHECK(car.SetSpeed(0));
				CHECK_FALSE(car.SetSpeed(-1));
				CHECK(car.SetSpeed(20));
				CHECK_FALSE(car.SetSpeed(21));
			}

			AND_WHEN("Has speed")
			{
				REQUIRE(car.SetSpeed(10));

				THEN("Gear can be changed to neutral")
				{
					REQUIRE(car.SetGear(0));

					AND_THEN("Gear can't be changed back to reverse without full stop")
					{
						CHECK_FALSE(car.SetGear(-1));
						REQUIRE(car.SetSpeed(0));
						REQUIRE(car.SetGear(-1));
					}
				}

				THEN("Gear can be changed to first gear only at 0 speed")
				{
					CHECK_FALSE(car.SetGear(1));
					REQUIRE(car.SetSpeed(0));
					REQUIRE(car.SetGear(1));
				}
			}

			THEN("Can't change speed further")
			{
				car.SetSpeed(20);
				REQUIRE_FALSE(car.SetGear(-2));
			}
		}
	}
}
