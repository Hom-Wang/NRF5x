/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_PORT  (*((vu8*)(&(NRF_GPIO->OUT))))   // Use Port0 ( Pin 0-7 )
/*====================================================================================================*/
/*====================================================================================================*/
#define USE_TIMER     NRF_TIMER0
#define USE_TIMER_CH  TIMER_CH0
void TIMER_DelayMS( vu16 DelayMs )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.TIMER_Mode      = TIMER_MODE_MODE_Timer;
  TIMER_TBInitStruct.TIMER_BitMode   = TIMER_BITMODE_BITMODE_16Bit;
  TIMER_TBInitStruct.TIMER_Prescaler = 9;  // 16Mhz / 2^9 = 16000000Hz / 512 = 31250 Hz
  TIMER_TimeBaseInit(USE_TIMER, &TIMER_TBInitStruct);

  TIMER_CCInit(USE_TIMER, USE_TIMER_CH, DelayMs*31.25f);

  TIMER_Cmd(USE_TIMER, ENABLE);
  while(TIMER_CompareCC(USE_TIMER, USE_TIMER_CH) != SUCCESS);
  TIMER_Cmd(USE_TIMER, DISABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  u8 i = 0;

  GPIO_Config();

  nrf_gpio_pin_set(LED_0);
  nrf_gpio_pin_clear(LED_1);

  #define DELAY_TIME 80
  while(1) {

    nrf_gpio_pin_toggle(LED_0);
    nrf_gpio_pin_toggle(LED_1);
    for(i = 0; i<7; i++) {
      LED_PORT = ~(0x01<<i);
      TIMER_DelayMS(DELAY_TIME);
    }
    nrf_gpio_pin_toggle(LED_0);
    nrf_gpio_pin_toggle(LED_1);
    for(i = 7; i>0; i--) {
      LED_PORT = ~(0x01<<i);
      TIMER_DelayMS(DELAY_TIME);
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output( 0,  7);              // Pin 00-07 - output
  nrf_gpio_range_cfg_output(LED_0, LED_1);        // Pin 18-19 - output
  nrf_gpio_cfg_input(KEY, NRF_GPIO_PIN_PULLUP);   // Pin 20    - input
}
/*====================================================================================================*/
/*====================================================================================================*/
