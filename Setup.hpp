
/** ### Features ### */
// #define CIRCUITOS_FREERTOS // Uncomment this line if you're compiling for a core with FreeRTOS

/** Task and synchronization classes are only available if we're compiling with FreeRTOS */
#ifdef CIRCUITOS_FREERTOS
#define CIRCUITOS_TASK
#define CIRCUITOS_MUTEX
#define CIRCUITOS_BINARY_SEMAPHORE
#define CIRCUITOS_QUEUE
#endif

/** Whether NVS (non-volatile storage) is present in the core. Required for Settings */
// #define CIRCUITOS_NVS

/** ### Device drivers ### */
// #define CIRCUITOS_ICM20948
// #define CIRCUITOS_MPU6050
