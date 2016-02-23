/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"

#include "nrf5xdk_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void timer_event_handler( nrf_timer_event_t event_type, void* p_context )
{
  LED1_Toggle();
}

const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);
void TIMER_Config( nrf_timer_event_handler_t t_timer_event_handler )
{
  uint32_t time_ms = 100;
  uint32_t time_ticks;

  nrf_drv_timer_init(&TIMER_LED, NULL, t_timer_event_handler);

  time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms);
  nrf_drv_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
  nrf_drv_timer_enable(&TIMER_LED);
}
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  Clock_Config();
  GPIO_Config();
  TIMER_Config(timer_event_handler);
}

int main( void )
{
  System_Init();

  while(1) {
    LED4_Toggle();
    delay_ms(100);
//    __WFI();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
