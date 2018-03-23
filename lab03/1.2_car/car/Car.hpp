#pragma once

class CCar
{
public:
	enum class MovingDirection;
	struct State;

	State GetState() const;
	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	int GetGear() const;
	bool SetGear(int gear);
	int GetSpeed() const;
	bool SetSpeed(int speed);
	MovingDirection GetMovingDirection() const;

private:
	bool m_isTurnedOn = false;
	int m_gear = 0;
	int m_speed = 0;

	bool SpeedIsInRangeOfGear(int speed, int gear) const;
	bool SetSpeedImpl(int speed);
};

enum class CCar::MovingDirection
{
	Forwards,
	Stopped,
	Backwards,
};

struct CCar::State
{
	bool isTurnedOn;
	int gear;
	int speed;
	MovingDirection movingDirection;
};
