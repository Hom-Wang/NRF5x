/* #include "experiment_nrf51.h" */

#ifndef __EXPERIMENT_NRF51_H
#define __EXPERIMENT_NRF51_H

#include "drivers\nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R  21
#define LED_G  22
#define LED_B  23

#define LEDR_Set()    __GPIO_SET(LED_R)
#define LEDR_Reset()  __GPIO_RST(LED_R)
#define LEDR_Toggle() __GPIO_TOG(LED_R)
#define LEDG_Set()    __GPIO_SET(LED_G)
#define LEDG_Reset()  __GPIO_RST(LED_G)
#define LEDG_Toggle() __GPIO_TOG(LED_G)
#define LEDB_Set()    __GPIO_SET(LED_B)
#define LEDB_Reset()  __GPIO_RST(LED_B)
#define LEDB_Toggle() __GPIO_TOG(LED_B)
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
