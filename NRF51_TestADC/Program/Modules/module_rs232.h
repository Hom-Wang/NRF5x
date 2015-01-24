/* #include "module_rs232.h" */

#ifndef __MODULE_RS232_H
#define __MODULE_RS232_H

#include "nrf51_system.h"
#include "algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void RS232_Config( void );
void RS232_SendByte( uint8_t SendByte );
void RS232_SendData( uint8_t *SendData, uint16_t DataLen );
void RS232_SendNum( StrType Type, uint8_t NumLen, int32_t SendData );
void RS232_SendStr( uint8_t *pWord );
void RS232_RecvByte( uint8_t *RecvData );
uint8_t RS232_RecvByteWTO( uint8_t *RecvData, int32_t Timeout_ms );
void RS232_RecvData( uint8_t *RecvData, uint16_t DataLen );
uint8_t RS232_RecvDataWTO( uint8_t *RecvData, uint16_t DataLen, int32_t Timeout_ms );
void RS232_RecvStr( uint8_t *pWord );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
