#pragma once

#include <array>

class CCar
{
public:
	enum class MovingDirection;

	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	int GetGear() const;
	bool SetGear(int gear);
	int GetSpeed() const;
	bool SetSpeed(int speed);
	MovingDirection GetMovingDirection() const;

private:
	static const int m_minGear = -1;
	static const int m_maxGear = 5;
	static const int m_gearsCount = m_maxGear - m_minGear + 1;
	static const std::array<std::pair<int, int>, m_gearsCount> m_speedRanges;

	bool m_isTurnedOn = false;
	int m_gear = 0;
	int m_speed = 0;

	static bool SpeedIsInRangeOfGear(int speed, int gear);
	bool SetSpeedImpl(int speed);
};

enum class CCar::MovingDirection
{
	Forwards,
	Stopped,
	Backwards,
};
