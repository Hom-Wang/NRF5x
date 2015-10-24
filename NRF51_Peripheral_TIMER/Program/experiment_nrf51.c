/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_timer.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DELAY_TIME  80

#define TIMERx      NRF_TIMER0
#define TIMERx_CH   TIMER_CH0

void TIMER_DelayMS( __IO uint32_t delayMs )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = NRF_TIMER_MODE_TIMER;
  TIMER_TBInitStruct.TIMER_BitMode   = NRF_TIMER_BIT_WIDTH_16;
  TIMER_TBInitStruct.TIMER_Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(TIMERx, &TIMER_TBInitStruct);

  TIMER_CCInit(TIMERx, TIMERx_CH, delayMs * 31.25f);

  TIMER_Cmd(TIMERx, ENABLE);
  while(TIMER_EvenCheck(TIMERx, TIMERx_CH) != SUCCESS);
  TIMER_EvenClear(NRF_TIMER0, TIMER_CH0);
  TIMER_Cmd(TIMERx, DISABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();

  LED1_Set();
  LED2_Reset();
  LED3_Reset();
  LED4_Reset();
}
int main( void )
{
  System_Init();

  while(1) {
    LED1_Toggle();
    LED2_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED2_Toggle();
    LED4_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED4_Toggle();
    LED3_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED3_Toggle();
    LED1_Toggle();
    TIMER_DelayMS(DELAY_TIME);
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
