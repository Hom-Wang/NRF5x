/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_timer.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DELAY_TIME 80

#define TIMER     NRF_TIMER0
#define TIMER_CH  TIMER_CH0

void TIMER_DelayMS( __IO uint32_t DelayMs )
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

  LED_1_Set();
  LED_2_Reset();
  LED_3_Reset();
  LED_4_Reset();

  while(1) {
    LED_1_Toggle();
    LED_2_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED_2_Toggle();
    LED_4_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED_4_Toggle();
    LED_3_Toggle();
    TIMER_DelayMS(DELAY_TIME);
    LED_3_Toggle();
    LED_1_Toggle();
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
