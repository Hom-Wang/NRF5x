/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_gpiote.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  GPIOTE_Config();

  Delay_100ms(1);

  while(1) {
    nrf_gpio_pin_toggle(LED_3);
    nrf_gpio_pin_toggle(LED_4);
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
void GPIOTE_Config( void )
{
  GPIOTE_InitTypeDef GPIOTE_InitStruct;

  GPIOTE_InitStruct.GPIOTE_Pin = KEY_1;                               // 
  GPIOTE_InitStruct.GPIOTE_Mode = GPIOTE_CONFIG_MODE_Event;           // output
  GPIOTE_InitStruct.GPIOTE_Polarity = GPIOTE_CONFIG_POLARITY_HiToLo;  // high to low
  GPIOTE_Init(KEY_EL1, &GPIOTE_InitStruct);                           // CH0

  GPIOTE_InitStruct.GPIOTE_Pin = KEY_2;                               // 
  GPIOTE_InitStruct.GPIOTE_Mode = GPIOTE_CONFIG_MODE_Event;           // output
  GPIOTE_InitStruct.GPIOTE_Polarity = GPIOTE_CONFIG_POLARITY_HiToLo;  // high to low
  GPIOTE_Init(KEY_EL2, &GPIOTE_InitStruct);                           // CH1

  NVIC_EnableIRQ(GPIOTE_IRQ);
}
/*====================================================================================================*/
/*====================================================================================================*/
