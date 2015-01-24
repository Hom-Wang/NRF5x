/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_adc.h"
#include "experiment_nrf51.h"
#include "module_rs232.h"
/*====================================================================================================*/
/*====================================================================================================*/
volatile uint16_t ReadADC = 0;
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  GPIO_Config();
  ADC_Config();
  RS232_Config();

  Delay_1ms(1);

  RS232_SendStr((uint8_t*)"\r\nHello World!\r\n\r\n");

  while(1) {
    nrf_gpio_pin_toggle(LED_2);
    nrf_gpio_pin_toggle(LED_3);
    nrf_gpio_pin_toggle(LED_4);
    Delay_100ms(1);

    RS232_SendStr((uint8_t*)"ReadADC = ");
    RS232_SendNum(Type_D, 4, ReadADC);
    RS232_SendStr((uint8_t*)"\r\n");
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
void ADC_Config( void )
{
  ADC_InitTypeDef ADC_InitStruct;

  ADC_InitStruct.ADC_AnalogInput        = ADC_CONFIG_PSEL_AnalogInput2; // Use ADC0(P0.01)
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
