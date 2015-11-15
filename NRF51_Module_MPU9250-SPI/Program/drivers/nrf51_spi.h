/* #include "nrf51_spi.h" */

#ifndef __NRF51_SPI_H
#define __NRF51_SPI_H

#include "nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint8_t  PinCS;
  uint8_t  PinSCK;
  uint8_t  PinMOSI;
  uint8_t  PinMISO;
  uint32_t Freguency;
  // SPI_FREQUENCY_FREQUENCY_K125 - 125kbps.
  // SPI_FREQUENCY_FREQUENCY_K250 - 250kbps.
  // SPI_FREQUENCY_FREQUENCY_K500 - 500kbps.
  // SPI_FREQUENCY_FREQUENCY_M1   - 1Mbps.
  // SPI_FREQUENCY_FREQUENCY_M2   - 2Mbps.
  // SPI_FREQUENCY_FREQUENCY_M4   - 4Mbps.
  // SPI_FREQUENCY_FREQUENCY_M8   - 8Mbps.
  uint16_t BitOrder;
  // SPI_CONFIG_ORDER_MsbFirst - Most significant bit transmitted out first.
  // SPI_CONFIG_ORDER_LsbFirst - Least significant bit transmitted out first.
  uint16_t CPOL;
  // SPI_CONFIG_CPOL_ActiveHigh - Active high, CPOL = 0
  // SPI_CONFIG_CPOL_ActiveLow  - Active low,  CPOL = 1
  uint16_t CPHA;
  // SPI_CONFIG_CPHA_Leading  - Sample on leading edge of the clock. Shift serial data on trailing edge, CPHA = 0
  // SPI_CONFIG_CPHA_Trailing - Sample on trailing edge of the clock. Shift serial data on leading edge, CPHA = 1
} SPI_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void    SPI_Init( NRF_SPI_Type *SPIx, SPI_InitTypeDef *SPI_InitStruct );
void    SPI_Cmd( NRF_SPI_Type *SPIx, uint8_t state );
void    SPI_CmdIRQ( NRF_SPI_Type *SPIx, uint8_t state );
uint8_t SPI_EvenCheck( NRF_SPI_Type *SPIx );
void    SPI_EvenClear( NRF_SPI_Type *SPIx );
uint8_t SPI_RW( NRF_SPI_Type *SPIx, uint8_t writeByte );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
