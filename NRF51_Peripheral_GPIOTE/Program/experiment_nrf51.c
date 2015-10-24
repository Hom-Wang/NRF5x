/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_gpiote.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  GPIOTE_Config();

  Delay_100ms(1);
}
int main( void )
{
  System_Init();

  while(1) {
    LED3_Toggle();
    LED4_Toggle();
    Delay_10ms(8);
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
void GPIOTE_Config( void )
{
  GPIOTE_InitTypeDef GPIOTE_InitStruct;

  GPIOTE_InitStruct.GPIOTE_Pin = KEY_1;                               // 
  GPIOTE_InitStruct.GPIOTE_Mode = GPIOTE_CONFIG_MODE_Event;           // output
  GPIOTE_InitStruct.GPIOTE_Polarity = NRF_GPIOTE_POLARITY_HITOLO;     // high to low
  GPIOTE_Init(KEY_EL1, &GPIOTE_InitStruct);                           // CH0

  GPIOTE_InitStruct.GPIOTE_Pin = KEY_2;                               // 
  GPIOTE_InitStruct.GPIOTE_Mode = GPIOTE_CONFIG_MODE_Event;           // output
  GPIOTE_InitStruct.GPIOTE_Polarity = NRF_GPIOTE_POLARITY_HITOLO;     // high to low
  GPIOTE_Init(KEY_EL2, &GPIOTE_InitStruct);                           // CH1

//  NVIC_ClearPendingIRQ(GPIOTE_IRQn);
//  NVIC_SetPriority(GPIOTE_IRQn, 1);
  NVIC_EnableIRQ(GPIOTE_IRQn);
}
/*====================================================================================================*/
/*====================================================================================================*/
