/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_delay.h"
#include "nrf51_uart.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_Init
**功能 : UART 初始化
**輸入 : UART_InitStruct
**輸出 : None
**使用 : UART_Init(&UART_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void UART_Init( UART_InitTypeDef *UART_InitStruct )
{
  nrf_gpio_cfg_output(UART_InitStruct->UART_PinTXD);
  nrf_gpio_cfg_input(UART_InitStruct->UART_PinRXD, NRF_GPIO_PIN_NOPULL);

  NRF_UART0->PSELTXD = UART_InitStruct->UART_PinTXD;
  NRF_UART0->PSELRXD = UART_InitStruct->UART_PinRXD;

  if( UART_InitStruct->UART_HardwareFlowControl == UART_CONFIG_HWFC_Enabled) {
    nrf_gpio_cfg_output(UART_InitStruct->UART_PinRTS);
    nrf_gpio_cfg_input(UART_InitStruct->UART_PinCTS, NRF_GPIO_PIN_NOPULL);
    NRF_UART0->PSELCTS = UART_InitStruct->UART_PinCTS;
    NRF_UART0->PSELRTS = UART_InitStruct->UART_PinRTS;
    NRF_UART0->CONFIG  = UART_InitStruct->UART_HardwareFlowControl << UART_CONFIG_HWFC_Pos;
  }

  NRF_UART0->CONFIG           = (UART_InitStruct->UART_Parity              << UART_CONFIG_PARITY_Pos) | 
                                (UART_InitStruct->UART_HardwareFlowControl << UART_CONFIG_HWFC_Pos);
  NRF_UART0->BAUDRATE         = (UART_InitStruct->UART_BaudRate << UART_BAUDRATE_BAUDRATE_Pos);
  NRF_UART0->ENABLE           = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
  NRF_UART0->TASKS_STARTTX    = 1;
  NRF_UART0->TASKS_STARTRX    = 1;
  NRF_UART0->EVENTS_RXDRDY    = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_InterruptEnable
**功能 : UART Interrupt Enable
**輸入 : None
**輸出 : None
**使用 : UART_InterruptEnable();
**====================================================================================================*/
/*====================================================================================================*/
void UART_InterruptEnable( void )
{
  NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_InterruptDisable
**功能 : UART Interrupt Disable
**輸入 : None
**輸出 : None
**使用 : UART_InterruptDisable();
**====================================================================================================*/
/*====================================================================================================*/
void UART_InterruptDisable( void )
{
  NRF_UART0->INTENCLR = UART_INTENCLR_RXDRDY_Enabled << UART_INTENCLR_RXDRDY_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendByte
**功能 : 發送 1Byte 資料
**輸入 : *SendData
**輸出 : None
**使用 : UART_SendByte('A');
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( u8 SendByte )
{
  NRF_UART0->TXD = (u8)SendByte;

  while(NRF_UART0->EVENTS_TXDRDY != 1);   // Wait for TXD data to be sent

  NRF_UART0->EVENTS_TXDRDY = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByte
**功能 : 接收 1Byte 資料
**輸入 : None
**輸出 : RecvByte
**使用 : RecvByte = UART_RecvByte();
**====================================================================================================*/
/*====================================================================================================*/
u8 UART_RecvByte( void )
{
  while(NRF_UART0->EVENTS_RXDRDY != 1);  // Wait for RXD data to be received

  NRF_UART0->EVENTS_RXDRDY = 0;

  return ((u8)NRF_UART0->RXD);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByteWTO
**功能 : 接收 1Byte 資料
**輸入 : *RecvData, Timeout_ms
**輸出 : State
**使用 : State = UART_RecvByteWTO(RecvData, Timeout_ms);
**====================================================================================================*/
/*====================================================================================================*/
u8 UART_RecvByteWTO( u8 *RecvData, s32 Timeout_ms )
{
  u8 State = ERROR;

  while(NRF_UART0->EVENTS_RXDRDY != 1) {
    if(Timeout_ms >= 0) {
      Timeout_ms--;
      Delay_1ms(1);
    }
    else {
      State = SUCCESS;
      break;
    }
  }

  if(Timeout_ms > 0) {
    NRF_UART0->EVENTS_RXDRDY = 0;
    *RecvData = (uint8_t)NRF_UART0->RXD;
  }

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendData
**功能 : 發送資料
**輸入 : *SendData, DataLen
**輸出 : None
**使用 : UART_SendByte(SendData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendData( u8 *SendData, u16 DataLen )
{
  do {
    UART_SendByte(*SendData);
    SendData++;
    DataLen--;
  } while(DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : 接收資料
**輸入 : *RecvData, DataLen
**輸出 : None
**使用 : UART_RecvData(RecvData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvData( u8 *RecvData, u16 DataLen )
{
  do {
    *RecvData = UART_RecvByte();
    RecvData++;
    DataLen--;
  } while(DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : 接收資料
**輸入 : *RecvData, DataLen, Timeout_ms
**輸出 : None
**使用 : UART_RecvData(RecvData, DataLen, Timeout_ms);
**====================================================================================================*/
/*====================================================================================================*/
u8 UART_RecvDataWTO( u8 *RecvData, u16 DataLen, s32 Timeout_ms )
{
  u8 State = ERROR;

  do {
    State = UART_RecvByteWTO(RecvData, Timeout_ms);
    RecvData++;
    DataLen--;
  } while(DataLen && (State != ERROR));

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*/
