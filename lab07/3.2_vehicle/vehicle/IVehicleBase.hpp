#pragma once

class IVehicleBase
{
public:
	virtual ~IVehicleBase() = default;

	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual size_t GetSeatsCount() const = 0;
	virtual size_t GetPassengersCount() const = 0;

	virtual void RemovePassenger(size_t index) = 0;
	virtual void RemoveAllPassengers() = 0;
};