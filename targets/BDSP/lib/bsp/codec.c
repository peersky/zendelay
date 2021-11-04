#include "codec.h"
#include <string.h>
#include "arm_math.h"
static Codec_Base_TypeDef CodecA_Write_Val_24b(float Data);
static float CodecA_Read_Val_24b(void);
static Codec_i2s_HandleTypeDef CodecA;
static inline void float_to_codec(float fVal, uint16_t *Val1, uint16_t *Val2);
static inline float codec_to_float(uint16_t Val1, uint16_t Val2);
// static Codec_SAI_HandleTypeDef CodecB;
//Pointer to the ADC device structure
//This is used because I can't pass device struct to the interrupt callbacks

/*
Configures Input or output I2S devices
 */
void Codec_configure_CodecA(void)
{
	memset(&CodecA.data.buffer_tx, 0, sizeof(CodecA.data.buffer_tx));
	memset(&CodecA.data.buffer_rx, 0, sizeof(CodecA.data.buffer_rx));
	CodecA.data.IO_state = IO_BUFFER_STATE_FULL;
	CodecA.data.IO_state_tx = IO_BUFFER_STATE_FULL;
	CodecA.data.DMA_state = BUFFER_OFFSET_NONE;
	CodecA.data.DMA_state_tx = BUFFER_OFFSET_NONE;

#ifdef CODEC_CS4271
	cs4271_Init_I2S(&CodecA.i2s, &CodecA.dma_tx, &CodecA.dma_rx);
#else
#error "something not defined"
#endif
}

/*
Starts  I2S devices
*/
void Codec_start_CodecA(void)
{
	uint8_t codec_inited = 0;
	//Set Index at max to wait for DMA data
	CodecA.data.IO_index = I2S_INPUT_BUFFER_SIZE * 2;
	CodecA.data.IO_index = I2S_INPUT_BUFFER_SIZE * 2;
	cs4271_I2S_Start(&CodecA.i2s, CodecA.data.buffer_tx, CodecA.data.buffer_rx, I2S_INPUT_BUFFER_SIZE * 2);
	volatile DMA_Buff_StateTypeDef entry_state = CodecA.data.DMA_state;
	if (!codec_inited)
	{

		while (CodecA.data.DMA_state == entry_state)
		{
			//			__NOP;
		}
		cs4271_UNMUTE_BOTH_CH();
		codec_inited = 1;
	}
}

//int Codecs_test(uint8_t test_n)
//{
//	switch(test_n)
//	{
//	case 1:
//		return cs4271_I2C_Test(0x20);
//		break;
//	case 2:
//		return Codec_Audio_Test(&CodecA,1);
//		break;
//	case 3:
//		return Codec_Audio_Test(&CodecA,0);
//		break;
//	case 4:
////		return Codec_Audio_Test(&CodecB);
//		return 0;
//		break;
//	default:
//		BSP_Error_Handler();
//		return 0;
//	}
//}

int Codec_Audio_Test(Codec_i2s_HandleTypeDef *Codec, uint8_t ch)
{
	for (uint32_t i = 0; i < 48000; i++)
	{
		float ReadVal = CodecA_Read_Val_24b();
		CodecA_Write_Val_24b(ReadVal);
	}
	float temp_buf[1000];
	float temp_buf2[48 * 5];
	float result;

	for (uint32_t __IO i = 0; i < 48 * 5; i++)
	{
		for (int __IO k = 0; k < 1000; k++)
		{
			signed int ReadVal = ((signed int)CodecA_Read_Val_24b() >> 8);
			signed int ReadVal2 = ((signed int)CodecA_Read_Val_24b() >> 8);
			CodecA_Write_Val_24b((float)ReadVal);
			CodecA_Write_Val_24b((float)ReadVal);

			if (ch)
			{
				temp_buf[k] = (float)ReadVal;
			}
			else
			{
				temp_buf[k] = (float)ReadVal2;
			}
		}
		arm_rms_f32(temp_buf, 1000, &temp_buf2[i]);
	}
	arm_rms_f32(temp_buf2, 48 * 5, &result);

	float upper_lim = 2.9e6;
	float lower_lim = 2.3e6;
	if (result < upper_lim)
	{
		if (result > lower_lim)
		{
			return 1;
		}
	}
	return 0;
}

