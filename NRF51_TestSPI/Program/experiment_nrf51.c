/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_spi.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint8_t i = 0;

  GPIO_Config();
  SPI_Config();

  Delay_100ms(2);

  if(SPI_RW(NRF_SPI0, 0x01) == 0x01)  nrf_gpio_pin_toggle(LED_1); Delay_100ms(2);
  if(SPI_RW(NRF_SPI0, 0x02) == 0x02)  nrf_gpio_pin_toggle(LED_2); Delay_100ms(2);
  if(SPI_RW(NRF_SPI0, 0x03) == 0x03)  nrf_gpio_pin_toggle(LED_3); Delay_100ms(2);
  if(SPI_RW(NRF_SPI0, 0x04) == 0x04)  nrf_gpio_pin_toggle(LED_4); Delay_100ms(2);

  while(1) {
    if(SPI_RW(NRF_SPI0, i) == i) {
      nrf_gpio_pin_toggle(LED_1);
      if(++i == 0xFF) i = 0x00;
    }
    Delay_10ms(5);
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
void SPI_Config( void )
{
  SPI_InitTypeDef SPI_InitStruct;

  SPI_Cmd(NRF_SPI0, DISABLE);

//  SPI_InitStruct.SPI_PinCS     = 9;
  SPI_InitStruct.SPI_PinSCK    = 10;
  SPI_InitStruct.SPI_PinMOSI   = 11;  // MOSI should be connected to MISO
  SPI_InitStruct.SPI_PinMISO   = 12;  // MOSI should be connected to MISO
  SPI_InitStruct.SPI_CPHA      = SPI_CONFIG_CPHA_Leading;
  SPI_InitStruct.SPI_CPOL      = SPI_CONFIG_CPOL_ActiveHigh;
  SPI_InitStruct.SPI_BitOrder  = SPI_CONFIG_ORDER_MsbFirst;
  SPI_InitStruct.SPI_Freguency = SPI_FREQUENCY_FREQUENCY_M8;
  SPI_Init(NRF_SPI0, &SPI_InitStruct);

  nrf_gpio_cfg_output(SPI_InitStruct.SPI_PinSCK);
  nrf_gpio_cfg_output(SPI_InitStruct.SPI_PinMOSI);
  nrf_gpio_cfg_input(SPI_InitStruct.SPI_PinMISO, NRF_GPIO_PIN_NOPULL);

  SPI_EvenClear(NRF_SPI0);
  SPI_Cmd(NRF_SPI0, ENABLE);

  SPI_RW(NRF_SPI0, 0x00); // Tx Buf
}
/*====================================================================================================*/
/*====================================================================================================*/
