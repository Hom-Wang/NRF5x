/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_ppi.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : PPI_Init
**功能 : PPI Init
**輸入 : None
**輸出 : None
**使用 : PPI_Init(PPIx, &PPI_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void PPI_Init( NRF_PPI_Type *PPIx, PPI_InitTypeDef *PPI_InitStruct )
{
  PPIx->CH[PPI_InitStruct->Channel].EEP = PPI_InitStruct->EventEndPoint;
  PPIx->CH[PPI_InitStruct->Channel].TEP = PPI_InitStruct->TaskEndPoint;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : PPI_ChannelCmd
**功能 : Enable / Disable PPI Channel
**輸入 : PPIx, state
**輸出 : None
**使用 : PPI_ChannelCmd(PPIx, PPIx_CH, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void PPI_ChannelCmd( NRF_PPI_Type *PPIx, PPI_CH_TypeDef PPIx_CH, uint8_t state )
{
  uint32_t tmpReg = 0;

  tmpReg = (state == ENABLE) ? PPIx->CHENSET : PPIx->CHENCLR;

  switch(PPIx_CH) {
    case PPI_CH0:   tmpReg |= (PPI_CHEN_CH0_Enabled  << PPI_CHEN_CH0_Pos);  break;
    case PPI_CH1:   tmpReg |= (PPI_CHEN_CH1_Enabled  << PPI_CHEN_CH1_Pos);  break;
    case PPI_CH2:   tmpReg |= (PPI_CHEN_CH2_Enabled  << PPI_CHEN_CH2_Pos);  break;
    case PPI_CH3:   tmpReg |= (PPI_CHEN_CH3_Enabled  << PPI_CHEN_CH3_Pos);  break;
    case PPI_CH4:   tmpReg |= (PPI_CHEN_CH4_Enabled  << PPI_CHEN_CH4_Pos);  break;
    case PPI_CH5:   tmpReg |= (PPI_CHEN_CH5_Enabled  << PPI_CHEN_CH5_Pos);  break;
    case PPI_CH6:   tmpReg |= (PPI_CHEN_CH6_Enabled  << PPI_CHEN_CH6_Pos);  break;
    case PPI_CH7:   tmpReg |= (PPI_CHEN_CH7_Enabled  << PPI_CHEN_CH7_Pos);  break;
    case PPI_CH8:   tmpReg |= (PPI_CHEN_CH8_Enabled  << PPI_CHEN_CH8_Pos);  break;
    case PPI_CH9:   tmpReg |= (PPI_CHEN_CH9_Enabled  << PPI_CHEN_CH9_Pos);  break;
    case PPI_CH10:  tmpReg |= (PPI_CHEN_CH10_Enabled << PPI_CHEN_CH10_Pos); break;
    case PPI_CH11:  tmpReg |= (PPI_CHEN_CH11_Enabled << PPI_CHEN_CH11_Pos); break;
    case PPI_CH12:  tmpReg |= (PPI_CHEN_CH12_Enabled << PPI_CHEN_CH12_Pos); break;
    case PPI_CH13:  tmpReg |= (PPI_CHEN_CH13_Enabled << PPI_CHEN_CH13_Pos); break;
    case PPI_CH14:  tmpReg |= (PPI_CHEN_CH14_Enabled << PPI_CHEN_CH14_Pos); break;
    case PPI_CH15:  tmpReg |= (PPI_CHEN_CH15_Enabled << PPI_CHEN_CH15_Pos); break;
    case PPI_CH20:  tmpReg |= (PPI_CHEN_CH20_Enabled << PPI_CHEN_CH20_Pos); break;
    case PPI_CH21:  tmpReg |= (PPI_CHEN_CH21_Enabled << PPI_CHEN_CH21_Pos); break;
    case PPI_CH22:  tmpReg |= (PPI_CHEN_CH22_Enabled << PPI_CHEN_CH22_Pos); break;
    case PPI_CH23:  tmpReg |= (PPI_CHEN_CH23_Enabled << PPI_CHEN_CH23_Pos); break;
    case PPI_CH24:  tmpReg |= (PPI_CHEN_CH24_Enabled << PPI_CHEN_CH24_Pos); break;
    case PPI_CH25:  tmpReg |= (PPI_CHEN_CH25_Enabled << PPI_CHEN_CH25_Pos); break;
    case PPI_CH26:  tmpReg |= (PPI_CHEN_CH26_Enabled << PPI_CHEN_CH26_Pos); break;
    case PPI_CH27:  tmpReg |= (PPI_CHEN_CH27_Enabled << PPI_CHEN_CH27_Pos); break;
    case PPI_CH28:  tmpReg |= (PPI_CHEN_CH28_Enabled << PPI_CHEN_CH28_Pos); break;
    case PPI_CH29:  tmpReg |= (PPI_CHEN_CH29_Enabled << PPI_CHEN_CH29_Pos); break;
    case PPI_CH30:  tmpReg |= (PPI_CHEN_CH30_Enabled << PPI_CHEN_CH30_Pos); break;
    case PPI_CH31:  tmpReg |= (PPI_CHEN_CH31_Enabled << PPI_CHEN_CH31_Pos); break;
  }

  if(state == ENABLE)
    PPIx->CHENSET = tmpReg;
  else
    PPIx->CHENCLR = tmpReg;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
