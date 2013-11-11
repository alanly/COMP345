#include "Dice.h"

namespace Dice{

	int roleTenSideDice()
	{
		return rand() % 10 + 1;
	}

	int roleTwentySideDice()
	{
		return rand() % 20 + 1;
	}
	int roleSixSideDice()
	{
		return rand() % 6 + 1;
	}
}