/* #include "module_rs232.h" */

#ifndef __MODULE_RS232_H
#define __MODULE_RS232_H

#include "drivers\nrf51_system.h"
#include "algorithms\algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void   RS232_Config( void );
void   RS232_SendByte( uint8_t SendByte );
void   RS232_SendData( uint8_t *SendData, uint16_t DataLen );
void   RS232_SendStr( char *pWord );
void   RS232_SendNum( StrType Type, uint8_t NumLen, int32_t SendData );
int8_t RS232_RecvByte( void );
void   RS232_RecvData( uint8_t *RecvData, uint16_t DataLen );
int8_t RS232_RecvDataWTO( uint8_t *RecvData, uint16_t DataLen, int32_t Timeout_ms );
void   RS232_RecvStr( char *pWord );
int8_t RS232_RecvStrWTO( char *pWord, int32_t TimeoutMs );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
