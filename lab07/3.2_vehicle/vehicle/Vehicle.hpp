#pragma once

#include "VehicleBase.hpp"
#include <memory>
#include <vector>

template <typename IVehicle, typename IPassenger>
class CVehicle
	: public CVehicleBase
	, public IVehicle
{
public:
	using IPassengerSPtr = std::shared_ptr<IPassenger>;

	CVehicle(size_t seatsCount);
	
	virtual const IPassenger& GetPassenger(size_t index) const override;

	virtual void AddPassenger(std::shared_ptr<IPassenger> pPassenger) override;
	virtual void RemovePassenger(size_t index) override;
	virtual void RemoveAllPassengers() override;

#pragma region Fix For Warning 4250: inherits via dominance
	virtual bool IsEmpty() const override;
	virtual bool IsFull() const override;
	virtual size_t GetSeatsCount() const override;
	virtual size_t GetPassengersCount() const override;
#pragma endregion

private:
	std::vector<IPassengerSPtr> m_passengers;
	size_t m_capacity;
};

#include "Vehicle.ipp"