///*
// * CS4271.h
// *
// *  Created on: 28 Oct 2018
// *      Author: Tim
// */
//
#ifndef BSP_COMPONENTS_CS4271_CS4271_H_
#define BSP_COMPONENTS_CS4271_CS4271_H_
//
#include "stm32f4xx_hal.h"
#include "../../debug.h"
#include "../../peripherials/i2c.h"
#include "../../codec.h"

#define CS4271_NUM_REGS 6	/* we only initialize the first 6 registers, the 7th is for pre/post-init and the 8th is read-only */


#define SINGLE_SPEED 		(0x0<<6)
#define SINGLE_SPEED2 		(0x1<<6)
#define DOUBLE_SPEED		(0x2<<6)		/* 50-100kHz */
#define QUAD_SPEED			(0x3<<6)		/* 100-200kHz */
#define	RATIO0				(0x0<<4)		/* See table page 28 and 29 of datasheet */
#define	RATIO1				(0x1<<4)
#define	RATIO2				(0x2<<4)
#define	RATIO3				(0<<4)
#define	MASTER				(0x1<<3)
#define	SLAVE				(0x0<<3)
#define	DIF_LEFTJUST_24b	(0x0)
#define	DIF_I2S_24b			(0x1)
#define	DIF_RIGHTJUST_16b	(0x2)
#define	DIF_RIGHTJUST_24b	(0x3)
#define	DIF_RIGHTJUST_20b	(0x4)
#define	DIF_RIGHTJUST_18b	(0x5)

//Reg 2 (DACCTRL)
#define AUTOMUTE 		(1<<7)
#define SLOW_FILT_SEL	(1<<6)
#define FAST_FILT_SEL	(0<<6)
#define DEEMPH_OFF		(0<<4)
#define DEEMPH_44		(1<<4)
#define DEEMPH_48		(2<<4)
#define DEEMPH_32		(3<<4)
#define	SOFT_RAMPUP		(1<<3) /*An un-mute will be performed after executing a filter mode change, after a MCLK/LRCK ratio change or error, and after changing the Functional Mode.*/
#define	SOFT_RAMPDOWN	(1<<2) /*A mute will be performed prior to executing a filter mode change.*/
#define INVERT_SIGA_POL	(1<<1) /*When set, this bit activates an inversion of the signal polarity for the appropriate channel*/
#define INVERT_SIGB_POL	(1<<0)

//Reg 3 (DACMIX)
#define BEQA			(1<<6) /*If set, ignore AOUTB volume setting, and instead make channel B's volume equal channel A's volume as set by AOUTA */
#define SOFTRAMP		(1<<5) /*Allows level changes, both muting and attenuation, to be implemented by incrementally ramping, in 1/8 dB steps, from the current level to the new level at a rate of 1 dB per 8 left/right clock periods */
#define	ZEROCROSS		(1<<4) /*Dictates that signal level changes, either by attenuation changes or muting, will occur on a signal zero crossing to minimize audible artifacts*/
#define ATAPI_aLbR		(9) /*channel A==>Left, channel B==>Right*/

//Reg 4: DACAVOL
//Reg 5: DACBVOL

//Reg 6 (ADCCTRL)
#define DITHER16		(1<<5) /*activates the Dither for 16-Bit Data feature*/
#define ADC_DIF_I2S		(1<<4) /*I2S, up to 24-bit data*/
#define ADC_DIF_LJUST	(0<<4) /*Left Justified, up to 24-bit data (default)*/
#define MUTEA			(1<<3)
#define MUTEB			(1<<2)
#define HPFDisableA		(1<<1)
#define HPFDisableB		(1<<0)


//Reg 7 (MODECTRL2)
#define PDN		(1<<0)		/* Power Down Enable */
#define CPEN	(1<<1)		/* Control Port Enable */
#define FREEZE	(1<<2)		/* Freezes effects of register changes */
#define MUTECAB	(1<<3)		/* Internal AND gate on AMUTEC and BMUTEC */
#define LOOP	(1<<4)		/* Digital loopback (ADC->DAC) */

//Reg 8 (CHIPID) (Read-only)
#define PART_mask	(0xF0)
#define REV_mask	(0xF)



#define CS4271_Set   HAL_GPIO_WritePin(CODEC_RST_PORT, CODEC_RST_PIN,GPIO_PIN_SET)
#define CS4271_Reset HAL_GPIO_WritePin(CODEC_RST_PORT, CODEC_RST_PIN, GPIO_PIN_RESET)

void CS4271_TxRxCplt_Callback(void);
void CS4271_TxRxHalfCplt_Callback(void);

void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef *hi2s);
void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
void cs4271_I2S_Start(I2S_HandleTypeDef *pI2S, uint16_t *pTxBuf, uint16_t *pRxBuf, size_t size);
void cs4271_Init_I2S(I2S_HandleTypeDef *pI2S, DMA_HandleTypeDef *hdmatx, DMA_HandleTypeDef *hdmarx);
int cs4271_I2C_Test(uint32_t addr);
void cs4271_MUTE_BOTH_CH(void);
void cs4271_UNMUTE_BOTH_CH(void);

#endif /* BSP_COMPONENTS_CS4271_CS4271_H_ */
