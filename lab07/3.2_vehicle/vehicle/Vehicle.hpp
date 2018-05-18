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
	
	const IPassenger& GetPassenger(size_t index) const override;

	void AddPassenger(std::shared_ptr<IPassenger> pPassenger) override;
	void RemovePassenger(size_t index) override;
	void RemoveAllPassengers() override;

#pragma region Fix For Warning 4250: inherits via dominance
	bool IsEmpty() const override;
	bool IsFull() const override;
	size_t GetSeatsCount() const override;
	size_t GetPassengersCount() const override;
#pragma endregion

private:
	std::vector<IPassengerSPtr> m_passengers;
	size_t m_capacity;
};

#include "Vehicle.ipp"