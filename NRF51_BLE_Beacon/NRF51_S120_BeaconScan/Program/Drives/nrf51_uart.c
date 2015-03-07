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
**使用 : UART_Init(NRF_UART0, &UART_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void UART_Init( NRF_UART_Type *UARTx, UART_InitTypeDef *UART_InitStruct )
{
  nrf_gpio_cfg_output(UART_InitStruct->UART_PinTXD);
  nrf_gpio_cfg_input(UART_InitStruct->UART_PinRXD, NRF_GPIO_PIN_NOPULL);

  UARTx->PSELTXD = UART_InitStruct->UART_PinTXD;
  UARTx->PSELRXD = UART_InitStruct->UART_PinRXD;

  if(UART_InitStruct->UART_HardwareFlowControl == UART_CONFIG_HWFC_Enabled) {
    nrf_gpio_cfg_output(UART_InitStruct->UART_PinRTS);
    nrf_gpio_cfg_input(UART_InitStruct->UART_PinCTS, NRF_GPIO_PIN_NOPULL);
    UARTx->PSELCTS = UART_InitStruct->UART_PinCTS;
    UARTx->PSELRTS = UART_InitStruct->UART_PinRTS;
    UARTx->CONFIG  = UART_InitStruct->UART_HardwareFlowControl << UART_CONFIG_HWFC_Pos;
  }

  UARTx->CONFIG        = (UART_InitStruct->UART_Parity << UART_CONFIG_PARITY_Pos) | 
                         (UART_InitStruct->UART_HardwareFlowControl << UART_CONFIG_HWFC_Pos);
  UARTx->BAUDRATE      = (UART_InitStruct->UART_BaudRate << UART_BAUDRATE_BAUDRATE_Pos);
  UARTx->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
  UARTx->TASKS_STARTTX = 1;
  UARTx->TASKS_STARTRX = 1;
  UARTx->EVENTS_RXDRDY = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_InterruptCmd
**功能 : UART Interrupt Enable / Disable
**輸入 : None
**輸出 : None
**使用 : UART_InterruptCmd(NRF_UART0, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void UART_InterruptCmd( NRF_UART_Type *UARTx, FunctionalState NewState )
{
  if(NewState == ENABLE)
    UARTx->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
  else
    UARTx->INTENCLR = UART_INTENCLR_RXDRDY_Enabled << UART_INTENCLR_RXDRDY_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendByte
**功能 : 發送 1Byte 資料
**輸入 : UARTx, *SendData
**輸出 : None
**使用 : UART_SendByte(NRF_UART0, SendData);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( NRF_UART_Type *UARTx, int8_t *SendData )
{
  UARTx->TXD = (uint8_t)(*SendData);
  while(UARTx->EVENTS_TXDRDY != SUCCESS);   // Wait for TXD data to be sent
  UARTx->EVENTS_TXDRDY = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByte
**功能 : 接收 1Byte 資料
**輸入 : UARTx, *RecvByte
**輸出 : None
**使用 : UART_RecvByte(NRF_UART0, RecvData);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvByte( NRF_UART_Type *UARTx, int8_t *RecvData )
{
  while(UARTx->EVENTS_RXDRDY != SUCCESS);  // Wait for RXD data to be received
  UARTx->EVENTS_RXDRDY = 0;
  *RecvData = (int8_t)UARTx->RXD;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByteWTO
**功能 : 接收 1Byte 資料, 並加入 Timeout 功能
**輸入 : UARTx, *RecvByte, TimeoutMs
**輸出 : State
**使用 : UART_RecvByteWTO(NRF_UART0, RecvData, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvByteWTO( NRF_UART_Type *UARTx, int8_t *RecvData, int32_t TimeoutMs )
{
  while(UARTx->EVENTS_RXDRDY != SUCCESS) {
    if(TimeoutMs >= 0) {
      TimeoutMs--;
      Delay_1ms(1);
    }
    else {
      return ERROR; // timeout
    }
  }

  UARTx->EVENTS_RXDRDY = 0;
  *RecvData = (int8_t)UARTx->RXD;

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendData
**功能 : 發送資料
**輸入 : UARTx, *SendData, DataLen
**輸出 : None
**使用 : UART_SendByte(NRF_UART0, SendData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendData( NRF_UART_Type *UARTx, int8_t *SendData, uint16_t DataLen )
{
  do {
    UART_SendByte(UARTx, SendData);
    SendData++;
  } while(--DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : 接收資料
**輸入 : UARTx, *RecvData, DataLen
**輸出 : None
**使用 : UART_RecvData(NRF_UART0, RecvData, DataLen);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvData( NRF_UART_Type *UARTx, int8_t *RecvData, uint16_t DataLen )
{
  do {
    UART_RecvByte(UARTx, RecvData++);
  } while(--DataLen);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvDataWTO
**功能 : 接收資料, 並加入 Timeout 功能
**輸入 : UARTx, *RecvByte, DataLen, TimeoutMs
**輸出 : State
**使用 : UART_RecvDataWTO(NRF_UART0, RecvData, DataLen, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvDataWTO( NRF_UART_Type *UARTx, int8_t *RecvData, uint16_t DataLen, int32_t TimeoutMs )
{
  int8_t State = ERROR;

  do {
    State = UART_RecvByteWTO(UARTx, RecvData++, TimeoutMs);
    if(State == ERROR)
      return ERROR;
  } while(--DataLen);

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*/
