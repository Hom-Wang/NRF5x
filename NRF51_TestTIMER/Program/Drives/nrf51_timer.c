/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_TimeBaseInit
**功能 : Timer TimeBase Init
**輸入 : TIMER_TBInitStruct
**輸出 : None
**使用 : TIMER_TimeBaseInit(NRF_TIMER0, &TIMER_TimeBaseInitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_TimeBaseInit( NRF_TIMER_Type *TIMERx, TIMER_TimeBaseInitTypeDef *TIMER_TBInitStruct )
{
//  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART    = 1;

  while(NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);

  TIMERx->MODE        = TIMER_TBInitStruct->TIMER_Mode;
  TIMERx->PRESCALER   = TIMER_TBInitStruct->TIMER_Prescaler;
  TIMERx->BITMODE     = TIMER_TBInitStruct->TIMER_BitMode;
  TIMERx->TASKS_CLEAR = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_Cmd
**功能 : Enable / Disable Timer
**輸入 : TIMERx, NewState
**輸出 : None
**使用 : TIMER_Cmd(NRF_TIMER0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_Cmd( NRF_TIMER_Type *TIMERx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    TIMERx->TASKS_START = 1;
  else
    TIMERx->TASKS_STOP = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CCInit
**功能 : TIMER CC Init
**輸入 : TIMERx, TIMER_CH, TIMER_CC
**輸出 : None
**使用 : TIMER_CCInit(NRF_TIMER0, TIMER_CH0, 1000);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_CCInit( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH, vu32 TIMER_CC )
{
  TIMERx->CC[TIMER_CH] = TIMER_CC;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CCInit
**功能 : TIMER CC Init
**輸入 : TIMERx, TIMER_CH
**輸出 : State
**使用 : while(TIMER_CompareCC != SUCCESS);
**====================================================================================================*/
/*====================================================================================================*/
u8 TIMER_CompareCC( NRF_TIMER_Type *TIMERx, TIMER_CH_TypeDef TIMER_CH )
{
  if(TIMERx->EVENTS_COMPARE[TIMER_CH] != 0) {
    TIMERx->EVENTS_COMPARE[TIMER_CH] = 0;
    return SUCCESS;
  }
  else {
    return ERROR;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CC0Interrupt
**功能 : Enable / Disable CC0 Interrupt
**輸入 : TIMERx, NewState
**輸出 : None
**使用 : TIMER_CC2Interrupt(NRF_TIMER0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_CC0Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    TIMERx->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
  else
    TIMERx->INTENSET = TIMER_INTENCLR_COMPARE0_Enabled << TIMER_INTENCLR_COMPARE0_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CC1Interrupt
**功能 : Enable / Disable CC1 Interrupt
**輸入 : TIMERx NewState
**輸出 : None
**使用 : TIMER_CC1Interrupt(NRF_TIMER0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_CC1Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    TIMERx->INTENSET = TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;
  else 
    TIMERx->INTENSET = TIMER_INTENCLR_COMPARE1_Enabled << TIMER_INTENCLR_COMPARE1_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CC2Interrupt
**功能 : Enable / Disable CC2 Interrupt
**輸入 : TIMERx NewState
**輸出 : None
**使用 : TIMER_CC2Interrupt(NRF_TIMER0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_CC2Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    TIMERx->INTENSET = TIMER_INTENSET_COMPARE2_Enabled << TIMER_INTENSET_COMPARE2_Pos;
  else
    TIMERx->INTENSET = TIMER_INTENCLR_COMPARE2_Enabled << TIMER_INTENCLR_COMPARE2_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIMER_CC3Interrupt
**功能 : Enable / Disable CC3 Interrupt
**輸入 : TIMERx NewState
**輸出 : None
**使用 : TIMER_CC3Interrupt(NRF_TIMER0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void TIMER_CC3Interrupt( NRF_TIMER_Type *TIMERx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    TIMERx->INTENSET = TIMER_INTENSET_COMPARE3_Enabled << TIMER_INTENSET_COMPARE3_Pos;
  else
    TIMERx->INTENSET = TIMER_INTENCLR_COMPARE3_Enabled << TIMER_INTENCLR_COMPARE3_Pos;
}
/*=====================================================================================================*/
/*=====================================================================================================*/

