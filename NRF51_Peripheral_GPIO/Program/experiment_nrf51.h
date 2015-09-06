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

#define LED_1_Set()     _GPIO_SET(LED_1)
#define LED_1_Reset()   _GPIO_RST(LED_1)
#define LED_1_Toggle()  _GPIO_TOG(LED_1)
#define LED_2_Set()     _GPIO_SET(LED_2)
#define LED_2_Reset()   _GPIO_RST(LED_2)
#define LED_2_Toggle()  _GPIO_TOG(LED_2)
#define LED_3_Set()     _GPIO_SET(LED_3)
#define LED_3_Reset()   _GPIO_RST(LED_3)
#define LED_3_Toggle()  _GPIO_TOG(LED_3)
#define LED_4_Set()     _GPIO_SET(LED_4)
#define LED_4_Reset()   _GPIO_RST(LED_4)
#define LED_4_Toggle()  _GPIO_TOG(LED_4)

#define KEY_1  17
#define KEY_2  18
#define KEY_3  19
#define KEY_4  20

#define KEY_1_Read()    (_GPIO_READ(KEY_1) == 0)
#define KEY_2_Read()    (_GPIO_READ(KEY_2) == 0)
#define KEY_3_Read()    (_GPIO_READ(KEY_3) == 0)
#define KEY_4_Read()    (_GPIO_READ(KEY_4) == 0)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
