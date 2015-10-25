/* #include "nrf51_ppi.h" */

#ifndef __NRF51_PPI_H
#define __NRF51_PPI_H

#include "nrf51_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef enum {
  PPI_CH0 = 0,
  PPI_CH1,
  PPI_CH2,
  PPI_CH3,
  PPI_CH4,
  PPI_CH5,
  PPI_CH6,
  PPI_CH7,
  PPI_CH8,
  PPI_CH9,
  PPI_CH10,
  PPI_CH11,
  PPI_CH12,
  PPI_CH13,
  PPI_CH14,
  PPI_CH15,
  PPI_CH20,
  PPI_CH21,
  PPI_CH22,
  PPI_CH23,
  PPI_CH24,
  PPI_CH25,
  PPI_CH26,
  PPI_CH27,
  PPI_CH28,
  PPI_CH29,
  PPI_CH30,
  PPI_CH31
} PPI_CH_TypeDef;

typedef enum {
  PPI_CHG0 = 0,
  PPI_CHG1,
  PPI_CHG2,
  PPI_CHG3
} PPI_CHG_TypeDef;

typedef struct {
  PPI_CH_TypeDef Channel;
  uint32_t EventEndPoint;
  uint32_t TaskEndPoint;
} PPI_InitTypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void PPI_Init( NRF_PPI_Type *PPIx, PPI_InitTypeDef *PPI_InitStruct );
void PPI_ChannelCmd( NRF_PPI_Type *PPIx, PPI_CH_TypeDef PPIx_CH, uint8_t state );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
