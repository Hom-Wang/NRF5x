/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_radio.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : RADIO_Init
**功能 : Radio Init
**輸入 : *RADIO_InitStruct
**輸出 : None
**使用 : RADIO_Init(&RADIO_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void RADIO_Init( RADIO_InitTypeDef *RADIO_InitStruct )
{
  uint32_t PrefixAddr[2] = { Byte32(uint32_t, RADIO_InitStruct->RADIO_BaseAddr[7],    // AP7
                                              RADIO_InitStruct->RADIO_BaseAddr[6],    // AP6
                                              RADIO_InitStruct->RADIO_BaseAddr[5],    // AP5
                                              RADIO_InitStruct->RADIO_BaseAddr[4]),   // AP4
                             Byte32(uint32_t, RADIO_InitStruct->RADIO_BaseAddr[3],    // AP3
                                              RADIO_InitStruct->RADIO_BaseAddr[2],    // AP2
                                              RADIO_InitStruct->RADIO_BaseAddr[1],    // AP1
                                              RADIO_InitStruct->RADIO_BaseAddr[0])};  // AP0

  NRF_RADIO->TXPOWER   = (RADIO_InitStruct->RADIO_TxPower   << RADIO_TXPOWER_TXPOWER_Pos);
  NRF_RADIO->FREQUENCY = (RADIO_InitStruct->RADIO_Frequency << RADIO_TXPOWER_TXPOWER_Pos);
  NRF_RADIO->MODE      = (RADIO_InitStruct->RADIO_Mode      << RADIO_MODE_MODE_Pos);

  NRF_RADIO->PREFIX0 = PrefixAddr[1];
  NRF_RADIO->PREFIX1 = PrefixAddr[0];

  NRF_RADIO->BASE0 = RADIO_InitStruct->RADIO_BaseAddr[0];
  NRF_RADIO->BASE1 = RADIO_InitStruct->RADIO_BaseAddr[1];

  NRF_RADIO->TXADDRESS   = RADIO_InitStruct->RADIO_TxAddr;
  NRF_RADIO->RXADDRESSES = RADIO_InitStruct->RADIO_RxAddr;

#define PACKET0_S1_SIZE             (0UL)   // S1 size in bits
#define PACKET0_S0_SIZE             (0UL)   // S0 size in bits
#define PACKET0_PAYLOAD_SIZE        (0UL)   // payload size in bits
#define PACKET1_BASE_ADDRESS_LENGTH (4UL)   // base address length in bytes
#define PACKET1_STATIC_LENGTH       (128UL) // static length in bytes
#define PACKET1_PAYLOAD_SIZE        (128UL) // payload size in bytes

  NRF_RADIO->PCNF0 = (PACKET0_S1_SIZE              << RADIO_PCNF0_S1LEN_Pos) | 
                     (PACKET0_S0_SIZE              << RADIO_PCNF0_S0LEN_Pos) | 
                     (PACKET0_PAYLOAD_SIZE         << RADIO_PCNF0_LFLEN_Pos);
  NRF_RADIO->PCNF1 = (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos) | 
                     (RADIO_PCNF1_ENDIAN_Big       << RADIO_PCNF1_ENDIAN_Pos) | 
                     (PACKET1_BASE_ADDRESS_LENGTH  << RADIO_PCNF1_BALEN_Pos) | 
                     (PACKET1_STATIC_LENGTH        << RADIO_PCNF1_STATLEN_Pos) | 
                     (PACKET1_PAYLOAD_SIZE         << RADIO_PCNF1_MAXLEN_Pos);

  NRF_RADIO->CRCCNF = (RADIO_InitStruct->RADIO_CRC << RADIO_CRCCNF_LEN_Pos);
  switch((NRF_RADIO->CRCCNF & RADIO_CRCCNF_LEN_Msk)) {
    case RADIO_CRCCNF_LEN_One:
      NRF_RADIO->CRCINIT = 0xFFUL;      // Init Value
      NRF_RADIO->CRCPOLY = 0x107UL;     // CRC poly: x^8+x^2^x^1+1
      break;
    case RADIO_CRCCNF_LEN_Two:
      NRF_RADIO->CRCINIT = 0xFFFFUL;    // Init Value
      NRF_RADIO->CRCPOLY = 0x11021UL;   // CRC poly: x^16+x^12^x^5+1
      break;
    case RADIO_CRCCNF_LEN_Three:
//      NRF_RADIO->CRCINIT = 0xFFUL;    // 
//      NRF_RADIO->CRCPOLY = 0x107UL;   // 
      break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/

