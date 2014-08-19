/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  u8 i = 0;

  GPIO_Config();
  TIMER_Config();

  nrf_gpio_pin_set(LED_0);
  nrf_gpio_pin_clear(LED_1);

  while(1) {

//    nrf_gpio_pin_toggle(LED_0);
    nrf_gpio_pin_toggle(LED_1);
    for(i = 0; i<7; i++) {
      LED_PORT = ~(0x01<<i);
      Delay_1ms(DELAY_TIME);
    }
//    nrf_gpio_pin_toggle(LED_0);
    nrf_gpio_pin_toggle(LED_1);
    for(i = 7; i>0; i--) {
      LED_PORT = ~(0x01<<i);
      Delay_1ms(DELAY_TIME);
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(0,  7);               // Pin 00-07 - output
  nrf_gpio_range_cfg_output(LED_0, LED_1);        // Pin 18-19 - output
  nrf_gpio_cfg_input(KEY, NRF_GPIO_PIN_PULLUP);   // Pin 20    - input
}
/*====================================================================================================*/
/*====================================================================================================*/
void TIMER_Config( void )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = TIMER_MODE_MODE_Timer;
  TIMER_TBInitStruct.TIMER_BitMode   = TIMER_BITMODE_BITMODE_16Bit;
  TIMER_TBInitStruct.TIMER_Prescaler = 9;  // 16Mhz / 2^9 = 16000000Hz / 512 = 31250 Hz
  TIMER_TimeBaseInit(USE_TIMER, &TIMER_TBInitStruct);

  TIMER_CCInit(USE_TIMER, USE_TIMER_CH, DELAY_TIME*31.25f);

  TIMER_Cmd(USE_TIMER, ENABLE);

  TIMER_CC0Interrupt(USE_TIMER, ENABLE);
  NVIC_SetPriority(USE_TIMER_IRQ, 1);
  NVIC_EnableIRQ(USE_TIMER_IRQ);
}
/*====================================================================================================*/
/*====================================================================================================*/
