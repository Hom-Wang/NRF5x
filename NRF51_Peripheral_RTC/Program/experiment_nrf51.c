/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_rtc.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  RTC_Config();
}
int main( void )
{
  System_Init();

  while(1) {
    LED4_Toggle();
    Delay_10ms(8);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_1, LED_4);
  nrf_gpio_range_cfg_input(KEY_1, KEY_4, NRF_GPIO_PIN_PULLUP);
}

void RTC_Config( void )
{
  RTC_InitTypeDef RTC_InitStruct;

  RTC_InitStruct.Channel   = RTCx_CH;
  RTC_InitStruct.Prescaler = 327; // F_RTC = 32768 Hz / (327 + 1) ~ 100Hz
  RTC_InitStruct.Period    = 100; // 1 s
  RTC_Init(RTCx, &RTC_InitStruct);

  NVIC_EnableIRQ(RTCx_IRQn);
  RTC_Cmd(RTCx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
