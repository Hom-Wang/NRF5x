/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf5x_system.h"
#include "nrf5x_saadc.h"

#include "app_util_platform.h"
#include "nrf5xdk_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void saadc_event_handler( nrf_drv_saadc_evt_t const * p_event );
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SAADC_Config
**功能 : SAADC Config
**輸入 : None
**輸出 : None
**使用 : SAADC_Config();
**====================================================================================================*/
/*====================================================================================================*/
void SAADC_Config( void )
{
  nrf_drv_saadc_config_t saadc_init_struct;
  nrf_saadc_channel_config_t saadc_channel_init_struct;

  saadc_init_struct.resolution         = SAADC_CONFIG_RESOLUTION;
  saadc_init_struct.oversample         = SAADC_CONFIG_OVERSAMPLE;
  saadc_init_struct.interrupt_priority = SAADC_CONFIG_IRQ_PRIORITY;
  nrf_drv_saadc_init(&saadc_init_struct, saadc_event_handler);

  saadc_channel_init_struct.resistor_p = NRF_SAADC_RESISTOR_DISABLED;
  saadc_channel_init_struct.resistor_n = NRF_SAADC_RESISTOR_DISABLED;
  saadc_channel_init_struct.gain       = NRF_SAADC_GAIN1_6;
  saadc_channel_init_struct.reference  = NRF_SAADC_REFERENCE_INTERNAL;
  saadc_channel_init_struct.acq_time   = NRF_SAADC_ACQTIME_40US;
  saadc_channel_init_struct.mode       = NRF_SAADC_MODE_SINGLE_ENDED;
  saadc_channel_init_struct.pin_p      = (nrf_saadc_input_t)(ADCx_CHANNEL + NRF_SAADC_INPUT_AIN0);
  saadc_channel_init_struct.pin_n      = NRF_SAADC_INPUT_DISABLED;
  nrf_drv_saadc_channel_init(ADCx_CHANNEL, &saadc_channel_init_struct);

  nrf_drv_saadc_sample();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SAADC_Read
**功能 : SAADC Read
**輸入 : channel
**輸出 : convADC
**使用 : convADC = SAADC_Read(0); // read AIN0
**====================================================================================================*/
/*====================================================================================================*/
int16_t SAADC_Read( uint8_t channel )
{
  int16_t convADC = 0;
  nrf_drv_saadc_sample_convert(channel, &convADC);
  return convADC;
}
/*====================================================================================================*/
/*====================================================================================================*/
void saadc_event_handler( nrf_drv_saadc_evt_t const * p_event )
{
  if(p_event->type == NRF_DRV_SAADC_EVT_DONE) {
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
