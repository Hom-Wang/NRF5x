/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "experiment_nrf51.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
//void POWER_CLOCK_IRQHandler( void ){}
//void RADIO_IRQHandler( void ){}
/*====================================================================================================*/
/*====================================================================================================*/
void UART0_IRQHandler( void )
{
  u8 RecvData = 0;

  RS232_RecvByte(&RecvData);
  if(RecvData == 0x0D)
    RS232_SendStr((u8*)"\r\n");
  else
    RS232_SendByte(RecvData);
}
/*====================================================================================================*/
/*====================================================================================================*/
//void SPI0_TWI0_IRQHandler( void ){}
//void SPI1_TWI1_IRQHandler( void ){}
//void GPIOTE_IRQHandler( void ){}
//void ADC_IRQHandler( void ){}
//void TIMER0_IRQHandler( void ){}
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
