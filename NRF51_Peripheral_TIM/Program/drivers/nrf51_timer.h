/* #include "nrf51_timer.h" */

#ifndef __NRF51_TIMER_H
#define __NRF51_TIMER_H

#include "nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef enum {
  TIMER_CH0 = 0,
  TIMER_CH1,
  TIMER_CH2,
  TIMER_CH3
} TIMER_CH_TypeDef;

typedef struct {
  uint32_t TIMER_Prescaler;
  // Prescaler 0~9 - F_Timer = HFCLK / 2^Prescaler
  uint32_t TIMER_Mode;
  // TIMER_MODE_MODE_Timer   - Timer in Normal mode.
  // TIMER_MODE_MODE_Counter - Timer in Counter mode.
  uint32_t TIMER_BitMode;
  // TIMER_BITMODE_BITMODE_08Bit -  8-bit timer behaviour.
  // TIMER_BITMODE_BITMODE_16Bit - 16-bit timer behaviour.
  // TIMER_BITMODE_BITMODE_24Bit - 24-bit timer behaviour.
  // TIMER_BITMODE_BITMODE_32Bit - 32-bit timer behaviour.
} TIMER_TimeBaseInitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void    TIMER_TimeBaseInit( NRF_TIMER_Type *TIMERx, TIMER_TimeBaseInitTypeDef *TIMER_TBInitStruct );
void    TIMER_Cmd( NRF_TIMER_Type *TIMERx, FunctionalState NewState );
void    TIMER_TimerClear( NRF_TIMER_Type *TIMERx );
void    TIMER_CCInit( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH, volatile uint32_t TIMER_CC );
uint8_t TIMER_EvenCheck( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH );
void    TIMER_EvenClear( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH );
void    TIMER_CC0Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState );
void    TIMER_CC1Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState );
void    TIMER_CC2Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState );
void    TIMER_CC3Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
