/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_adc.h"
#include "modules\module_serial.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
extern __IO uint16_t readADC;
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  ADC_Config();
  Serial_Config();

  Delay_1ms(1);

  Serial_SendStr("\r\nHello World!\r\n\r\n");
}
int main( void )
{
  System_Init();

  while(1) {
    LED1_Toggle();
    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();

    printf("ADC Read = %d\r\n", readADC);
    Delay_100ms(1);
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
void ADC_Config( void )
{
  ADC_InitTypeDef ADC_InitStruct;

  ADC_InitStruct.AnalogInput     = NRF_ADC_CONFIG_INPUT_2;                  // P0.01
  ADC_InitStruct.Resolution      = NRF_ADC_CONFIG_RES_10BIT;                // 0 ~ 1023
  ADC_InitStruct.ConfigReference = NRF_ADC_CONFIG_REF_VBG;                  // Ref 1.2V
  ADC_InitStruct.InputSelection  = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;  // AIN max 3.6V
  ADC_Init(ADCx, &ADC_InitStruct);

  ADC_Cmd(ADCx, ENABLE);

  ADC_IntCmd(ADCx, ENABLE);
  NVIC_SetPriority(ADC_IRQn, 1);
  NVIC_EnableIRQ(ADC_IRQn);

  ADC_StartConv(ADCx);
}
/*====================================================================================================*/
/*====================================================================================================*/
