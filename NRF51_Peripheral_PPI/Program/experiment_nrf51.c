/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_clock.h"
#include "drivers\nrf51_ppi.h"
#include "drivers\nrf51_timer.h"

#include "experiment_nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
//uint32_t ppi_task = 0;
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  CLOCK_SourceXTAL(NRF_CLOCK_XTALFREQ_16MHz);
  CLOCK_SourceLFCLK(NRF_CLOCK_LF_SRC_RC);
  CLOCK_CmdHFCLK(ENABLE);
  CLOCK_CmdLFCLK(ENABLE);

  GPIO_Config();
  TIMER_Config();
  PPI_Config();
}
int main( void )
{
  System_Init();

  while(1) {
    LED3_Toggle();
    Delay_100ms(10);
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
void TIMER_Config( void )
{
  TIMER_TimeBaseInitTypeDef TIMER_TBInitStruct;

  TIMER_TBInitStruct.Mode      = NRF_TIMER_MODE_TIMER;
  TIMER_TBInitStruct.BitWidth  = NRF_TIMER_BIT_WIDTH_16;
  TIMER_TBInitStruct.Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(TIMERx, &TIMER_TBInitStruct);
  TIMER_CCInit(TIMERx, TIMERx_CH, 50 * 31.25f);

  TIMER_CC0Interrupt(TIMERx, ENABLE);
  NVIC_SetPriority(TIMERx_IRQ, 1);
  NVIC_EnableIRQ(TIMERx_IRQ);

  TIMER_TBInitStruct.Mode      = NRF_TIMER_MODE_TIMER;
  TIMER_TBInitStruct.BitWidth  = NRF_TIMER_BIT_WIDTH_16;
  TIMER_TBInitStruct.Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(NRF_TIMER1, &TIMER_TBInitStruct);
  TIMER_CCInit(NRF_TIMER1, TIMERx_CH, 1000 * 31.25f);

  TIMER_TBInitStruct.Mode      = NRF_TIMER_MODE_TIMER;
  TIMER_TBInitStruct.BitWidth  = NRF_TIMER_BIT_WIDTH_16;
  TIMER_TBInitStruct.Prescaler = NRF_TIMER_FREQ_31250Hz;
  TIMER_TimeBaseInit(NRF_TIMER2, &TIMER_TBInitStruct);
  TIMER_CCInit(NRF_TIMER2, TIMERx_CH, 2000 * 31.25f);

//  TIMER_Cmd(TIMERx, ENABLE);
  TIMER_Cmd(NRF_TIMER1, ENABLE);
  TIMER_Cmd(NRF_TIMER2, ENABLE);
}

void PPI_Config( void )
{
  PPI_InitTypeDef PPI_InitStruct;

  PPI_InitStruct.Channel       = PPI_CH1;
  PPI_InitStruct.EventEndPoint = (uint32_t)(&NRF_TIMER1->EVENTS_COMPARE[0]);
  PPI_InitStruct.TaskEndPoint  = (uint32_t)(&NRF_TIMER0->TASKS_STOP);
  PPI_Init(PPIx, &PPI_InitStruct);

  PPI_InitStruct.Channel       = PPI_CH2;
  PPI_InitStruct.EventEndPoint = (uint32_t)(&NRF_TIMER2->EVENTS_COMPARE[0]);
  PPI_InitStruct.TaskEndPoint  = (uint32_t)(&NRF_TIMER0->TASKS_START);
  PPI_Init(PPIx, &PPI_InitStruct);

  PPI_ChannelCmd(PPIx, PPI_CH1, ENABLE);
  PPI_ChannelCmd(PPIx, PPI_CH2, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
