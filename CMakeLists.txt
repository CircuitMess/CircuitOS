cmake_minimum_required(VERSION 3.15)
project(CircuitOS)
set(PORT /dev/ttyUSB0)
set(DEVICE cm:esp32:spencer) # Arduino device FQBN
set(CMAKE_CXX_STANDARD 11)

if(WIN32 OR CYGWIN)
    set(Arduino15 $ENV{APPDATA}/../Local/Arduino15)
    set(ArduinoLibs $ENV{USERPROFILE}/Documents/Arduino/libraries)

    string(REPLACE "\\" "/" Arduino15 ${Arduino15})
    string(REPLACE "\\" "/" ArduinoLibs ${ArduinoLibs})

    if(${CYGWIN})
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" Arduino15 ${Arduino15})
        string(REGEX REPLACE "^([A-Za-z]):" "/cygdrive/\\1" ArduinoLibs ${ArduinoLibs})
    endif()
else()
    set(Arduino15 ~/.arduino15)
    set(ArduinoLibs ~/Arduino/libraries)
endif()

# ESP32
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/cores/esp32)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/esp32)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/freertos)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/spi_flash)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/nvs_flash)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/driver)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/tools/sdk/include/driver/driver)

# ESP8266
include_directories(${Arduino15}/packages/esp8266/hardware/esp8266/2.7.1/cores/esp8266)
include_directories(${Arduino15}/packages/esp8266/hardware/esp8266/2.7.1/libraries/LittleFS/src)

# Package libs
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/Wire/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/FS/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/SD/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/SPI/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/WiFi/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/SPIFFS/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/HTTPClient/src)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/TFT_eSPI)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/TFT_eSPI/Extensions)
include_directories(${Arduino15}/packages/cm/hardware/esp32/1.1.1/libraries/heatshrink)

# External libs
include_directories(${ArduinoLibs}/Keypad_I2Ca)
include_directories(${ArduinoLibs}/Keypad/src)
include_directories(${ArduinoLibs}/I2Cdev)
include_directories(${ArduinoLibs}/MPU6050)
include_directories(${ArduinoLibs}/SparkFun_ICM20948/src)

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(src/Audio SOURCES)
AUX_SOURCE_DIRECTORY(src/Bitmaps SOURCES)
AUX_SOURCE_DIRECTORY(src/Buffer SOURCES)
AUX_SOURCE_DIRECTORY(src/Devices SOURCES)
AUX_SOURCE_DIRECTORY(src/Devices/Motion SOURCES)
AUX_SOURCE_DIRECTORY(src/Devices/SerialFlash SOURCES)
AUX_SOURCE_DIRECTORY(src/Devices/LEDmatrix SOURCES)
AUX_SOURCE_DIRECTORY(src/Display SOURCES)
AUX_SOURCE_DIRECTORY(src/Elements SOURCES)
AUX_SOURCE_DIRECTORY(src/FS SOURCES)
AUX_SOURCE_DIRECTORY(src/Input SOURCES)
AUX_SOURCE_DIRECTORY(src/Loop SOURCES)
AUX_SOURCE_DIRECTORY(src/Motion SOURCES)
set(SOURCES ${SOURCES} src/Motion/Fusion.hpp)
AUX_SOURCE_DIRECTORY(src/Support SOURCES)
AUX_SOURCE_DIRECTORY(src/Sync SOURCES)
AUX_SOURCE_DIRECTORY(src/UI SOURCES)
AUX_SOURCE_DIRECTORY(src/Util SOURCES)
AUX_SOURCE_DIRECTORY(src/Network SOURCES)

add_definitions(-DDEBUG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(BUILD ${ROOT}/build)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_PROJECT_NAME}.ino PROPERTIES LANGUAGE CXX)

add_custom_command(OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.ino.elf
        COMMAND arduino-cli compile --fqbn ${DEVICE} --output-dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_SOURCE_DIR}
        DEPENDS ${CMAKE_PROJECT_NAME}.ino ${SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(CMBuild
        SOURCES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.ino.elf)

add_custom_target(CMUpload ALL
        COMMAND arduino-cli upload --fqbn ${DEVICE} -p ${PORT} --input-dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS CMBuild
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.ino ${SOURCES})

set(EXAMPLES ListMenu Settings Mutex Queue Motion)

foreach(EXAMPLE ${EXAMPLES})
    AUX_SOURCE_DIRECTORY(examples/${EXAMPLE} EXAMPLE_SOURCES)
    AUX_SOURCE_DIRECTORY(examples/${EXAMPLE}/src EXAMPLE_SOURCES)
    SET_SOURCE_FILES_PROPERTIES(examples/${EXAMPLE}/${EXAMPLE}.ino PROPERTIES LANGUAGE CXX)
    add_executable(Example_${EXAMPLE} ${EXAMPLE_SOURCES} examples/${EXAMPLE}/${EXAMPLE}.ino)
endforeach(EXAMPLE)
