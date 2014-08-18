/* #include "nrf51_uart.h" */

#ifndef __NRF51_UART_H
#define __NRF51_UART_H

#include "nrf51_typedef.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  u8  UART_PinTXD;
  u8  UART_PinRXD;
  u8  UART_PinRTS;
  u8  UART_PinCTS;
  u16 UART_Parity;
  u16 UART_HardwareFlowControl;
  u32 UART_BaudRate;
} UART_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void UART_Init( UART_InitTypeDef *UART_InitStruct );

void UART_SendByte( u8 SendData );
u8   UART_RecvByte( void );
u8   UART_RecvByteWTO( u8 *RecvData, s32 Timeout_ms );
void UART_SendData( u8 *SendData, u16 DataLen );
void UART_RecvData( u8 *RecvData, u16 DataLen );
u8   UART_RecvDataWTO( u8 *RecvData, u16 DataLen, s32 Timeout_ms );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
