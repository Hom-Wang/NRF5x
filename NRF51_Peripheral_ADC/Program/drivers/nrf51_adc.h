/* #include "nrf51_adc.h" */

#ifndef __NRF51_ADC_H
#define __NRF51_ADC_H

#include "nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint16_t Resolution;
  // NRF_ADC_CONFIG_RES_8BIT  -  8 bit resolution
  // NRF_ADC_CONFIG_RES_9BIT  -  9 bit resolution
  // NRF_ADC_CONFIG_RES_10BIT - 10 bit resolution
  uint16_t AnalogInput;
  // NRF_ADC_CONFIG_INPUT_DISABLED - No input selected
  // NRF_ADC_CONFIG_INPUT_0        - Input 0, P0.26
  // NRF_ADC_CONFIG_INPUT_1        - Input 1, P0.27
  // NRF_ADC_CONFIG_INPUT_2        - Input 2, P0.01
  // NRF_ADC_CONFIG_INPUT_3        - Input 3, P0.02
  // NRF_ADC_CONFIG_INPUT_4        - Input 4, P0.03
  // NRF_ADC_CONFIG_INPUT_5        - Input 5, P0.04
  // NRF_ADC_CONFIG_INPUT_6        - Input 6, P0.05
  // NRF_ADC_CONFIG_INPUT_7        - Input 7, P0.06
  uint16_t ConfigReference;
  // NRF_ADC_CONFIG_REF_VBG              - 1.2 V reference
  // NRF_ADC_CONFIG_REF_SUPPLY_ONE_HALF  - 1/2 of power supply
  // NRF_ADC_CONFIG_REF_SUPPLY_ONE_THIRD - 1/3 of power supply
  // NRF_ADC_CONFIG_REF_EXT_REF0         - External reference 0
  // NRF_ADC_CONFIG_REF_EXT_REF1         - External reference 1
  uint16_t InputSelection;
  // NRF_ADC_CONFIG_SCALING_INPUT_FULL_SCALE  - Full scale input, AIN max 1.2 V
  // NRF_ADC_CONFIG_SCALING_INPUT_TWO_THIRDS  - 2/3 scale input,  AIN max 2.4 V
  // NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD   - 1/3 scale input,  AIN max 3.6 V
  // NRF_ADC_CONFIG_SCALING_SUPPLY_TWO_THIRDS - 2/3 of supply,
  // NRF_ADC_CONFIG_SCALING_SUPPLY_ONE_THIRD  - 1/3 of supply,
} ADC_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void     ADC_Init( NRF_ADC_Type *ADCx, ADC_InitTypeDef *ADC_InitStruct );
void     ADC_Cmd( NRF_ADC_Type *ADCx, uint8_t state );
void     ADC_IntCmd( NRF_ADC_Type *ADCx, uint8_t state );
void     ADC_StartConv( NRF_ADC_Type *ADCx );
void     ADC_StopConv( NRF_ADC_Type *ADCx );
uint8_t  ADC_Busy( NRF_ADC_Type *ADCx );
uint8_t  ADC_EvenCheck( NRF_ADC_Type *ADCx );
void     ADC_EvenClear( NRF_ADC_Type *ADCx );
uint16_t ADC_GetResult( NRF_ADC_Type *ADCx );
uint16_t ADC_ReadData( NRF_ADC_Type *ADCx );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
