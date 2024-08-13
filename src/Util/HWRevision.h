#ifndef CIRCUITOS_HWREVISION_H
#define CIRCUITOS_HWREVISION_H

#include <Arduino.h>

class HWRevision {
public:
	static uint8_t get();

	static void write(uint8_t value);

	static void commit();
	static void reset();

private:
	static bool changes;

};


#endif //CIRCUITOS_HWREVISION_H
