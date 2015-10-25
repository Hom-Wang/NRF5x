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
  uint32_t Prescaler;
  // NRF_TIMER_FREQ_16MHz   - Timer frequency 16 MHz.
  // NRF_TIMER_FREQ_8MHz    - imer frequency 8 MHz.
  // NRF_TIMER_FREQ_4MHz    - Timer frequency 4 MHz.
  // NRF_TIMER_FREQ_2MHz    - Timer frequency 2 MHz.
  // NRF_TIMER_FREQ_1MHz    - Timer frequency 1 MHz.
  // NRF_TIMER_FREQ_500kHz  - Timer frequency 500 kHz.
  // NRF_TIMER_FREQ_250kHz  - Timer frequency 250 kHz.
  // NRF_TIMER_FREQ_125kHz  - Timer frequency 125 kHz.
  // NRF_TIMER_FREQ_62500Hz - Timer frequency 62500 Hz.
  // NRF_TIMER_FREQ_31250Hz - Timer frequency 31250 Hz.
  uint32_t Mode;
  // NRF_TIMER_MODE_TIMER   - Timer in Normal mode.
  // NRF_TIMER_MODE_COUNTER - Timer in Counter mode.
  uint32_t BitWidth;
  // NRF_TIMER_BIT_WIDTH_8  -  8-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_16 - 16-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_24 - 24-bit timer behaviour.
  // NRF_TIMER_BIT_WIDTH_32 - 32-bit timer behaviour.
} TIMER_TimeBaseInitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void    TIMER_TimeBaseInit( NRF_TIMER_Type *TIMERx, TIMER_TimeBaseInitTypeDef *TIMER_TBInitStruct );
void    TIMER_Cmd( NRF_TIMER_Type *TIMERx, uint8_t state );
void    TIMER_TimerClear( NRF_TIMER_Type *TIMERx );
void    TIMER_CCInit( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH, __IO uint32_t TIMER_CC );
uint8_t TIMER_EvenCheck( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH );
void    TIMER_EvenClear( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH );
void    TIMER_CC0Interrupt( NRF_TIMER_Type *TIMERx, uint8_t state );
void    TIMER_CC1Interrupt( NRF_TIMER_Type *TIMERx, uint8_t state );
void    TIMER_CC2Interrupt( NRF_TIMER_Type *TIMERx, uint8_t state );
void    TIMER_CC3Interrupt( NRF_TIMER_Type *TIMERx, uint8_t state );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
