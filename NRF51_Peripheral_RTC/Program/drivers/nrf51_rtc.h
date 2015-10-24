/* #include "nrf51_rtc.h" */

#ifndef __NRF51_RTC_H
#define __NRF51_RTC_H

#include "nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef enum {
  RTC_CH0 = 0,
  RTC_CH1,
  RTC_CH2,
  RTC_CH3
} RTC_CH_TypeDef;

typedef struct {
  uint32_t Prescaler;
  uint32_t Period;
  RTC_CH_TypeDef Channel;
} RTC_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void    RTC_Init( NRF_RTC_Type *RTCx, RTC_InitTypeDef *RTC_InitStruct );
void    RTC_Cmd( NRF_RTC_Type *RTCx, uint8_t state );
void    RTC_CntClear( NRF_RTC_Type *RTCx );
uint8_t RTC_TickEvenCheck( NRF_RTC_Type *RTCx );
void    RTC_TickEvenClear( NRF_RTC_Type *RTCx );
uint8_t RTC_CompEvenCheck( NRF_RTC_Type *RTCx, RTC_CH_TypeDef RTCx_CH );
void    RTC_CompEvenClear( NRF_RTC_Type *RTCx, RTC_CH_TypeDef RTCx_CH );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
