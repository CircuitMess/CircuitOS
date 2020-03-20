#include "Debug.h"

void Debug::println(String msg){
#ifdef DEBUG
	Serial.println(msg);
#endif
}

void Debug::println(){
#ifdef DEBUG
	Serial.println();
#endif
}

void Debug::print(String msg){
#ifdef DEBUG
	Serial.print(msg);
#endif
}
