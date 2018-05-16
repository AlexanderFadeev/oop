#include "IPoliceMan.hpp"

std::ostream& operator<<(std::ostream& os, const IPoliceMan& policeMan)
{
	os << static_cast<const IPerson&>(policeMan) << " from " << policeMan.GetDepartamentName();

	return os;
}
