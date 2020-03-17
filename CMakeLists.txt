cmake_minimum_required(VERSION 3.15)
project(CircuitOS)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/cm/.arduino15/packages/cm/hardware/esp32/1.0.4/cores/esp32)
include_directories(~/Arduino/libraries/TFT_eSPI-master)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Display SOURCES)
AUX_SOURCE_DIRECTORY(src/UI SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)

add_executable(CircuitOS.elf ${SOURCES} OSTest.ino src/UI/Element.cpp src/UI/Element.h src/Display/Color.h src/UI/Image.cpp src/UI/Image.h src/UI/Screen.cpp src/UI/Screen.h src/Util/Vector.h src/UI/ElementContainer.h src/UI/Layout.cpp src/UI/Layout.h src/UI/LinearLayout.cpp src/UI/LinearLayout.h src/UI/ElementContainer.cpp)
