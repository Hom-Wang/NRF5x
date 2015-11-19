/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_spi.h"
#include "modules\module_serial.h"
#include "modules\module_ili9341.h"

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
  Serial_Config();
  ILI9341_Config();

  Delay_100ms(1);
  ILI9341_Init();
  Delay_100ms(2);
}
int main( void )
{
  System_Init();

  LCD_TestColoBar();

  while(1) {
    LED4_Toggle();
    Delay_100ms(5);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_1, LED_4);
  nrf_gpio_range_cfg_input(KEY_1, KEY_4, NRF_GPIO_PIN_PULLUP);

  LED1_Set();
  LED2_Set();
  LED3_Set();
  LED4_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
