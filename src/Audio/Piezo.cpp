#include "../../Setup.hpp"

#ifdef CIRCUITOS_TONE
#include "Piezo.impl"
#else

#ifdef CIRCUITOS_PIEZO_PWM
#include "PiezoPWM.impl"
#endif

#endif