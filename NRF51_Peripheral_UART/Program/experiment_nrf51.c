/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "modules\module_serial.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define USE_SCANF_AND_PRINTF 0
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  Serial_Config();

  Delay_1ms(1);

  Serial_SendStr("\r\nHello World!\r\n\r\n");
}
int main( void )
{
  System_Init();

#if USE_SCANF_AND_PRINTF
  int recvNum = 0;
  while(1) {
    LED1_Toggle();
    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();

    printf("\r\nNumber Input : ");
    scanf("%d", &recvNum);
    printf("\r\nNumber Output %d\r\n", recvNum);
  }

#else
  static uint8_t i = 0;
  static uint8_t recvData = 0;
  static int8_t  state = ERROR;
  while(1) {
    LED1_Toggle();
    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();

    state = Serial_RecvDataWTO(&recvData, 1, 200);
    if(state == ERROR) {
      Serial_SendStr("Timeout ... ");
      Serial_SendNum(Type_D, 3, i);
      Serial_SendStr("\r\n");
      i = (i == 255) ? 0 : i + 1;
    }
    else if(recvData == 0x0D)  // if press enter
      Serial_SendStr("\r\n");
    else
      Serial_SendData(&recvData, 1);
  }

#endif
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
