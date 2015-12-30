/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_clock.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_SourceXTAL
**功能 : Select Frequency of External XTAL
**輸入 : ClockSource
**輸出 : None
**使用 : CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_SourceXTAL( uint32_t clockSource )
{
  NRF_CLOCK->XTALFREQ = (uint32_t)((clockSource << CLOCK_XTALFREQ_XTALFREQ_Pos) & CLOCK_XTALFREQ_XTALFREQ_Msk);
  // NRF_CLOCK_XTALFREQ_16MHz - 16 MHz crystal.
  // NRF_CLOCK_XTALFREQ_32MHz - 32 MHz crystal.
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_SourceLFCLK
**功能 : Set Low Frequency Clock Source
**輸入 : ClockSource
**輸出 : None
**使用 : CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_SourceLFCLK( uint32_t clockSource )
{
  NRF_CLOCK->LFCLKSRC = (uint32_t)((clockSource << CLOCK_LFCLKSRC_SRC_Pos) & CLOCK_LFCLKSRC_SRC_Msk);
  // NRF_CLOCK_LF_SRC_RC    - Internal 32KiHz RC oscillator.
  // NRF_CLOCK_LF_SRC_Xtal  - External 32KiHz crystal.
  // NRF_CLOCK_LF_SRC_Synth - Internal 32KiHz synthesizer from HFCLK system clock.
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : CLOCK_CmdLFCLK
**功能 : Enable / Disable Low Frequency Clock
**輸入 : state
**輸出 : None
**使用 : CLOCK_CmdLFCLK(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_CmdLFCLK( uint8_t state )
{
  if(state == ENABLE) {
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
**輸入 : state
**輸出 : None
**使用 : CLOCK_CmdHFCLK(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void CLOCK_CmdHFCLK( uint8_t state )
{
  if(state == ENABLE) {
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
