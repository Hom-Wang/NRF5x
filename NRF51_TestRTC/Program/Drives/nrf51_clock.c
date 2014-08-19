/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_clock.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_SourceLFCLK
**功能 : Set Low Frequency Clock Source
**輸入 : ClockSource
**輸出 : None
**使用 : CLOCK_SourceLFCLK(CLOCK_LFCLKSRC_SRC_Synth);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_SourceLFCLK( u32 ClockSource )
{
  NRF_CLOCK->LFCLKSRC = (ClockSource << CLOCK_LFCLKSRC_SRC_Pos);
  // CLOCK_LFCLKSRC_SRC_RC    - Internal 32KiHz RC oscillator.
  // CLOCK_LFCLKSRC_SRC_Xtal  - External 32KiHz crystal.
  // CLOCK_LFCLKSRC_SRC_Synth - Internal 32KiHz synthesizer from HFCLK system clock.
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_CmdLFCLK
**功能 : Enable / Disable Low Frequency Clock
**輸入 : NewState
**輸出 : None
**使用 : CLOCK_CmdLFCLK(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_CmdLFCLK( FunctionalState NewState )
{
  if(NewState == ENABLE) {
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;
    while(NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
  }
  else {
    NRF_CLOCK->TASKS_LFCLKSTOP = 1;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_CmdHFCLK
**功能 : Enable / Disable High Frequency Clock
**輸入 : NewState
**輸出 : None
**使用 : CLOCK_CmdHFCLK(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_CmdHFCLK( FunctionalState NewState )
{
  if(NewState == ENABLE) {
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART    = 1;
    while(NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  }
  else {
    NRF_CLOCK->TASKS_HFCLKSTOP = 1;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
