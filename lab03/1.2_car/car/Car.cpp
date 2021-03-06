#include "Car.hpp"
#include <cmath>

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

const std::array<std::pair<int, int>, CCar::m_gearsCount> CCar::m_speedRanges{ {
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

bool CCar::SpeedIsInRangeOfGear(int speed, int gear)
{
	if (gear < m_minGear || m_maxGear < gear)
	{
		return false;
	}

	auto& range = m_speedRanges[gear - m_minGear];
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
	return std::abs(m_speed);
}

bool CCar::SetSpeedImpl(int speed)
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

bool CCar::SetSpeed(int speed)
{
	if (m_gear < 0 || m_speed < 0)
	{
		return SetSpeedImpl(-speed);
	}

	return SetSpeedImpl(speed);
}

CCar::MovingDirection CCar::GetMovingDirection() const
{
	if (m_speed > 0)
	{
		return MovingDirection::Forwards;
	}

	if (m_speed < 0)
	{
		return MovingDirection::Backwards;
	}

	return MovingDirection::Stopped;
}
