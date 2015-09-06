/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "modules\module_rs232.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define USE_SCANF_AND_PRINTF 0

int main( void )
{
  GPIO_Config();
  RS232_Config();

  Delay_1ms(1);

  RS232_SendStr("\r\nHello World!\r\n\r\n");

#if USE_SCANF_AND_PRINTF
  int recvNum = 0;
  while(1) {
    LED_1_Toggle();
    LED_2_Toggle();
    LED_3_Toggle();
    LED_4_Toggle();

    printf("\r\nPlease scan a Number : ");
    scanf("%d", &recvNum);
    printf("\r\nNumber is %d\r\n", recvNum);
  }

#else
  static uint8_t i = 0;
  static uint8_t RecvData = 0;
  static int8_t  State = ERROR;
  while(1) {
    LED_1_Toggle();
    LED_2_Toggle();
    LED_3_Toggle();
    LED_4_Toggle();

    State = RS232_RecvDataWTO(&RecvData, 1, 200);
    if(State == ERROR) {
      RS232_SendStr("Timeout ... ");
      RS232_SendNum(Type_D, 3, i);
      RS232_SendStr("\r\n");
      i = (i == 255) ? 0 : i + 1;
    }
    else if(RecvData == 0x0D)  // if press enter
      RS232_SendStr("\r\n");
    else
      RS232_SendData(&RecvData, 1);
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
