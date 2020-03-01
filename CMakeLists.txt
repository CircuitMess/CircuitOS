cmake_minimum_required(VERSION 3.15)
project(CircuitOS)

set(CMAKE_CXX_STANDARD 14)

include_directories(/home/cm/.arduino15/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(~/Arduino/libraries/TFT_eSPI-master)

include_directories(.)
include_directories(src)
include_directories(src/Display)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Display SOURCES)

add_executable(CircuitOS.elf ${SOURCES} OSTest.ino)
