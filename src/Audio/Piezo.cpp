#include "../../Setup.hpp"

#ifdef CIRCUITOS_TONE
#include "Piezo.impl"
#else
#ifdef CIRCUITOS_I2S
#include "Piezo_I2S.impl"
#endif
#endif