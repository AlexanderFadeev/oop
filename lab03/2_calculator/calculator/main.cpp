#include "Calculator.hpp"
#include "Controller.hpp"

int main()
{
	CCalculator calc;
	CController controller(calc);

	controller.HandleUserCommands();

	return 0;
}
