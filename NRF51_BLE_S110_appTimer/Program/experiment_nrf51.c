/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "modules\module_serial.h"

#include "experiment_nrf51.h"

#include "nordic_common.h"
#include "app_timer.h"
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

  Delay_100ms(1);
  Serial_SendStr("\r\nHello World!\r\n\r\n");
}
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_TIMER_PRESCALER     0
#define APP_TIMER_OP_QUEUE_SIZE 4

APP_TIMER_DEF(m_leds_timer_id);

static void leds_timer_handler( void * p_context )
{
  uint32_t next_delay = 0;
  static uint8_t state = 0;

  UNUSED_PARAMETER(p_context);

  if(!state) {
    LED1_Set();
    next_delay = 1950;  // 1950 ms
  }
  else {
    LED1_Toggle();
    next_delay = 50;    // 50 ms
  }
  state = !state;

  app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay, APP_TIMER_PRESCALER), NULL);
}

void timers_init( void )
{
  uint32_t err_code;

  APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);

  // LED timer
  err_code = app_timer_create(&m_leds_timer_id, APP_TIMER_MODE_SINGLE_SHOT, leds_timer_handler);
  APP_ERROR_CHECK(err_code);
}

void timers_start( void )
{
  uint32_t err_code;

  err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), NULL);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
void ble_init( void )
{
  System_Init();
  timers_init();
  
  timers_start();
}
/*====================================================================================================*/
/*====================================================================================================*/
int main( void )
{
  ble_init();

  while(1) {
//    LED1_Toggle();
//    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();
    Delay_100ms(1);
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
