#include "../../Setup.hpp"
#include "ContextTransition.h"

bool ContextTransition::transitionRunning = false;

bool ContextTransition::isRunning(){
	return transitionRunning;
}
#ifdef CIRCUITOS_LOWRAM
	#include "LowRamContextTransition.impl"
#else
	#include "StandardContextTransition.impl"
#endif