/* #include "nrf51_system.h" */

#ifndef __NRF51_SYSTEM_H
#define __NRF51_SYSTEM_H

#include "nrf51.h"
#include "nrf51_delay.h"
#include "nrf51_conf.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define U8_MAX    ((u8)255)
#define S8_MAX    ((s8)127)
#define S8_MIN    ((s8)-128)
#define U16_MAX   ((u16)65535u)
#define S16_MAX   ((s16)32767)
#define S16_MIN   ((s16)-32768)
#define U32_MAX   ((u32)4294967295uL)
#define S32_MAX   ((s32)2147483647)
#define S32_MIN   ((s32)-2147483648)

#define Byte32(Type, Byte4, Byte3, Byte2, Byte1)  ((Type)((((u8)(Byte4))<<24) | (((u8)(Byte3))<<16) | (((u8)(Byte2))<<8) | ((u8)(Byte1))))
#define Byte16(Type, ByteH, ByteL)  ((Type)((((u16)(ByteH))<<8) | ((u16)(ByteL))))
#define Byte8H(ByteH)   ((u8)(((u16)(ByteH))>>8))
#define Byte8L(ByteL)   ((u8)(ByteL))

#define NULL 0
/*====================================================================================================*/
/*====================================================================================================*/
#endif
