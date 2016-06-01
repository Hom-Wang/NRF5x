/* #include "imuCube_bsp.h" */

#ifndef __IMUCUBE_BSP_H
#define __IMUCUBE_BSP_H

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
void NRF51_CKOCK_Config( void );
void NRF51_GPIO_Config( void );
void NRF51_UART_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
