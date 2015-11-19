/* #include "nrf51_uart.h" */

#ifndef __NRF51_UART_H
#define __NRF51_UART_H

#include "drivers\nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  uint8_t  PinTXD;
  uint8_t  PinRXD;
  uint8_t  PinRTS;
  uint8_t  PinCTS;
  uint32_t Parity;
  // UART_CONFIG_PARITY_Excluded - Parity bit excluded.
  // UART_CONFIG_PARITY_Included - Parity bit included.
  uint32_t HardwareFlowControl;
  // UART_CONFIG_HWFC_Disabled - Hardware flow control disabled.
  // UART_CONFIG_HWFC_Enabled  - Hardware flow control enabled.
  uint32_t BaudRate;
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
void    UART_Init( NRF_UART_Type *UARTx, UART_InitTypeDef *UART_InitStruct );
void    UART_Cmd( NRF_UART_Type *UARTx, uint8_t state );
void    UART_InterruptCmd( NRF_UART_Type *UARTx, uint8_t state );
void    UART_SendByte( NRF_UART_Type *UARTx, uint8_t *sendByte );
void    UART_RecvByte( NRF_UART_Type *UARTx, uint8_t *recvData );
int8_t  UART_RecvByteWTO( NRF_UART_Type *UARTx, uint8_t *recvData, int32_t timeoutMs );
void    UART_SendData( NRF_UART_Type *UARTx, uint8_t *sendData, uint16_t lens );
void    UART_RecvData( NRF_UART_Type *UARTx, uint8_t *recvData, uint16_t lens );
int8_t  UART_RecvDataWTO( NRF_UART_Type *UARTx, uint8_t *recvData, uint16_t lens, int32_t timeoutMs );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
