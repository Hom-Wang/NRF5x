/* #include "experiment_nrf51.h" */

#ifndef __EXPERIMENT_NRF51_H
#define __EXPERIMENT_NRF51_H

#include "drivers\nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_1  21
#define LED_2  22
#define LED_3  23
#define LED_4  24

#define LED1_Set()    __GPIO_SET(LED_1)
#define LED1_Reset()  __GPIO_RST(LED_1)
#define LED1_Toggle() __GPIO_TOG(LED_1)
#define LED2_Set()    __GPIO_SET(LED_2)
#define LED2_Reset()  __GPIO_RST(LED_2)
#define LED2_Toggle() __GPIO_TOG(LED_2)
#define LED3_Set()    __GPIO_SET(LED_3)
#define LED3_Reset()  __GPIO_RST(LED_3)
#define LED3_Toggle() __GPIO_TOG(LED_3)
#define LED4_Set()    __GPIO_SET(LED_4)
#define LED4_Reset()  __GPIO_RST(LED_4)
#define LED4_Toggle() __GPIO_TOG(LED_4)

#define KEY_1  17
#define KEY_2  18
#define KEY_3  19
#define KEY_4  20

#define KEY1_Read()   (__GPIO_READ(KEY_1) == 0)
#define KEY2_Read()   (__GPIO_READ(KEY_2) == 0)
#define KEY3_Read()   (__GPIO_READ(KEY_3) == 0)
#define KEY4_Read()   (__GPIO_READ(KEY_4) == 0)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
