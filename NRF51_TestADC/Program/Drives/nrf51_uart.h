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
  u32 UART_Parity;
  // UART_CONFIG_PARITY_Excluded - Parity bit excluded.
  // UART_CONFIG_PARITY_Included - Parity bit included.
  u32 UART_HardwareFlowControl;
  // UART_CONFIG_HWFC_Disabled - Hardware flow control disabled.
  // UART_CONFIG_HWFC_Enabled  - Hardware flow control enabled.
  u32 UART_BaudRate;
  // UART_BAUDRATE_BAUDRATE_Baud1200   -   1200 baud.
  // UART_BAUDRATE_BAUDRATE_Baud2400   -   2400 baud.
  // UART_BAUDRATE_BAUDRATE_Baud4800   -   4800 baud.
  // UART_BAUDRATE_BAUDRATE_Baud9600   -   9600 baud.
  // UART_BAUDRATE_BAUDRATE_Baud14400  -  14400 baud.
  // UART_BAUDRATE_BAUDRATE_Baud19200  -  19200 baud.
  // UART_BAUDRATE_BAUDRATE_Baud28800  -  28800 baud.
  // UART_BAUDRATE_BAUDRATE_Baud38400  -  38400 baud.
  // UART_BAUDRATE_BAUDRATE_Baud57600  -  57600 baud.
  // UART_BAUDRATE_BAUDRATE_Baud76800  -  76800 baud.
  // UART_BAUDRATE_BAUDRATE_Baud115200 - 115200 baud.
  // UART_BAUDRATE_BAUDRATE_Baud230400 - 230400 baud.
  // UART_BAUDRATE_BAUDRATE_Baud250000 - 250000 baud.
  // UART_BAUDRATE_BAUDRATE_Baud460800 - 460800 baud.
  // UART_BAUDRATE_BAUDRATE_Baud921600 - 921600 baud.
  // UART_BAUDRATE_BAUDRATE_Baud1M     -     1M baud.
} UART_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void UART_Init( UART_InitTypeDef *UART_InitStruct );
void UART_InterruptCmd( FunctionalState NewState );

void UART_SendByte( u8 SendData );
u8   UART_RecvByte( void );
u8   UART_RecvByteWTO( u8 *RecvData, s32 Timeout_ms );
void UART_SendData( u8 *SendData, u16 DataLen );
void UART_RecvData( u8 *RecvData, u16 DataLen );
u8   UART_RecvDataWTO( u8 *RecvData, u16 DataLen, s32 Timeout_ms );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
