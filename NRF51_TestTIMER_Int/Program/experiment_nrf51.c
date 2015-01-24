/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  TIMER_Config();

  nrf_gpio_pin_clear(LED_1);
  nrf_gpio_pin_set(LED_2);
  nrf_gpio_pin_set(LED_3);
  nrf_gpio_pin_set(LED_4);

  while(1) {
    nrf_gpio_pin_toggle(LED_2);
    Delay_10ms(8);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_1, LED_4);
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIMER_Config( void )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = TIMER_MODE_MODE_Timer;
  TIMER_TBInitStruct.TIMER_BitMode   = TIMER_BITMODE_BITMODE_16Bit;
  TIMER_TBInitStruct.TIMER_Prescaler = 9;  // 16Mhz / 2^9 = 16000000Hz / 512 = 31250 Hz
  TIMER_TimeBaseInit(TIMER, &TIMER_TBInitStruct);

  TIMER_CCInit(TIMER, TIMER_CH, DELAY_TIME*31.25f);

  TIMER_Cmd(TIMER, ENABLE);

  TIMER_CC0Interrupt(TIMER, ENABLE);
  NVIC_SetPriority(TIMER_IRQ, 1);
  NVIC_EnableIRQ(TIMER_IRQ);
}
/*====================================================================================================*/
/*====================================================================================================*/
