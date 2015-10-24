/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"

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
}
int main( void )
{
  System_Init();

  while(1) {
    LED3_Set();
    LED1_Reset();
    Delay_10ms(8);
    while(KEY1_Read()) {
      LED1_Toggle();
      Delay_10ms(8);
    }
    LED1_Set();
    LED2_Reset();
    Delay_10ms(8);
    while(KEY2_Read()) {
      LED2_Toggle();
      Delay_10ms(8);
    }
    LED2_Set();
    LED4_Reset();
    Delay_10ms(8);
    while(KEY4_Read()) {
      LED4_Toggle();
      Delay_10ms(8);
    }
    LED4_Set();
    LED3_Reset();
    Delay_10ms(8);
    while(KEY3_Read()) {
      LED3_Toggle();
      Delay_10ms(8);
    }
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
