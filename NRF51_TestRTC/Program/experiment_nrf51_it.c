/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_rtc.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
//void POWER_CLOCK_IRQHandler( void )
//void RADIO_IRQHandler( void )
//void UART0_IRQHandler( void )
//void SPI0_TWI0_IRQHandler( void )
//void SPI1_TWI1_IRQHandler( void )
//void GPIOTE_IRQHandler( void )
//void ADC_IRQHandler( void )
//void TIMER0_IRQHandler( void )
//void TIMER1_IRQHandler( void )
//void TIMER2_IRQHandler( void )
/*====================================================================================================*/
/*====================================================================================================*/
void RTC0_IRQHandler( void )
{
  if(RTC_TickEvenCheck() == SUCCESS) {
    nrf_gpio_pin_toggle(LED_0);
    RTC_TickEvenClear();
  }
  if(RTC_CompEvenCheck(RTC_CH0) == SUCCESS) {
    nrf_gpio_pin_toggle(LED_1);
    RTC_CompEvenClear(RTC_CH0);
    RTC_CntClear();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
//void TEMP_IRQHandler( void )
//void RNG_IRQHandler( void )
//void ECB_IRQHandler( void )
//void CCM_AAR_IRQHandler( void )
//void WDT_IRQHandler( void )
//void RTC1_IRQHandler( void )
//void QDEC_IRQHandler( void )
//void LPCOMP_COMP_IRQHandler( void )
//void SWI0_IRQHandler( void )
//void SWI1_IRQHandler( void )
//void SWI2_IRQHandler( void )
//void SWI3_IRQHandler( void )
//void SWI4_IRQHandler( void )
//void SWI5_IRQHandler( void )
/*====================================================================================================*/
/*====================================================================================================*/
