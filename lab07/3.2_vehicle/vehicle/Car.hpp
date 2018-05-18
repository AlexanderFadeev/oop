#pragma once

#include "CarBrand.h"

template <typename CVehicle>
class CCar
	: public CVehicle
{
public:
	using Brand = CarBrand;

	CCar(size_t seatsCount, Brand brand);

	Brand GetBrand() const override;

private:
	Brand m_brand;
};

#include "Car.ipp"
