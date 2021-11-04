///*
// * CS4271.c
// *
// *  Created on: 28 Oct 2018
// *      Author: Tim
// */
//
//
#include "CS4271.h"


DMA_HandleTypeDef *hdma_spi2_tx;
DMA_HandleTypeDef *hdma_i2s2_ext_rx;

extern I2C_HandleTypeDef hi2c;

const uint8_t codec_init_data_slave_DCinput[] =
{
		SINGLE_SPEED|RATIO0|SLAVE|DIF_I2S_24b,		//MODECTRL1
		SLOW_FILT_SEL|DEEMPH_OFF,		//DACCTRL

		ATAPI_aLbR,			//DACMIX

		0,			//DACAVOL
		0,			//DACBVOL

		ADC_DIF_I2S
//		| HPFDisableA
//		| HPFDisableB 	//ADCCTRL

};


const uint8_t codec_init_data_slave[] =
{

		SINGLE_SPEED
		| RATIO0
		| SLAVE
		| DIF_I2S_24b,		//MODECTRL1

		SLOW_FILT_SEL
		| DEEMPH_OFF,		//DACCTRL

		ATAPI_aLbR,			//DACMIX

		0,			//DACAVOL
		0,			//DACBVOL

		ADC_DIF_I2S|MUTEA|MUTEB
	//	| HPFDisableA
	//	| HPFDisableB 	//ADCCTRL

};
const uint8_t codec_init_data_master[] =
{

		SINGLE_SPEED
		| RATIO0
		| MASTER
		| DIF_I2S_24b,//MODECTRL1

		FAST_FILT_SEL
		| DEEMPH_OFF
		| SOFT_RAMPUP
		| SOFT_RAMPDOWN,	//DACCTRL

		ATAPI_aLbR,			//DACMIX

		0,			//DACAVOL
		0,			//DACBVOL

		ADC_DIF_I2S
	/*	| HPFDisableA
		| HPFDisableB */	//ADCCTRL

};


//void cs4271_Init_I2S(I2S_HandleTypeDef * InpI2S, DMA_HandleTypeDef *pDmaTx, DMA_HandleTypeDef *pDmaRx)
//{
//	I2S_cs4271_configure(pDmaTx,pDmaRx);
//}

void cs4271_Init_I2S(I2S_HandleTypeDef *pI2S, DMA_HandleTypeDef *hdmatx, DMA_HandleTypeDef *hdmarx)
{

	hdma_spi2_tx=hdmatx;
	hdma_i2s2_ext_rx=hdmarx;

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
	/* DMA1_Stream5_IRQn interrupt configuration */
//		HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
//		HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

	pI2S->Instance = SPI2;
	pI2S->Init.Mode           = I2S_MODE_MASTER_TX;
	pI2S->Init.Standard       = I2S_STANDARD;
	pI2S->Init.DataFormat     = I2S_DATA_FORMAT;
	pI2S->Init.AudioFreq      = I2S_SAMPLING_FREQ;

	pI2S->Init.MCLKOutput     = I2S_MCLKOUTPUT_ENABLE;
	pI2S->Init.CPOL           = I2S_CPOL_LOW;
	pI2S->Init.ClockSource    = I2S_CLOCK_EXTERNAL;
	pI2S->Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
if (HAL_I2S_Init(pI2S) != HAL_OK)
	{
		BSP_Error_Handler();
	}

	CS4271_Reset;
	HAL_Delay(30);
	CS4271_Set;
//	HAL_Delay(1);
//	I2C_Transmit_data(0x20,0x7, (CPEN|PDN), &hi2c);
//	for(int i=0;i<CS4271_NUM_REGS;i++)
//	{
//		I2C_Transmit_data(0x20,i+1, codec_init_data_slave[i], &hi2c);
//	}

//	I2C_scan_dbg();



}

__weak void CS4271_TxRxCplt_Callback(void)
{

}
__weak void CS4271_TxRxHalfCplt_Callback(void)
{

}

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	CS4271_TxRxHalfCplt_Callback();
}
void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	CS4271_TxRxCplt_Callback();

}




//Begin recieving I2S from pcm186x in DMA mode
void cs4271_I2S_Start(I2S_HandleTypeDef *pI2S, uint16_t *pTxBuf, uint16_t *pRxBuf, size_t size)
{
	HAL_I2SEx_TransmitReceive_DMA(pI2S, pTxBuf, pRxBuf, size);
	CS4271_Reset;
	HAL_Delay(30);
	CS4271_Set;
	HAL_Delay(1);
	I2C_Transmit_data(0x20,0x7, (CPEN|PDN), &hi2c);
	for(int i=0;i<CS4271_NUM_REGS;i++)
	{
		I2C_Transmit_data(0x20,i+1, codec_init_data_slave[i], &hi2c);
	}
	I2C_Transmit_data(0x20,0x7, (CPEN), &hi2c);

	if(cs4271_I2C_Test(0x20)!=1)
	{
		BSP_Error_Handler();
		while(1){}
	}
}

int cs4271_I2C_Test(uint32_t addr)
{
	uint8_t datareg[8];
	for (int i=0; i<CS4271_NUM_REGS; i++)
	{
		I2C_Read_register(addr,i+1,&datareg[i],&hi2c);
		if(datareg[i]!=codec_init_data_slave[i]) return 0;
	}
	return 1;

}


void cs4271_MUTE_BOTH_CH(void)
{
	uint8_t datareg;
	I2C_Read_register(0x20,0x6,&datareg,&hi2c);
	HAL_Delay(30);
	datareg |=MUTEA;
	datareg |=MUTEB;
	I2C_Transmit_data(0x20,0x6, (datareg), &hi2c);
	datareg=0;
}

void cs4271_UNMUTE_BOTH_CH(void)
{
	uint8_t datareg;
	I2C_Read_register(0x20,0x6,&datareg,&hi2c);
	HAL_Delay(30);
	datareg &=~MUTEA;
	datareg &=~MUTEB;
	I2C_Transmit_data(0x20,0x6, (datareg), &hi2c);
}


