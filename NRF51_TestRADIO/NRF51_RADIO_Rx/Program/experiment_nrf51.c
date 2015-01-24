/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_clock.h"
#include "nrf51_radio.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
static uint32_t packet;
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  CLOCK_CmdHFCLK(ENABLE);

  GPIO_Config();
  radio_configure();

  while(1) {
    // Set payload pointer
    NRF_RADIO->PACKETPTR = (uint32_t)(&packet);
    NRF_RADIO->EVENTS_READY = 0U;
    // Enable radio and wait for ready
    NRF_RADIO->TASKS_RXEN = 1U;
    while(NRF_RADIO->EVENTS_READY == 0U);
    NRF_RADIO->EVENTS_END = 0U;
    // Start listening and wait for address received event
    NRF_RADIO->TASKS_START = 1U;
    // Wait for end of packet
    while(NRF_RADIO->EVENTS_END == 0U);

    // Write received data to LED0 and LED1 on CRC match
    if (NRF_RADIO->CRCSTATUS == 1U) {
      nrf_gpio_pin_write(LED_1, Byte32U8_1(packet));
      nrf_gpio_pin_write(LED_2, Byte32U8_2(packet));
      nrf_gpio_pin_write(LED_3, Byte32U8_3(packet));
      nrf_gpio_pin_write(LED_4, Byte32U8_4(packet));
    }
    NRF_RADIO->EVENTS_DISABLED = 0U;

    // Disable radio
    NRF_RADIO->TASKS_DISABLE = 1U;
    while(NRF_RADIO->EVENTS_DISABLED == 0U);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_1, LED_4);
}
/*====================================================================================================*/
/*====================================================================================================*/
