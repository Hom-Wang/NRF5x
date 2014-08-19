/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_timer.h"
#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
//void POWER_CLOCK_IRQHandler( void ){}
//void RADIO_IRQHandler( void ){}
//void UART0_IRQHandler( void ){}
//void SPI0_TWI0_IRQHandler( void ){}
//void SPI1_TWI1_IRQHandler( void ){}
//void GPIOTE_IRQHandler( void ){}
//void ADC_IRQHandler( void ){}
/*====================================================================================================*/
/*====================================================================================================*/
void TIMER0_IRQHandler( void )
{
  if(TIMER_EvenCheck(USE_TIMER, USE_TIMER_CH) == SUCCESS) {
    nrf_gpio_pin_toggle(LED_0);
    TIMER_EvenClear(USE_TIMER, USE_TIMER_CH);
    TIMER_TimerClear(USE_TIMER);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
//void TIMER1_IRQHandler( void ){}
//void TIMER2_IRQHandler( void ){}
//void RTC0_IRQHandler( void ){}
//void TEMP_IRQHandler( void ){}
//void RNG_IRQHandler( void ){}
//void ECB_IRQHandler( void ){}
//void CCM_AAR_IRQHandler( void ){}
//void WDT_IRQHandler( void ){}
//void RTC1_IRQHandler( void ){}
//void QDEC_IRQHandler( void ){}
//void LPCOMP_COMP_IRQHandler( void ){}
//void SWI0_IRQHandler( void ){}
//void SWI1_IRQHandler( void ){}
//void SWI2_IRQHandler( void ){}
//void SWI3_IRQHandler( void ){}
//void SWI4_IRQHandler( void ){}
//void SWI5_IRQHandler( void ){}
/*====================================================================================================*/
/*====================================================================================================*/
