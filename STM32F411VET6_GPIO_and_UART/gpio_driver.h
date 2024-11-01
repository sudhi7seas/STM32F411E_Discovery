#ifndef _HAL_GPIO_DRIVER_H
#define _HAL_GPIO_DRIVER_H

#include "stm32f411xe.h"  


/*************************************************************************************************************************************************************/
/*
/*                     1. Macros used for GPIO Initialization
/*
/*************************************************************************************************************************************************************/


/* GPIO Mode Settings values*/
#define GPIO_PIN_INPUT_MODE                                            ((uint32_t)0x00)
#define GPIO_PIN_OUTPUT_MODE                                           ((uint32_t)0x01)
#define GPIO_PIN_ALT_FUN_MODE                                          ((uint32_t)0x02)
#define GPIO_PIN_ANALOG_MODE                                           ((uint32_t)0x03)


/* GPIO OP type settings values*/  
#define GPIO_PIN_OP_TYPE_PUSHPULL                                      ((uint32_t)0x00)
#define GPIO_PIN_OP_TYPE_OPEN_DRAIN                                    ((uint32_t)0x01)


/* GPIO Port Output Speed values*/ 
#define GPIO_PIN_SPEED_LOW                                             ((uint32_t)0x00)
#define GPIO_PIN_SPEED_MED                                             ((uint32_t)0x01)
#define GPIO_PIN_SPEED_FAST                                            ((uint32_t)0x02)
#define GPIO_PIN_SPEED_HIGH                                            ((uint32_t)0x03)


/* GPIO Port Pull-up Pull-down setting values*/ 
#define GPIO_PIN_NO_PUSH_PULL                                          ((uint32_t)0x00)
#define GPIO_PIN_PULL_UP                                               ((uint32_t)0x01)
#define GPIO_PIN_PULL_DOWN                                             ((uint32_t)0x02)

/* GPIO PORT ADDRESS */
#define GPIO_PORT_A   GPIOA
#define GPIO_PORT_B   GPIOB
#define GPIO_PORT_C   GPIOC
#define GPIO_PORT_D   GPIOD
#define GPIO_PORT_E   GPIOE
#define GPIO_PORT_H   GPIOH

/* Macros to enable clock for different GPIO ports in RCC registers */

#define _HAL_RCC_GPIOA_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<0))
#define _HAL_RCC_GPIOB_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<1))
#define _HAL_RCC_GPIOC_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<2))
#define _HAL_RCC_GPIOD_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<3))
#define _HAL_RCC_GPIOE_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<4))
#define _HAL_RCC_GPIOH_CLK_ENABLE()         (RCC->AHB1ENR |= (1<<7))











#endif