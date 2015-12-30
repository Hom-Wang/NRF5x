/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"

#include "experiment_nrf51.h"

#include "cmsis_os.h"
/*====================================================================================================*/
/*====================================================================================================*/
static void osTimer_Callback( void const *argument )
{
  (void) argument;  

  LED1_Toggle();
}
static void thread_ToggleLEDG( void const *argument )
{
  (void) argument;

  while(1) {
    LED2_Toggle();
    osDelay(400);
  }
}
static void thread_ToggleLEDB( void const *argument )
{
  (void) argument;

  while(1) {
    LED3_Toggle();
    osDelay(800);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
}

static void FreeRTOS_Init( void )
{
  /* Create Timer */
  osTimerDef(timer, osTimer_Callback);
  osTimerId osTimer = osTimerCreate(osTimer(timer), osTimerPeriodic, NULL);

  /* Start Timer */
  osTimerStart(osTimer, 200);

  /* Create LED Thread */
  osThreadDef(threadLEDG, thread_ToggleLEDG, osPriorityNormal, 1, configMINIMAL_STACK_SIZE);
  osThreadCreate(osThread(threadLEDG), NULL);
  osThreadDef(threadLEDB, thread_ToggleLEDB, osPriorityNormal, 1, configMINIMAL_STACK_SIZE);
  osThreadCreate(osThread(threadLEDB), NULL);

  /* Start scheduler */
  osKernelStart();
}

int main( void )
{
  System_Init();
  FreeRTOS_Init();

  while(1) {

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
