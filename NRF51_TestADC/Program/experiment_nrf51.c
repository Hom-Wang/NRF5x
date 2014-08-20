/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_adc.h"
#include "experiment_nrf51.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
vu16 ReadADC = 0;
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  u8 i = 0;

  GPIO_Config();
  ADC_Config();
  RS232_Config();

  Delay_1ms(5);

  while(1) {

    nrf_gpio_pin_toggle(LED_1);
    for(i = 0; i<7; i++) {
      LED_PORT = ~(0x01<<i);
      Delay_10ms(DELAY_TIME);
    }
    nrf_gpio_pin_toggle(LED_1);
    for(i = 7; i>0; i--) {
      LED_PORT = ~(0x01<<i);
      Delay_10ms(DELAY_TIME);
    }

    RS232_SendStr((u8*)"ReadADC = ");
    RS232_SendNum(Type_D, 4, ReadADC);
    RS232_SendStr((u8*)"\r\n");
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(0, 7);              // Pin 00-07 - output
  nrf_gpio_range_cfg_output(LED_0, LED_1);      // Pin 18-19 - output
  nrf_gpio_cfg_input(KEY, NRF_GPIO_PIN_PULLUP); // Pin 20    - input
}
/*====================================================================================================*/
/*====================================================================================================*/
void ADC_Config( void )
{
  ADC_InitTypeDef ADC_InitStruct;

  ADC_InitStruct.ADC_AnalogInput        = ADC_CONFIG_PSEL_AnalogInput0;
  ADC_InitStruct.ADC_ExternalReference  = ADC_CONFIG_EXTREFSEL_None;
  ADC_InitStruct.ADC_Resolution         = ADC_CONFIG_RES_10bit;
  ADC_InitStruct.ADC_ReferenceSelection = ADC_CONFIG_REFSEL_VBG;
  ADC_InitStruct.ADC_InputSelection     = ADC_CONFIG_INPSEL_AnalogInputOneThirdPrescaling;
  ADC_Init(&ADC_InitStruct);

  ADC_Cmd(ENABLE);

  ADC_IntCmd(ENABLE);
  NVIC_SetPriority(ADC_IRQn, 1);
  NVIC_EnableIRQ(ADC_IRQn);

  ADC_StartConv();
}
/*====================================================================================================*/
/*====================================================================================================*/
