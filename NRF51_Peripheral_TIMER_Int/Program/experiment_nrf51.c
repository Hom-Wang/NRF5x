/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_timer.h"

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
  TIMER_Config();

  LED1_Reset();
  LED2_Reset();
  LED3_Reset();
  LED4_Reset();
}
int main( void )
{
  System_Init();

  while(1) {
    LED2_Toggle();
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
/*====================================================================================================*/
/*====================================================================================================*/
void TIMER_Config( void )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = NRF_TIMER_MODE_TIMER;
  TIMER_TBInitStruct.TIMER_BitMode   = NRF_TIMER_BIT_WIDTH_16;
  TIMER_TBInitStruct.TIMER_Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(TIMERx, &TIMER_TBInitStruct);

  TIMER_CCInit(TIMERx, TIMERx_CH, DELAY_TIME * 31.25f);

  TIMER_Cmd(TIMERx, ENABLE);

  TIMER_CC0Interrupt(TIMERx, ENABLE);
  NVIC_SetPriority(TIMERx_IRQ, 1);
  NVIC_EnableIRQ(TIMERx_IRQ);
}
/*====================================================================================================*/
/*====================================================================================================*/
