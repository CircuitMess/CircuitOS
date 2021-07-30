
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

/** Whether NVS (non-volatile storage) is present in the core. Enables NVS variant of Settings */
// #define CIRCUITOS_NVS

/** Whether LittleFS library is available. Enables LittleFS variant of Settings */
// #define CIRCUITOS_LITTLEFS

/** Whether global `tone` and `noTone` functions are available. Required for Audio/Piezo */
// #define CIRCUITOS_TONE

/** If I2S amplifier chip is present (e.g. TFA9882UK). Required for Audio/Piezo */
// #define CIRCUITOS_I2S

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