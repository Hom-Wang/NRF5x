/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
void TIMER_DelayMS( volatile uint32_t DelayMs )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = TIMER_MODE_MODE_Timer;
  TIMER_TBInitStruct.TIMER_BitMode   = TIMER_BITMODE_BITMODE_16Bit;
  TIMER_TBInitStruct.TIMER_Prescaler = 9;  // 16Mhz / 2^9 = 16000000Hz / 512 = 31250 Hz
  TIMER_TimeBaseInit(TIMER, &TIMER_TBInitStruct);

  TIMER_CCInit(TIMER, TIMER_CH, DelayMs*31.25f);

  TIMER_Cmd(TIMER, ENABLE);
  while(TIMER_EvenCheck(TIMER, TIMER_CH) != SUCCESS);
  TIMER_EvenClear(NRF_TIMER0, TIMER_CH0);
  TIMER_Cmd(TIMER, DISABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();

  nrf_gpio_pin_clear(LED_1);
  nrf_gpio_pin_set(LED_2);
  nrf_gpio_pin_set(LED_3);
  nrf_gpio_pin_set(LED_4);

  while(1) {
    nrf_gpio_pin_toggle(LED_1);
    nrf_gpio_pin_toggle(LED_2);
    TIMER_DelayMS(DELAY_TIME);
    nrf_gpio_pin_toggle(LED_2);
    nrf_gpio_pin_toggle(LED_4);
    TIMER_DelayMS(DELAY_TIME);
    nrf_gpio_pin_toggle(LED_4);
    nrf_gpio_pin_toggle(LED_3);
    TIMER_DelayMS(DELAY_TIME);
    nrf_gpio_pin_toggle(LED_3);
    nrf_gpio_pin_toggle(LED_1);
    TIMER_DelayMS(DELAY_TIME);
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
