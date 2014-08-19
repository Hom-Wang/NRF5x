/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "experiment_nrf51.h"
#include "module_sf595.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  u8 Count = 0;
  u8 State = 0;

  GPIO_Config();

  SF595_Config();
  SF595_Init();

  nrf_gpio_pin_toggle(LED_0);
  nrf_gpio_pin_toggle(LED_1);
  Delay_10ms(10);

  while(1) {
    nrf_gpio_pin_toggle(LED_0);
    nrf_gpio_pin_toggle(LED_1);
    Delay_10ms(10);

    Count++;

    switch (State) {

        case 0:
          if (Count == 8) {
            SF595_Shift(0);
            State = 1;
          }
          else {
            SF595_Shift(0);
          }
          break;

        case 1:
          if (Count == 16) {
            SF595_Shift(1);
            State = 2;
          }
          else {
            SF595_Shift(1);
          }
          break;

        case 2:
          for(; State>0; State--) {
            SF595_SendByte(0x00);
            Delay_100ms(2);
            SF595_SendByte(0xFF);
            Delay_100ms(2);
          }
          Count = 0;
          break;
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(0, 7);              // Pin 00-07 - output
  nrf_gpio_range_cfg_output(LED_0, LED_1);      // Pin 18-19 - output
  nrf_gpio_cfg_input(KEY, NRF_GPIO_PIN_PULLUP); // Pin 20    - input
}
/*====================================================================================================*/
/*====================================================================================================*/
