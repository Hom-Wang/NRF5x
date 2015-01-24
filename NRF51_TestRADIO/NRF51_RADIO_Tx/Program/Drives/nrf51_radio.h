/* #include "nrf51_radio.h" */

#ifndef __NRF51_RADIO_H
#define __NRF51_RADIO_H

#include "nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint8_t RADIO_TxPower;
  // RADIO_TXPOWER_TXPOWER_Pos4dBm  - + 4dBm.
  // RADIO_TXPOWER_TXPOWER_0dBm     -   0dBm.
  // RADIO_TXPOWER_TXPOWER_Neg4dBm  - - 4dBm.
  // RADIO_TXPOWER_TXPOWER_Neg8dBm  - - 8dBm.
  // RADIO_TXPOWER_TXPOWER_Neg12dBm - -12dBm.
  // RADIO_TXPOWER_TXPOWER_Neg16dBm - -16dBm.
  // RADIO_TXPOWER_TXPOWER_Neg20dBm - -20dBm.
  // RADIO_TXPOWER_TXPOWER_Neg30dBm - -30dBm.
  uint8_t RADIO_Frequency;
  // RF Frequency = 2400 + Frequency (MHz)
  uint8_t RADIO_Mode;
  // RADIO_MODE_MODE_Nrf_1Mbit   -   1Mbit/s Nordic propietary radio mode.
  // RADIO_MODE_MODE_Nrf_2Mbit   -   2Mbit/s Nordic propietary radio mode.
  // RADIO_MODE_MODE_Nrf_250Kbit - 250kbit/s Nordic propietary radio mode.
  // RADIO_MODE_MODE_Ble_1Mbit   -   1Mbit/s Bluetooth Low Energy.
  uint8_t *RADIO_Prefix;
  uint8_t RADIO_TxAddr;
  uint8_t RADIO_RxAddr;
  uint8_t RADIO_CRC;
  // RADIO_CRCCNF_LEN_Disabled - CRC calculation disabled.
  // RADIO_CRCCNF_LEN_One      - One byte long CRC.
  // RADIO_CRCCNF_LEN_Two      - Two bytes long CRC.
  // RADIO_CRCCNF_LEN_Three    - Three bytes long CRC.
  uint32_t *RADIO_BaseAddr;
  uint32_t *RADIO_PacketPtr;
} RADIO_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void RADIO_Init( RADIO_InitTypeDef *RADIO_InitStruct );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
