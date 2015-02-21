/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();

  nrf_gpio_pin_clear(LED_1);
  nrf_gpio_pin_set(LED_2);
  nrf_gpio_pin_set(LED_3);
  nrf_gpio_pin_set(LED_4);
  Delay_100ms(10);

  while(1) {
    while(nrf_gpio_pin_read(KEY_1) == 0) {
      nrf_gpio_pin_toggle(LED_1);
      Delay_10ms(8);
    }
    while(nrf_gpio_pin_read(KEY_2) == 0) {
      nrf_gpio_pin_toggle(LED_2);
      Delay_10ms(8);
    }
    while(nrf_gpio_pin_read(KEY_3) == 0) {
      nrf_gpio_pin_toggle(LED_3);
      Delay_10ms(8);
    }
    while(nrf_gpio_pin_read(KEY_4) == 0) {
      nrf_gpio_pin_toggle(LED_4);
      Delay_10ms(8);
    }
      
    nrf_gpio_pin_toggle(LED_1);
    nrf_gpio_pin_toggle(LED_2);
    Delay_10ms(8);
    nrf_gpio_pin_toggle(LED_2);
    nrf_gpio_pin_toggle(LED_4);
    Delay_10ms(8);
    nrf_gpio_pin_toggle(LED_4);
    nrf_gpio_pin_toggle(LED_3);
    Delay_10ms(8);
    nrf_gpio_pin_toggle(LED_3);
    nrf_gpio_pin_toggle(LED_1);
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