float CodecA_Read_Write_24b(float Data)
{

	CodecA_Write_Val_24b(Data);
	float retval = CodecA_Read_Val_24b();
	CodecA.data.IO_index += 2;

	return retval;
}

static Codec_Base_TypeDef CodecA_Write_Val_24b(float Data)
{
	uint16_t Val1, Val2;
	float_to_codec(Data, &Val1, &Val2);
	CodecA.data.IO_buffer_tx[CodecA.data.IO_index] = Val1;
	CodecA.data.IO_buffer_tx[CodecA.data.IO_index + 1] = Val2;

	return Codec_OK;
}

static float CodecA_Read_Val_24b(void)
{

	uint16_t Val1, Val2;
	Val1 = CodecA.data.IO_buffer_rx[CodecA.data.IO_index];
	Val2 = CodecA.data.IO_buffer_rx[CodecA.data.IO_index + 1];
	return codec_to_float(Val1, Val2);
}

void codec_flush_buffers(void)
{
	CodecA.data.IO_state = IO_BUFFER_STATE_FULL;
	uint32_t offset = 0;
	if (CodecA.data.DMA_state != BUFFER_OFFSET_HALF)
	{
		offset = I2S_INPUT_SAMPLES_NUM;
	}
	else
	{
		offset = 0;
	}
	uint16_t tval1;

	for (volatile uint32_t i = 0; i < I2S_INPUT_SAMPLES_NUM; i++)
	{
		tval1 = CodecA.data.buffer_rx[i + offset];
		CodecA.data.IO_buffer_rx[i] = tval1;

		tval1 = CodecA.data.IO_buffer_tx[i];
		CodecA.data.buffer_tx[i + offset] = tval1;
	}

	CodecA.data.IO_index = 0;
}

Codec_BufferState_TypeDef codec_buffer_ready(void)
{
	//	if(CodecA.data.IO_index >= I2S_INPUT_SAMPLES_NUM)
	//	{
	//		return CODEC_BUFFER_BUSY;
	//	}
	//	else
	//	{
	//		return CODEC_BUFFER_READY;
	//	}
	return CodecA.data.IO_index >= I2S_INPUT_SAMPLES_NUM ? CODEC_BUFFER_BUSY : CODEC_BUFFER_READY;
}

#define FMAX (float)INT32_MAX
#define FMIN (float)INT32_MIN
static inline void float_to_codec(float fVal, uint16_t *Val1, uint16_t *Val2)
{
	//Flating number cast to signed int might lead to overflow.
	//Adding max/min hard limits here will ensure no undefined values
	//For to make sound better - add limiting compression in procesing part.
	float _fVal = fVal > FMAX ? fVal = FMAX : fVal < FMIN ? FMIN
														  : fVal;

	fVal = _fVal;
	signed int sVal = (signed int)(fVal);
	uint32_t temp;
	temp = (uint32_t)(sVal) >> 16;
	temp = temp & 0x0000FFFF;

	*Val1 = (uint16_t)temp;
	temp = (uint32_t)(sVal)&0x0000FF00;
	*Val2 = (uint16_t)temp;
}

static inline float codec_to_float(uint16_t Val1, uint16_t Val2)
{
	uint32_t temp;

	temp = (uint32_t)Val1;
	temp = temp << 16;
	temp &= 0xFFFF0000;
	temp = temp + ((uint32_t)Val2 & 0x0000FF00);
	signed int s_temp = (signed int)temp;
	return (float)(s_temp);
}

static inline void Codec_Callback(void)
{
	//	{
	CodecA.data.IO_state = BUFFER_READY;
	codec_flush_buffers();
	//	}
}

void CS4271_TxRxCplt_Callback(void)
{

	CodecA.data.DMA_state = BUFFER_OFFSET_FULL;
	Codec_Callback();
}

void CS4271_TxRxHalfCplt_Callback(void)
{
	CodecA.data.DMA_state = BUFFER_OFFSET_HALF;
	Codec_Callback();
}
