cmake_minimum_required(VERSION 3.15)
project(CircuitOS)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/cm/.arduino15/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(~/Arduino/libraries/Keypad_I2Ca)
include_directories(~/Arduino/libraries/Keypad/src)
include_directories(~/Arduino/libraries/TFT_eSPI)
include_directories(~/Arduino/libraries/Time)
include_directories(~/Arduino/libraries/RTClib)
include_directories(~/Arduino/libraries/CircuitOS/src)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Bitmaps SOURCES)
AUX_SOURCE_DIRECTORY(src/Display SOURCES)
AUX_SOURCE_DIRECTORY(src/Elements SOURCES)
AUX_SOURCE_DIRECTORY(src/Input SOURCES)
AUX_SOURCE_DIRECTORY(src/RTC SOURCES)
AUX_SOURCE_DIRECTORY(src/Support SOURCES)
AUX_SOURCE_DIRECTORY(src/UI SOURCES)
AUX_SOURCE_DIRECTORY(src/Update SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)

add_definitions(-DDEBUG)
add_executable(CircuitOS ${SOURCES} CircuitOS.ino)

set(EXAMPLES ListMenu Settings RTC)

foreach(EXAMPLE ${EXAMPLES})
    AUX_SOURCE_DIRECTORY(examples/${EXAMPLE} EXAMPLE_SOURCES)
    SET_SOURCE_FILES_PROPERTIES(examples/${EXAMPLE}/${EXAMPLE}.ino PROPERTIES LANGUAGE CXX)
    add_executable(Example_${EXAMPLE} ${EXAMPLE_SOURCES} examples/${EXAMPLE}/${EXAMPLE}.ino)
endforeach(EXAMPLE)
