/* #include "nrf51_delay.h" */

#ifndef __NRF51_DELAY_H
#define __NRF51_DELAY_H

#include "nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
void Delay_1us( volatile uint32_t nCnt_1us );
void Delay_10us( volatile uint32_t  nCnt_10us );
void Delay_100us( volatile uint32_t  nCnt_100us );
void Delay_1ms( volatile uint32_t  nCnt_1ms );
void Delay_10ms( volatile uint32_t  nCnt_10ms );
void Delay_100ms( volatile uint32_t  nCnt_100ms );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
