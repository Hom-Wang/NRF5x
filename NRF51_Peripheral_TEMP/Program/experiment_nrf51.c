/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_temp.h"
#include "modules\module_serial.h"

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
  TEMP_Config();
  Serial_Config();

  Delay_1ms(1);

  Serial_SendStr("\r\nHello World!\r\n\r\n");
}
int main( void )
{
  float temp = 0.0f;

  System_Init();

  while(1) {
    LED1_Toggle();
    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();
    Delay_100ms(5);

    NRF_TEMP->TASKS_START = 1;
    while(NRF_TEMP->EVENTS_DATARDY == 0);
    NRF_TEMP->EVENTS_DATARDY = 0;
    temp = (TEMP_GetTemp() / 4.0f);
    printf("chip temperature : %.2f degC\r\n", temp);
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
