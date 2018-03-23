#include "Car.hpp"
#include <array>
#include <cmath>
#include <limits>

CCar::State CCar::GetState() const
{
	return {
		m_isTurnedOn,
		m_gear,
		m_speed
	};
}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isTurnedOn)
	{
		return false;
	}

	m_isTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isTurnedOn)
	{
		return false;
	}

	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}

	m_isTurnedOn = false;
	return true;
}

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const std::array<std::pair<int, int>, MAX_GEAR - MIN_GEAR + 1> SPEED_RANGES{ {
	{ -20, 0 },
	{ INT_MIN, INT_MAX },
	{ 0, 30 },
	{ 20, 50 },
	{ 30, 60 },
	{ 40, 90 },
	{ 50, 150 },
} };

int CCar::GetGear() const
{
	return m_gear;
}

bool CCar::SpeedIsInRangeOfGear(int speed, int gear) const
{
	if (gear < MIN_GEAR || MAX_GEAR < gear)
	{
		return false;
	}

	auto range = SPEED_RANGES[gear - MIN_GEAR];
	return (range.first <= speed && speed <= range.second);
}

bool CCar::SetGear(int gear)
{
	if (!m_isTurnedOn && gear != 0)
	{
		return false;
	}

	if (gear == -1 && m_speed != 0)
	{
		return false;
	}

	if (!SpeedIsInRangeOfGear(m_speed, gear))
	{
		return false;
	}

	m_gear = gear;
	return true;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isTurnedOn && speed != 0)
	{
		return false;
	}

	if (m_gear == 0 && std::abs(speed) > std::abs(m_speed))
	{
		return false;
	}

	if (!SpeedIsInRangeOfGear(speed, m_gear))
	{
		return false;
	}

	m_speed = speed;
	return true;
}
