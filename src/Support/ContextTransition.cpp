#include "../../Setup.hpp"

#ifdef CIRCUITOS_LOWRAM
	#include "LowRamContextTransition.impl"
#else
	#include "StandardContextTransition.impl"
#endif