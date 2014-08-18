/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_delay.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_PORT  (*((vu8*)(&(NRF_GPIO->OUT))))   // Use Port0 ( Pin 0-7 )
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  u8 i = 0;

  GPIO_Config();

  #define DELAY_TIME 8
  while(1) {

    while(!nrf_gpio_pin_read(20)) {
      // Port 0 ( Pin 0-7 ) Blink
      nrf_gpio_word_byte_write(&(NRF_GPIO->OUT), NRF_GPIO_PORT_SELECT_PORT0, 0x0F);
      Delay_100ms(1);
      nrf_gpio_word_byte_write(&(NRF_GPIO->OUT), NRF_GPIO_PORT_SELECT_PORT0, 0xF0);
      Delay_100ms(1);
    }

    // Port 0 ( Pin 0-7 ) Blink
    for(i = 0; i<8; i++) {
//      nrf_gpio_word_byte_write(&(NRF_GPIO->OUT), NRF_GPIO_PORT_SELECT_PORT0, ~(0x01<<i));
      LED_PORT = ~(0x01<<i);
      Delay_10ms(DELAY_TIME);
    }
    for(i = 6; i>0; i--) {
//      nrf_gpio_word_byte_write(&(NRF_GPIO->OUT), NRF_GPIO_PORT_SELECT_PORT0, ~(0x01<<i));
      LED_PORT = ~(0x01<<i);
      Delay_10ms(DELAY_TIME);
    }

    // Pin 18, 19 Toggle
    nrf_gpio_pin_toggle(18);
    nrf_gpio_pin_toggle(19);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output( 0,  7);            // Pin 00-07 - output
  nrf_gpio_range_cfg_output(18, 19);            // Pin 18-19 - output
  nrf_gpio_cfg_input(20, NRF_GPIO_PIN_PULLUP);  // Pin 20    - input
}
/*====================================================================================================*/
/*====================================================================================================*/
