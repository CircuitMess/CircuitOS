#ifndef CIRCUITOS_DEBUG_H
#define CIRCUITOS_DEBUG_H

#include <Arduino.h>

// should be set with compiler parameters
#define DEBUG

#ifdef DEBUG
	#define logln(msg) Debug::println(msg)
	#define logr(msg) Debug::print(msg)
#else
	#define logln(msg)
	#define logr(msg)
#endif

class Debug {
public:
	static void println(String msg);
	static void println();
	static void print(String msg);

};

#endif //CIRCUITOS_DEBUG_H
