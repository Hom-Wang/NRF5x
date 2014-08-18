/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_gpiote.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_Init
**功能 : GPIOTE Init
**輸入 : *GPIOTE_InitStruct, GPIOTE_Line
**輸出 : None
**使用 : GPIOTE_Init(&GPIOTE_InitStruct, 0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Init( GPIOTE_InitTypeDef *GPIOTE_InitStruct, u8 GPIOTE_Line )
{
  NRF_GPIOTE->CONFIG[GPIOTE_Line] = (GPIOTE_InitStruct->GPIOTE_Pin      << GPIOTE_CONFIG_PSEL_Pos) | 
                                    (GPIOTE_InitStruct->GPIOTE_Mode     << GPIOTE_CONFIG_MODE_Pos) | 
                                    (GPIOTE_InitStruct->GPIOTE_Polarity << GPIOTE_CONFIG_POLARITY_Pos) | 
                                    (GPIOTE_InitStruct->GPIOTE_OutInit  << GPIOTE_CONFIG_OUTINIT_Pos);
  GPIOTE_Enable(GPIOTE_Line);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_Init
**功能 : Enable Interrupt
**輸入 : GPIOTE_Line
**輸出 : None
**使用 : GPIOTE_Enable(0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Enable( u8 GPIOTE_Line )
{
  switch(GPIOTE_Line) {
    case 0:
      NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;
      break;
    case 1:
      NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN1_Set << GPIOTE_INTENSET_IN1_Pos;
      break;
    case 2:
      NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN2_Set << GPIOTE_INTENSET_IN2_Pos;
      break;
    case 3:
      NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN3_Set << GPIOTE_INTENSET_IN3_Pos;
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_Disable
**功能 : Disable Interrupt
**輸入 : GPIOTE_Line
**輸出 : None
**使用 : GPIOTE_Disable(0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_Disable( u8 GPIOTE_Line )
{
  switch(GPIOTE_Line) {
    case 0:
      NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN0_Clear << GPIOTE_INTENCLR_IN0_Pos;
      break;
    case 1:
      NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN1_Clear << GPIOTE_INTENCLR_IN1_Pos;
      break;
    case 2:
      NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN2_Clear << GPIOTE_INTENCLR_IN2_Pos;
      break;
    case 3:
      NRF_GPIOTE->INTENCLR = GPIOTE_INTENCLR_IN3_Clear << GPIOTE_INTENCLR_IN3_Pos;
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_EvenCheck
**功能 : Even Check
**輸入 : GPIOTE_Line
**輸出 : State
**使用 : GPIOTE_EvenCheck(0);
**====================================================================================================*/
/*====================================================================================================*/
u8 GPIOTE_EvenCheck( u8 GPIOTE_Line )
{
  u8 State = ERROR;

  switch(GPIOTE_Line) {
    case 0:
      State = ((NRF_GPIOTE->EVENTS_IN[GPIOTE_Line] == 1) && (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk)) ? SUCCESS : ERROR;
      break;
    case 1:
      State = ((NRF_GPIOTE->EVENTS_IN[GPIOTE_Line] == 1) && (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN1_Msk)) ? SUCCESS : ERROR;
      break;
    case 2:
      State = ((NRF_GPIOTE->EVENTS_IN[GPIOTE_Line] == 1) && (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN2_Msk)) ? SUCCESS : ERROR;
      break;
    case 3:
      State = ((NRF_GPIOTE->EVENTS_IN[GPIOTE_Line] == 1) && (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN3_Msk)) ? SUCCESS : ERROR;
      break;
  }

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIOTE_EvenClear
**功能 : Even Clear
**輸入 : GPIOTE_Line
**輸出 : None
**使用 : GPIOTE_EvenClear(0);
**====================================================================================================*/
/*====================================================================================================*/
void GPIOTE_EvenClear( u8 GPIOTE_Line )
{
  NRF_GPIOTE->EVENTS_IN[GPIOTE_Line] = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*/

