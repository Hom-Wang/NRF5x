/* #include "nrf51_gpiote.h" */

#ifndef __NRF51_GPIOTE_H
#define __NRF51_GPIOTE_H

#include "nrf51_typedef.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
//  u8 GPIOTE_line;
//  // Line 0-3
  u32 GPIOTE_Pin;
  // Pin 0-31
  u32 GPIOTE_Mode;
  // GPIOTE_CONFIG_MODE_Disabled - Disabled.
  // GPIOTE_CONFIG_MODE_Event    - Channel configure in event mode.
  // GPIOTE_CONFIG_MODE_Task     - Channel configure in task mode.
  u32 GPIOTE_Polarity;
  // GPIOTE_CONFIG_POLARITY_LoToHi - Low to high.
  // GPIOTE_CONFIG_POLARITY_HiToLo - High to low.
  // GPIOTE_CONFIG_POLARITY_Toggle - Toggle.
  u32 GPIOTE_OutInit;
  // GPIOTE_CONFIG_OUTINIT_Low  - Initial low output when in task mode.
  // GPIOTE_CONFIG_OUTINIT_High - Initial high output when in task mode.
} GPIOTE_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Init( GPIOTE_InitTypeDef *GPIOTE_InitStruct, u8 GPIOTE_Line );
void GPIOTE_Enable( u8 GPIOTE_Line );
void GPIOTE_Disable( u8 GPIOTE_Line );
u8   GPIOTE_EvenCheck( u8 GPIOTE_Line );
void GPIOTE_EvenClear( u8 GPIOTE_Line );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
