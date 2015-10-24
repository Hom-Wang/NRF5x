/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_gpiote.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_Init
**功能 : GPIOTE Init
**輸入 : *GPIOTE_InitStruct, GPIOTE_CH
**輸出 : None
**使用 : GPIOTE_Init(&GPIOTE_InitStruct, GPIOTE_CH0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Init( GPIOTE_CH_TypeDef GPIOTE_CH, GPIOTE_InitTypeDef *GPIOTE_InitStruct )
{
  NRF_GPIOTE->CONFIG[GPIOTE_CH] = (GPIOTE_InitStruct->GPIOTE_Pin      << GPIOTE_CONFIG_PSEL_Pos) | 
                                  (GPIOTE_InitStruct->GPIOTE_Mode     << GPIOTE_CONFIG_MODE_Pos) | 
                                  (GPIOTE_InitStruct->GPIOTE_Polarity << GPIOTE_CONFIG_POLARITY_Pos) | 
                                  (GPIOTE_InitStruct->GPIOTE_OutInit  << GPIOTE_CONFIG_OUTINIT_Pos);
  GPIOTE_Cmd(GPIOTE_CH, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_Cmd
**功能 : Enable / Disable Interrupt
**輸入 : GPIOTE_CH, NewState
**輸出 : None
**使用 : GPIOTE_Cmd(GPIOTE_CH0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Cmd( GPIOTE_CH_TypeDef GPIOTE_CH, FunctionalState NewState )
{
  if(NewState == ENABLE) {
    switch(GPIOTE_CH) {
      case GPIOTE_CH0:
        NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;
        break;
      case GPIOTE_CH1:
        NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Set << GPIOTE_INTENSET_IN1_Pos;
        break;
      case GPIOTE_CH2:
        NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Set << GPIOTE_INTENSET_IN2_Pos;
        break;
      case GPIOTE_CH3:
        NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Set << GPIOTE_INTENSET_IN3_Pos;
        break;
    }
  }
  else {
    switch(GPIOTE_CH) {
      case GPIOTE_CH0:
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN0_Clear << GPIOTE_INTENCLR_IN0_Pos;
        break;
      case GPIOTE_CH1:
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN1_Clear << GPIOTE_INTENCLR_IN1_Pos;
        break;
      case GPIOTE_CH2:
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN2_Clear << GPIOTE_INTENCLR_IN2_Pos;
        break;
      case GPIOTE_CH3:
        NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN3_Clear << GPIOTE_INTENCLR_IN3_Pos;
        break;
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_EvenCheck
**功能 : Even Check
**輸入 : GPIOTE_CH
**輸出 : State
**使用 : State = GPIOTE_EvenCheck(GPIOTE_CH0);
**====================================================================================================*/
/*====================================================================================================*/
uint8_t GPIOTE_EvenCheck( GPIOTE_CH_TypeDef GPIOTE_CH )
{
  return ((NRF_GPIOTE->EVENTS_IN[GPIOTE_CH] == 1) ? SUCCESS : ERROR);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_EvenClear
**功能 : Even Clear
**輸入 : GPIOTE_CH
**輸出 : None
**使用 : GPIOTE_EvenClear(GPIOTE_CH0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_EvenClear( GPIOTE_CH_TypeDef GPIOTE_CH )
{
  NRF_GPIOTE->EVENTS_IN[GPIOTE_CH] = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*/

