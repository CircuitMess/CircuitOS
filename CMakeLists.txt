cmake_minimum_required(VERSION 3.15)
project(CircuitOS)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/cm/.arduino15/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(~/Arduino/libraries/TFT_eSPI-master)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Display SOURCES)
AUX_SOURCE_DIRECTORY(src/UI SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)
AUX_SOURCE_DIRECTORY(src/Input SOURCES)

add_definitions(-DDEBUG)

add_executable(CircuitOS ${SOURCES} CircuitOS.ino)
