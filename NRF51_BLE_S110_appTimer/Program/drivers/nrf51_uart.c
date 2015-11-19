/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_uart.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_Init
**功能 : UART Init
**輸入 : UART_InitStruct
**輸出 : None
**使用 : UART_Init(UARTx, &UART_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void UART_Init( NRF_UART_Type *UARTx, UART_InitTypeDef *UART_InitStruct )
{
  nrf_gpio_cfg_output(UART_InitStruct->PinTXD);
  nrf_gpio_cfg_input(UART_InitStruct->PinRXD, NRF_GPIO_PIN_NOPULL);

  UARTx->PSELTXD = UART_InitStruct->PinTXD;
  UARTx->PSELRXD = UART_InitStruct->PinRXD;

  if(UART_InitStruct->HardwareFlowControl == UART_CONFIG_HWFC_Enabled) {
    nrf_gpio_cfg_output(UART_InitStruct->PinRTS);
    nrf_gpio_cfg_input(UART_InitStruct->PinCTS, NRF_GPIO_PIN_NOPULL);
    UARTx->PSELCTS = UART_InitStruct->PinCTS;
    UARTx->PSELRTS = UART_InitStruct->PinRTS;
    UARTx->CONFIG  = UART_InitStruct->HardwareFlowControl << UART_CONFIG_HWFC_Pos;
  }

  UARTx->CONFIG        = (UART_InitStruct->Parity << UART_CONFIG_PARITY_Pos) | 
                         (UART_InitStruct->HardwareFlowControl << UART_CONFIG_HWFC_Pos);
  UARTx->BAUDRATE      = (UART_InitStruct->BaudRate << UART_BAUDRATE_BAUDRATE_Pos);
  UARTx->TASKS_STARTTX = 1;
  UARTx->TASKS_STARTRX = 1;
  UARTx->EVENTS_RXDRDY = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_Cmd
**功能 : UART Enable / Disable
**輸入 : None
**輸出 : None
**使用 : UART_Cmd(UARTx, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void UART_Cmd( NRF_UART_Type *UARTx, uint8_t state )
{
  if(state == ENABLE)
    UARTx->ENABLE = UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos;
  else
    UARTx->ENABLE = UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_InterruptCmd
**功能 : UART Interrupt Enable / Disable
**輸入 : None
**輸出 : None
**使用 : UART_InterruptCmd(UARTx, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void UART_InterruptCmd( NRF_UART_Type *UARTx, uint8_t state )
{
  if(state == ENABLE)
    UARTx->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
  else
    UARTx->INTENCLR = UART_INTENCLR_RXDRDY_Enabled << UART_INTENCLR_RXDRDY_Pos;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendByte
**功能 : Send Byte
**輸入 : *sendData
**輸出 : None
**使用 : UART_SendByte(UARTx, 'A');
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( NRF_UART_Type *UARTx, uint8_t *sendByte )
{
  UARTx->TXD = *sendByte;
  while(UARTx->EVENTS_TXDRDY != 1);   // Wait for TXD data to be sent
  UARTx->EVENTS_TXDRDY = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByte
**功能 : Recv Byte
**輸入 : None
**輸出 : recvData
**使用 : RecvByte = UART_RecvByte(UARTx, recvData);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvByte( NRF_UART_Type *UARTx, uint8_t *recvData )
{
  while(UARTx->EVENTS_RXDRDY != 1);  // Wait for RXD data to be received
  UARTx->EVENTS_RXDRDY = 0;
  *recvData = (uint8_t)UARTx->RXD;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByteWTO
**功能 : Recv Byte Wait Timeout
**輸入 : *recvData, timeoutMs
**輸出 : State
**使用 : State = UART_RecvByteWTO(UARTx, recvData, timeoutMs);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvByteWTO( NRF_UART_Type *UARTx, uint8_t *recvData, int32_t timeoutMs )
{
  while(UARTx->EVENTS_RXDRDY != 1) {
    if(timeoutMs-- >= 0)
      Delay_1ms(1);
    else
      return ERROR; // timeout
  }

  UARTx->EVENTS_RXDRDY = 0;
  *recvData = (uint8_t)UARTx->RXD;

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendData
**功能 : Send Data
**輸入 : *sendData, lens
**輸出 : None
**使用 : UART_SendByte(UARTx, sendData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendData( NRF_UART_Type *UARTx, uint8_t *sendData, uint16_t lens )
{
  do {
    UART_SendByte(UARTx, sendData++);
  } while(--lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : Recv Data
**輸入 : *recvData, lens
**輸出 : None
**使用 : UART_RecvData(UARTx, recvData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvData( NRF_UART_Type *UARTx, uint8_t *recvData, uint16_t lens )
{
  do {
    UART_RecvByte(UARTx, recvData++);
  } while(--lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvDataWTO
**功能 : Recv Data With Timeout
**輸入 : *recvData, lens, timeoutMs
**輸出 : None
**使用 : UART_RecvData(UARTx, recvData, lens, timeoutMs);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvDataWTO( NRF_UART_Type *UARTx, uint8_t *recvData, uint16_t lens, int32_t timeoutMs )
{
  int8_t state = ERROR;

  do {
    state = UART_RecvByteWTO(UARTx, recvData++, timeoutMs);
  } while((--lens) && (state != ERROR));

  return state;
}
/*====================================================================================================*/
/*====================================================================================================*/
