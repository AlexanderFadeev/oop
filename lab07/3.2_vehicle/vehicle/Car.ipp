#include "Car.hpp"
#pragma once

template<typename V>
inline CCar<V>::CCar(size_t seatsCount, Brand brand)
	: V(seatsCount)
	, m_brand(brand)
{
}

template<typename V>
inline typename CCar<V>::Brand CCar<V>::GetBrand() const
{
	return m_brand;
}
