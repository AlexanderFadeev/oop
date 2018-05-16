#include "Bus.hpp"
#include "CarBrand.h"
#include "IVehicle.hpp"
#include "Person.hpp"
#include "PoliceCar.hpp"
#include "PoliceMan.hpp"
#include "Racer.hpp"
#include "Taxi.hpp"
#include <memory>

template <typename IPassenger>
void PrintPassengersInfo(std::ostream& os, const IVehicle<IPassenger>& v)
{
	for (size_t index = 0; index < v.GetPassengersCount(); index++)
	{
		os << v.GetPassenger(index) << std::endl;
	}
}

int main()
{
	CPoliceCar policeCar(5, CarBrand::Ford);
	auto pCop1 = std::make_shared<CPoliceMan>("John Smith", "North-West Police Station");
	policeCar.AddPassenger(pCop1);

	auto pCop2 = std::make_shared<CPoliceMan>("Jim Clark", "South-East Police Station");
	policeCar.AddPassenger(pCop2);

	PrintPassengersInfo(std::cout, policeCar);

	//

	policeCar.RemovePassenger(1);

	CTaxi taxi(2, CarBrand::Toyota);
	auto pTaxiDriver = std::make_shared<CPerson>("Raja Gandhi"); 
	auto pRacer = std::make_shared<CRacer>("Michael Schumacher", 155);
	taxi.AddPassenger(pTaxiDriver);
	taxi.AddPassenger(pRacer);

	taxi.RemovePassenger(0);
	taxi.AddPassenger(pCop2);

	//

	try
	{
		taxi.AddPassenger(pTaxiDriver);

		return 1;
	}
	catch (const std::logic_error&)
	{
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}