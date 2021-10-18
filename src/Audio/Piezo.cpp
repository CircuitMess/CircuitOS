#include "../../Setup.hpp"
#include "Notes.hpp"
#ifdef CIRCUITOS_TONE
#include "Piezo.impl"

#elif defined CIRCUITOS_PIEZO_PWM
#include "PiezoPWM.impl"

#elif defined CIRCUITOS_PIEZO_DAC
#include "PiezoDAC.impl"
#endif