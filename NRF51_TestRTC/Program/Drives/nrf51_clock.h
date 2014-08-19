/* #include "nrf51_clock.h" */

#ifndef __NRF51_CLOCK_H
#define __NRF51_CLOCK_H

#include "nrf51_typedef.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LFCLK_FREQUENCY   (32768UL)     // 32.768kHz
#define HFCLK_FREQUENCY   (16000000UL)  // 16MHz
/*====================================================================================================*/
/*====================================================================================================*/
void CLOCK_SourceLFCLK( u32 ClockSource );
void CLOCK_CmdLFCLK( FunctionalState NewState );
void CLOCK_CmdHFCLK( FunctionalState NewState );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
