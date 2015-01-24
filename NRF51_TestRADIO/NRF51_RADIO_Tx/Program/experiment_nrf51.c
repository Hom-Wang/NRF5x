/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_clock.h"
#include "nrf51_radio.h"
#include "experiment_nrf51.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
uint8_t RecvData = 0;
static uint32_t packet;
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  uint8_t tmp[4] = {0};

  CLOCK_CmdHFCLK(ENABLE);

  GPIO_Config();
  RS232_Config();
  RADIO_Config();

  Delay_1ms(1);

  RS232_SendStr((uint8_t*)"\r\nHello World!\r\n\r\n");

  while(1) {
    nrf_gpio_pin_toggle(LED_R);
    nrf_gpio_pin_toggle(LED_G);
    nrf_gpio_pin_toggle(LED_B);
    Delay_10ms(4);

    tmp[0] = (RecvData == 1) ? 0 : 1;
    tmp[1] = (RecvData == 2) ? 0 : 1;
    tmp[2] = (RecvData == 3) ? 0 : 1;
    tmp[3] = (RecvData == 4) ? 0 : 1;
    RecvData = 0;

    packet = Byte32(uint32_t, tmp[3], tmp[2], tmp[1], tmp[0]);

    NRF_RADIO->TASKS_TXEN = 1;

    NRF_RADIO->EVENTS_READY = 0U;
    while(NRF_RADIO->EVENTS_READY == 0U);

    NRF_RADIO->TASKS_START = 1U;

    NRF_RADIO->EVENTS_END = 0U;
    while(NRF_RADIO->EVENTS_END == 0U);

    NRF_RADIO->EVENTS_DISABLED = 0U;
    NRF_RADIO->TASKS_DISABLE = 1U;
    while(NRF_RADIO->EVENTS_DISABLED == 0U);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_R, LED_B);
}
/*====================================================================================================*/
/*====================================================================================================*/
void RADIO_Config( void )
{
  RADIO_InitTypeDef RADIO_InitStruct;

  uint8_t  PrefixAddr[8] = {0xE7, 0xC2, 0xC3, 0xC4, 0xC8, 0xC7, 0xC6, 0xC5};
  uint32_t BaseAddr[2]   = {0xE7E7E7E7, 0x00C2C2C2};

  RADIO_InitStruct.RADIO_TxPower   = RADIO_TXPOWER_TXPOWER_0dBm;
  RADIO_InitStruct.RADIO_Frequency = 7;   // RF Freq = 2407 MHz
  RADIO_InitStruct.RADIO_Mode      = RADIO_MODE_MODE_Nrf_2Mbit;
  RADIO_InitStruct.RADIO_Prefix    = PrefixAddr;
  RADIO_InitStruct.RADIO_BaseAddr  = BaseAddr;
  RADIO_InitStruct.RADIO_TxAddr    = 0x00;
  RADIO_InitStruct.RADIO_RxAddr    = 0x01;
  RADIO_InitStruct.RADIO_CRC       = RADIO_CRCCNF_LEN_Two;
  RADIO_Init(&RADIO_InitStruct);

  NRF_RADIO->PACKETPTR = (uint32_t)(&packet);

  Delay_1ms(5);
}
/*====================================================================================================*/
/*====================================================================================================*/
