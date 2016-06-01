/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"

#include "nrf51dk.h"
#include "nrf51dk_ble.h"

#include "app_timer.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_TIMER_PRESCALER       0   /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE   4   /**< Size of timer operation queues. */

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
    LED1_Reset();
    next_delay = 50;    // 50 ms
  }
  state = !state;

  app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay, APP_TIMER_MODE_SINGLE_SHOT), NULL);
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

  err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
void NRF51_Init( void )
{
  NRF51_CKOCK_Config();
  NRF51_GPIO_Config();

  timers_init();
  timers_start();

  NRF51_BLE_StackInit();
}
/*====================================================================================================*/
/*====================================================================================================*/
void NRF51_Loop( void )
{
  while(1) {
//    LED1_Toggle();
//    LED2_Toggle();
    LED3_Toggle();
    LED4_Toggle();
    delay_ms(200);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
