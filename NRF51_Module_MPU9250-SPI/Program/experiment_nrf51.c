/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_spi.h"
#include "modules\module_serial.h"
#include "modules\module_mpu9250.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  Serial_Config();
  MPU9250_Config();

  Delay_100ms(1);
  printf("\r\nHello World!\r\n\r\n");

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_41Hz;
  printf("MPU9250 Init ...");
  if(MPU9250_Init(&MPU_InitStruct) != SUCCESS) {
    printf("ERROR\r\n");
    while(1) {
      LED2_Toggle();
      Delay_100ms(1);
    }
  }
  printf("SUCCESS\r\n");
  LED2_Set();
  Delay_100ms(1);
}
int main( void )
{
  int16_t dataIMU[10] = {0};

  System_Init();

  while(1) {
    LED4_Toggle();
    Delay_100ms(5);

    MPU9250_getData(dataIMU);
    printf("Acc.X = %d\tAcc.Y = %d\tAcc.Z = %d\tGyr.X = %d\tGyr.Y = %d\tGyr.Z = %d\tMag.X = %d\tMag.Y = %d\tMag.Z = %d\tTemp = %d\r\n", dataIMU[1], dataIMU[2], dataIMU[3], dataIMU[4], dataIMU[5], dataIMU[6], dataIMU[7], dataIMU[8], dataIMU[9], dataIMU[0]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void GPIO_Config( void )
{
  nrf_gpio_range_cfg_output(LED_1, LED_4);
  nrf_gpio_range_cfg_input(KEY_1, KEY_4, NRF_GPIO_PIN_PULLUP);

  LED1_Set();
  LED2_Set();
  LED3_Set();
  LED4_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
