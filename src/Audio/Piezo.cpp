#include "../../Setup.hpp"
#include "Notes.hpp"
#ifdef CIRCUITOS_TONE
#include "Piezo.impl"
#else

#ifdef CIRCUITOS_PIEZO_ESP32
#include "PiezoESP32.impl"
#endif

#endif