/* #include "nrf51_typedef.h" */

#ifndef __NRF51_TYPEDEF_H
#define __NRF51_TYPEDEF_H

#include "nrf51.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   /*!< Read Only */
typedef const int16_t sc16;   /*!< Read Only */
typedef const int8_t  sc8;    /*!< Read Only */

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t  vs8;

typedef __I int32_t vsc32;    /*!< Read Only */
typedef __I int16_t vsc16;    /*!< Read Only */
typedef __I int8_t  vsc8;     /*!< Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t  uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;   /*!< Read Only */
typedef __I uint16_t vuc16;   /*!< Read Only */
typedef __I uint8_t  vuc8;    /*!< Read Only */

typedef double fp64;
typedef float  fp32;

typedef const double fpc64;
typedef const float  fpc32;

typedef __IO double vfp64;
typedef __IO float  vfp32;

typedef __I double vfpc64;
typedef __I float  vfpc32;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
/*====================================================================================================*/
/*====================================================================================================*/
#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

#define Byte32(Type, Byte4, Byte3, Byte2, Byte1)  ((Type)((((u8)(Byte4))<<24) | (((u8)(Byte3))<<16) | (((u8)(Byte2))<<8) | ((u8)(Byte1))))
#define Byte16(Type, ByteH, ByteL)  ((Type)((((u16)(ByteH))<<8) | ((u16)(ByteL))))
#define Byte8H(ByteH)   ((u8)(((u16)(ByteH))>>8))
#define Byte8L(ByteL)   ((u8)(ByteL))

#define NULL 0
/*====================================================================================================*/
/*====================================================================================================*/
#endif
