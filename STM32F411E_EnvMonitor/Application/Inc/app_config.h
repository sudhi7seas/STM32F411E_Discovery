#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "main.h"

//Task Stack Sizes (in words)
#define SENSOR_TASK_STACK_SIZE          (512)
#define DISPLAY_TASK_STACK_SIZE          (512)
#define LOGGER_TASK_STACK_SIZE          (768)
#define SYSTEM_TASK_STACK_SIZE          (256)

//Task priorities
#define SENSOR_TASK_PRIORITY             (osPriorityNormal + 1)
#define DISPLAY_TASK_PRIORITY             (osPriorityNormal)
#define LOGGER_TASK_PRIORITY			     (osPriorityNormal - 1)
#define SYSTEM_TASK_PRIORITY             (osPriorityNormal + 2)

//System Configuration
#define SENSOR_SAMPLE_RATE_MS           (1000)
#define DISPLAY_UPDATE_RATE_MS            (100)
#define LOG_WRITE_RATE_MS                     (5000)
#define SYSTEM_CHECK_RATE                      (2000)

//Sensor Thresholds
#define SOUND_THRESHOLD_HIGH       (3000)
#define SOUND_THRESHOLD_LOW       (500)
#define MOTION_DEBOUNCE_TIME_MS       (2000)

//Queue sizes
#define SENSOR_QUEUE_SIZE        (10)
#define LOG_QUEUE_SIZE      (20)
#define DISPLAY_QUEUE_SIZE     (5)










#endif
