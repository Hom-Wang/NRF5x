/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_spi.h"
#include "modules\module_serial.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define USE_SCANF_AND_PRINTF 0
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  SPI_Config();
  Serial_Config();

  Delay_10ms(1);

  Serial_SendStr("\r\nHello World!\r\n\r\n");
}
int main( void )
{
  uint8_t sendData = 0;
  uint8_t recvData = 0;
  uint32_t errrCount = 0;

  System_Init();

  LED1_Set();
  LED2_Set();
  LED3_Set();
  LED4_Set();
  if(SPI_RW(SPIx, 0x01) == 0x01)  LED1_Reset();   Delay_100ms(2);
  if(SPI_RW(SPIx, 0x02) == 0x02)  LED2_Reset();   Delay_100ms(2);
  if(SPI_RW(SPIx, 0x03) == 0x03)  LED3_Reset();   Delay_100ms(2);
  if(SPI_RW(SPIx, 0x04) == 0x04)  LED4_Reset();   Delay_100ms(2);
  Delay_100ms(2);
  LED1_Set();
  LED2_Set();
  LED3_Set();
  LED4_Set();
  Delay_100ms(2);

  while(1) {
    if(++sendData == 0xFF)
      sendData = 0x00;
    recvData = SPI_RW(SPIx, sendData);
    printf("spi send %2x ... recv %2x ... ", sendData, recvData);
    if(sendData == recvData) {
      LED1_Toggle();
      printf("SUCCESS\r\n");
    }
    else {
      LED2_Toggle();
      printf("ERROR %i\r\n", ++errrCount);
    }
//    Delay_10ms(5);
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

  SPI_Cmd(SPIx, DISABLE);

  SPI_InitStruct.PinCS     = 12;
  SPI_InitStruct.PinSCK    = 13;
  SPI_InitStruct.PinMOSI   = 14;  // MOSI should be connected to MISO
  SPI_InitStruct.PinMISO   = 15;  // MOSI should be connected to MISO
  SPI_InitStruct.CPHA      = SPI_CONFIG_CPHA_Leading;
  SPI_InitStruct.CPOL      = SPI_CONFIG_CPOL_ActiveHigh;
  SPI_InitStruct.BitOrder  = SPI_CONFIG_ORDER_MsbFirst;
  SPI_InitStruct.Freguency = SPI_FREQUENCY_FREQUENCY_M8;
  SPI_Init(SPIx, &SPI_InitStruct);

  SPI_EvenClear(SPIx);
  SPI_Cmd(SPIx, ENABLE);

  SPI_RW(SPIx, 0x00); // Tx Buf
}
/*====================================================================================================*/
/*====================================================================================================*/
