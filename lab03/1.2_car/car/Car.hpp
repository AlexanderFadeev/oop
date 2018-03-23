#pragma once

class CCar
{
public:
	struct State;

	State GetState() const;
	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	int GetGear() const;
	bool SetGear(int gear);
	int GetSpeed() const;
	bool SetSpeed(int speed);

private:
	bool m_isTurnedOn = false;
	int m_gear = 0;
	int m_speed = 0;

	bool SpeedIsInRangeOfGear(int speed, int gear) const;
	bool SetSpeedImpl(int speed);
};

struct CCar::State
{
	bool isTurnedOn;
	int gear;
	int speed;
};
