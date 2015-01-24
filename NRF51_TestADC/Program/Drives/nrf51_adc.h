/* #include "nrf51_adc.h" */

#ifndef __NRF51_ADC_H
#define __NRF51_ADC_H

#include "nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint16_t ADC_Resolution;
  // ADC_CONFIG_RES_8bit  -  8bit ADC resolution.
  // ADC_CONFIG_RES_9bit  -  9bit ADC resolution.
  // ADC_CONFIG_RES_10bit - 10bit ADC resolution.
  uint16_t ADC_ExternalReference;
  // ADC_CONFIG_EXTREFSEL_None             - Analog external reference inputs disabled.
  // ADC_CONFIG_EXTREFSEL_AnalogReference0 - Use analog reference 0 as reference. P0.00
  // ADC_CONFIG_EXTREFSEL_AnalogReference1 - Use analog reference 1 as reference. P0.06
  uint16_t ADC_AnalogInput;
  // ADC_CONFIG_PSEL_Disabled     - Analog input pins disabled.
  // ADC_CONFIG_PSEL_AnalogInput0 - Use analog input 0 as analog input. P0.26
  // ADC_CONFIG_PSEL_AnalogInput1 - Use analog input 1 as analog input. P0.27
  // ADC_CONFIG_PSEL_AnalogInput2 - Use analog input 2 as analog input. P0.01
  // ADC_CONFIG_PSEL_AnalogInput3 - Use analog input 3 as analog input. P0.02
  // ADC_CONFIG_PSEL_AnalogInput4 - Use analog input 4 as analog input. P0.03
  // ADC_CONFIG_PSEL_AnalogInput5 - Use analog input 5 as analog input. P0.04
  // ADC_CONFIG_PSEL_AnalogInput6 - Use analog input 6 as analog input. P0.05
  // ADC_CONFIG_PSEL_AnalogInput7 - Use analog input 7 as analog input. P0.06
  uint16_t ADC_ReferenceSelection;
  // ADC_CONFIG_REFSEL_VBG                      - Use internal 1.2V bandgap voltage as reference for conversion.
  // ADC_CONFIG_REFSEL_External                 - Use external source configured by EXTREFSEL as reference for conversion.
  // ADC_CONFIG_REFSEL_SupplyOneHalfPrescaling  - Use supply voltage with 1/2 prescaling as reference for conversion. Only usable when supply voltage is between 1.7V and 2.6V.
  // ADC_CONFIG_REFSEL_SupplyOneThirdPrescaling - Use supply voltage with 1/3 prescaling as reference for conversion. Only usable when supply voltage is between 2.5V and 3.6V.
  uint16_t ADC_InputSelection;
  // ADC_CONFIG_INPSEL_AnalogInputNoPrescaling        - Analog input specified by PSEL with no prescaling used as input for the conversion.
  // ADC_CONFIG_INPSEL_AnalogInputTwoThirdsPrescaling - Analog input specified by PSEL with 2/3 prescaling used as input for the conversion.
  // ADC_CONFIG_INPSEL_AnalogInputOneThirdPrescaling  - Analog input specified by PSEL with 1/3 prescaling used as input for the conversion.
  // ADC_CONFIG_INPSEL_SupplyTwoThirdsPrescaling      - Supply voltage with 2/3 prescaling used as input for the conversion.
  // ADC_CONFIG_INPSEL_SupplyOneThirdPrescaling       - Supply voltage with 1/3 prescaling used as input for the conversion.
} ADC_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void     ADC_Init( ADC_InitTypeDef *ADC_InitStruct );
void     ADC_Cmd( FunctionalState NewState );
void     ADC_IntCmd( FunctionalState NewState );
void     ADC_StartConv( void );
void     ADC_StopConv( void );
uint8_t  ADC_Busy( void );
uint8_t  ADC_EvenCheck( void );
void     ADC_EvenClear( void );
uint16_t ADC_GetResult( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
