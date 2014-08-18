/* #include "module_rs232.h" */

#ifndef __MODULE_RS232_H
#define __MODULE_RS232_H

#include "nrf51_typedef.h"
#include "algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void RS232_Config( void );
void RS232_SendByte( u8 SendByte );
void RS232_SendData( u8 *SendData, u16 DataLen );
void RS232_SendNum( StrType Type, u8 NumLen, s32 SendData );
void RS232_SendStr( u8 *pWord );
void RS232_RecvByte( u8 *RecvData );
u8   RS232_RecvByteWTO( u8 *RecvData, s32 Timeout_ms );
void RS232_RecvData( u8 *RecvData, u16 DataLen );
u8   RS232_RecvDataWTO( u8 *RecvData, u16 DataLen, s32 Timeout_ms );
void RS232_RecvStr( u8 *pWord );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
