/*
 * codec.h
 *
 *  Created on: 30 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_CODEC_H_
#define BSP_CODEC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "config.h"
#include "components/CS4271/CS4271.h"

#define I2S_INPUT_BUFFER_SIZE I2S_INPUT_SAMPLES_PER_BUFFER
#define I2S_INPUT_SAMPLES_NUM I2S_INPUT_BUFFER_SIZE * 2

  typedef enum
  {
    IO_BUFFER_STATE_NOT_INITED = 0,
    IO_BUFFER_STATE_EMPTY,
    IO_BUFFER_STATE_REFILLING,
    IO_BUFFER_STATE_FULL,
    IO_BUFFER_STATE_OVERFLOW,
    BUFFER_READY,
    BUFFER_BUSY
  } IO_Buffer_StateTypeDef;

  typedef enum
  {
    BUFFER_OFFSET_NONE = 0,
    BUFFER_OFFSET_HALF,
    BUFFER_OFFSET_FULL
  } DMA_Buff_StateTypeDef;

  typedef enum
  {
    I2S_ERROR = 0,
    I2S_OK,
    I2S_BUSY
  } I2S_Base_TypeDef;

  typedef enum
  {
    IO_BUFFER_TYPE_RX = 0,
    IO_BUFFER_TYPE_TX
  } IO_Buffer_Type;

  //ToDo: This struct should be revised and defined as IO_buffer.c..
  typedef struct
  {
    //Size parameter means the number of 16-bit data length, HAL multiples it by itself
    uint16_t buffer_tx[I2S_INPUT_BUFFER_SIZE * 2 + I2S_INPUT_BUFFER_SIZE * 2];
    uint16_t IO_buffer_tx[I2S_INPUT_BUFFER_SIZE * 2];
    uint16_t buffer_rx[I2S_INPUT_BUFFER_SIZE * 2 + I2S_INPUT_BUFFER_SIZE * 2];
    uint16_t IO_buffer_rx[I2S_INPUT_BUFFER_SIZE * 2];
    DMA_Buff_StateTypeDef DMA_state_tx;
    __IO DMA_Buff_StateTypeDef DMA_state;
    uint32_t IO_index_tx;
    uint32_t IO_index;
    __IO IO_Buffer_StateTypeDef IO_state_tx;
    __IO IO_Buffer_StateTypeDef IO_state;
    uint16_t *sdram; //output buffer

  } Codec_Data_TypeDef;

  typedef struct Codec_i2s_Handle
  {
    I2S_HandleTypeDef i2s;
    DMA_HandleTypeDef dma_rx;
    DMA_HandleTypeDef dma_tx;
    Codec_Data_TypeDef data;

  } Codec_i2s_HandleTypeDef;

  typedef struct Codec_SAI_Handle
  {
    SAI_HandleTypeDef sai;
    DMA_HandleTypeDef dma_rx;
    DMA_HandleTypeDef dma_tx;
    Codec_Data_TypeDef data;

  } Codec_SAI_HandleTypeDef;

  typedef enum
  {
    CODEC_BUFFER_BUSY = 0,
    CODEC_BUFFER_READY
  } Codec_BufferState_TypeDef;

  typedef enum
  {
    Codec_ERROR = 0,
    Codec_OK,
    Codec_BUSY
  } Codec_Base_TypeDef;

  void Codec_configure_CodecA(void);
  void Codec_start_CodecA(void);
  void codec_flush_buffers(void);
  Codec_BufferState_TypeDef codec_buffer_ready(void);
  float CodecA_Read_Write_24b(float Data);
  void CS4271_TxRxCplt_Callback(void);
  void CS4271_TxRxHalfCplt_Callback(void);
  //int Codecs_test(uint8_t test_n);
  int Codec_Audio_Test(Codec_i2s_HandleTypeDef *Codec, uint8_t ch);
#ifdef __cplusplus
}
#endif

#endif /* BSP_CODEC_H_ */
