
/** ### Features ### */
// #define CIRCUITOS_FREERTOS // Uncomment this line if you're compiling for a core with FreeRTOS

/** Task and synchronization classes are only available if we're compiling with FreeRTOS */
#ifdef CIRCUITOS_FREERTOS
#define CIRCUITOS_TASK
#define CIRCUITOS_MUTEX
#define CIRCUITOS_BINARY_SEMAPHORE
#define CIRCUITOS_SEMAPHORE
#define CIRCUITOS_QUEUE
#endif

/** Use the LovyanGFX library (https://github.com/lovyan03/LovyanGFX) instead of TFT_eSPI
 * The library has better performance on higher-res screens (320x240 and above). */
 #define CIRCUITOS_LOVYANGFX

/** Whether NVS (non-volatile storage) is present in the core. Enables NVS variant of Settings */
// #define CIRCUITOS_NVS

/** Whether LittleFS library is available. Enables LittleFS variant of Settings */
// #define CIRCUITOS_LITTLEFS

/** Whether global `tone` and `noTone` functions are available. Required for Audio/Piezo */
// #define CIRCUITOS_TONE

/** Enable Piezo for ESP32 using timed interrupts */
// #define CIRCUITOS_PIEZO_ESP32
#define CIRCUITOS_PIEZO_ESP32_PWM_CHANNEL 0

/** Context transitions for devices with little RAM won't keep both context sprites in RAM at the same time. */
// #define CIRCUITOS_LOWRAM

/** ### Device drivers ### */
// #define CIRCUITOS_ICM20948
// #define CIRCUITOS_MPU6050
// #define CIRCUITOS_LEDMATRIX
// #define CIRCUITOS_SERIALFLASH

/** Using u8g2 fonts uses up some RAM and PROGMEM for every font used.
 * The U8g2_for_TFT_eSPI library is used. (https://github.com/Bodmer/U8g2_for_TFT_eSPI)*/
// #define CIRCUITOS_U8G2FONTS

/** Using WiFi **/
// #define CIRCUITOS_NET
