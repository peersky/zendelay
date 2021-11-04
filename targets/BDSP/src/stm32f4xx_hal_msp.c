
/**
 ******************************************************************************
 * @file    stm32f4xx_hal_msp_template.c
 * @author  MCD Application Team
 * @version V1.7.1
 * @date    14-April-2017
 * @brief   This file contains the HAL System and Peripheral (PPP) MSP initialization
 *          and de-initialization functions.
 *          It should be copied to the application folder and renamed into 'stm32f4xx_hal_msp.c'.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
// #include "..bsp/BDSP_Conf.h"
#include "stm32f4xx_hal.h"
#include "../bsp/debug.h"
#include "../bsp/config.h"
#include "../bsp/peripherials/gpio.h"

extern DMA_HandleTypeDef *hdma_spi2_tx;
extern DMA_HandleTypeDef *hdma_i2s2_ext_rx;

//#include <adc.h>
//#include <i2s.h>
//#include <sdram.h>
//#include <delay_midi.h>
/** @addtogroup STM32F4xx_HAL_Driver
 * @{
 */

/** @defgroup HAL_MSP HAL MSP
 * @brief HAL MSP module.
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions HAL MSP Private Functions
 * @{
 */

/**
 * @brief  Initializes the Global MSP.
 * @note   This function is called from HAL_Init() function to perform system
 *         level initialization (GPIOs, clock, DMA, interrupt).
 * @retval None
 */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	/* BusFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	/* UsageFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	/* SVCall_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 11, 0);

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

/**
 * @brief  DeInitializes the Global MSP.
 * @note   This functiona is called from HAL_DeInit() function to perform system
 *         level de-initialization (GPIOs, clock, DMA, interrupt).
 * @retval None
 */
void HAL_MspDeInit(void)
{
}

/**
 * @brief  Initializes the PPP MSP.
 * @note   This functiona is called from HAL_PPP_Init() function to perform
 *         peripheral(PPP) system level initialization (GPIOs, clock, DMA, interrupt)
 * @retval None
 */
//void HAL_PPP_MspInit(void)
//{
//
//}
//
///**
//  * @brief  DeInitializes the PPP MSP.
//  * @note   This functiona is called from HAL_PPP_DeInit() function to perform
//  *         peripheral(PPP) system level de-initialization (GPIOs, clock, DMA, interrupt)
//  * @retval None
//  */
//void HAL_PPP_MspDeInit(void)
//{
//
//}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if (hi2c->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */

		/**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
		 */
		GPIO_InitStruct.Pin = I2C_SCL_PIN | I2C_SDA_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(I2C_PORT, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

	if (hi2c->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspDeInit 0 */

		/* USER CODE END I2C1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_I2C1_CLK_DISABLE();

		/**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
		 */
		HAL_GPIO_DeInit(I2C_PORT, I2C_SDA_PIN | I2C_SCL_PIN);

		/* USER CODE BEGIN I2C1_MspDeInit 1 */

		/* USER CODE END I2C1_MspDeInit 1 */
	}
}

static uint32_t FMC_Initialized = 0;

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram)
{
	/* USER CODE BEGIN FMC_MspInit 0 */

	/* USER CODE END FMC_MspInit 0 */
	if (FMC_Initialized)
	{
		return;
	}
	FMC_Initialized = 1;
	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();

	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__HAL_RCC_FMC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/** FMC GPIO Configuration
    PF0   ------> FMC_A0
    PF1   ------> FMC_A1
    PF2   ------> FMC_A2
    PF3   ------> FMC_A3
    PF4   ------> FMC_A4
    PF5   ------> FMC_A5
    PC0   ------> FMC_SDNWE
    PC2   ------> FMC_SDNE0
    PC3   ------> FMC_SDCKE0
    PF11   ------> FMC_SDNRAS
    PF12   ------> FMC_A6
    PF13   ------> FMC_A7
    PF14   ------> FMC_A8
    PF15   ------> FMC_A9
    PG0   ------> FMC_A10
    PG1   ------> FMC_A11
    PE7   ------> FMC_D4
    PE8   ------> FMC_D5
    PE9   ------> FMC_D6
    PE10   ------> FMC_D7
    PE11   ------> FMC_D8
    PE12   ------> FMC_D9
    PE13   ------> FMC_D10
    PE14   ------> FMC_D11
    PE15   ------> FMC_D12
    PD8   ------> FMC_D13
    PD9   ------> FMC_D14
    PD10   ------> FMC_D15
    PD14   ------> FMC_D0
    PD15   ------> FMC_D1
    PG2   ------> FMC_A12
    PG4   ------> FMC_BA0
    PG5   ------> FMC_BA1
    PG8   ------> FMC_SDCLK
    PD0   ------> FMC_D2
    PD1   ------> FMC_D3
    PG15   ------> FMC_SDNCAS
    PE0   ------> FMC_NBL0
    PE1   ------> FMC_NBL1
    */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	/* USER CODE BEGIN FMC_MspInit 1 */

	/* USER CODE END FMC_MspInit 1 */
}
//
//void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram){
//  /* USER CODE BEGIN SDRAM_MspInit 0 */
//
//  /* USER CODE END SDRAM_MspInit 0 */
//  HAL_FMC_MspInit();
//  /* USER CODE BEGIN SDRAM_MspInit 1 */
//
//  /* USER CODE END SDRAM_MspInit 1 */
//}
//
//static uint32_t FMC_DeInitialized = 0;
//
//static void HAL_FMC_MspDeInit(void){
//  /* USER CODE BEGIN FMC_MspDeInit 0 */
//
//  /* USER CODE END FMC_MspDeInit 0 */
//  if (FMC_DeInitialized) {
//    return;
//  }
//  FMC_DeInitialized = 1;
//  /* Peripheral clock enable */
//  __HAL_RCC_FMC_CLK_DISABLE();
//
//  SDRAM_msp_fmc_deinit();
//  /* USER CODE BEGIN FMC_MspDeInit 1 */
//
//  /* USER CODE END FMC_MspDeInit 1 */
//}
//
//void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram){
//  /* USER CODE BEGIN SDRAM_MspDeInit 0 */
//
//  /* USER CODE END SDRAM_MspDeInit 0 */
//  HAL_FMC_MspDeInit();
//  /* USER CODE BEGIN SDRAM_MspDeInit 1 */
//
//  /* USER CODE END SDRAM_MspDeInit 1 */
//}
//
void HAL_I2S_MspInit(I2S_HandleTypeDef *hi2s)
{
	//  I2S_PCM51XX_msp_init(hi2s);
	//  I2S_PCM186X_msp_init(hi2s);
	//	I2S_c4271_MspInit(hi2s);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_Clock_Check(CODEC_RST_PORT);
	GPIO_InitStruct.Pin = CODEC_RST_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(CODEC_RST_PORT, &GPIO_InitStruct);

	/* Peripheral clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();

	/**I2S3 GPIO Configuration
		    PA4     ------> I2S3_WS
		    PC10     ------> I2S3_CK
		    PC11     ------> I2S3_ext_SD
		    PC12     ------> I2S3_SD
	 */
	GPIO_Clock_Check(GPIOB);
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF6_I2S2ext;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_Clock_Check(GPIOC);
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* I2S3 DMA Init */
	/* I2S3_EXT_RX Init */
	hdma_i2s2_ext_rx->Instance = DMA1_Stream3;
	hdma_i2s2_ext_rx->Init.Channel = DMA_CHANNEL_3;
	hdma_i2s2_ext_rx->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_i2s2_ext_rx->Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_i2s2_ext_rx->Init.MemInc = DMA_MINC_ENABLE;
	hdma_i2s2_ext_rx->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_i2s2_ext_rx->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma_i2s2_ext_rx->Init.Mode = DMA_CIRCULAR;
	hdma_i2s2_ext_rx->Init.Priority = DMA_PRIORITY_HIGH;
	hdma_i2s2_ext_rx->Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	if (HAL_DMA_Init(hdma_i2s2_ext_rx) != HAL_OK)
	{
		BSP_Error_Handler();
	}

	__HAL_DMA_DISABLE_IT(hdma_i2s2_ext_rx, DMA_IT_HT); //?? Do we need it?
	__HAL_DMA_DISABLE_IT(hdma_i2s2_ext_rx, DMA_IT_TC);

	__HAL_LINKDMA(hi2s, hdmarx, *hdma_i2s2_ext_rx);

	/* SPI3_TX Init */
	hdma_spi2_tx->Instance = DMA1_Stream4;
	hdma_spi2_tx->Init.Channel = DMA_CHANNEL_0;
	hdma_spi2_tx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi2_tx->Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_tx->Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_tx->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_spi2_tx->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma_spi2_tx->Init.Mode = DMA_CIRCULAR;
	hdma_spi2_tx->Init.Priority = DMA_PRIORITY_HIGH;
	hdma_spi2_tx->Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	if (HAL_DMA_Init(hdma_spi2_tx) != HAL_OK)
	{
		BSP_Error_Handler();
	}

	__HAL_DMA_DISABLE_IT(hdma_spi2_tx, DMA_IT_HT); //do we need these enables?
	__HAL_DMA_DISABLE_IT(hdma_spi2_tx, DMA_IT_TC);

	__HAL_LINKDMA(hi2s, hdmatx, *hdma_spi2_tx);
}

//
//void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
//{
//  ADC_msp_init(hadc);
//}
//
//void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
//{
//  ADC_msp_deinit(hadc);
//}
//
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();

		HAL_NVIC_SetPriority(TIM2_IRQn, 5, 1);
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
	}
	if (htim->Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();

		HAL_NVIC_SetPriority(TIM4_IRQn, 6, 0);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
	}
}
//
//
//void HAL_UART_MspInit(UART_HandleTypeDef* huart)
//{
//	MIDI_MSP_Init(huart);
//}
//
//void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
//{
//	MIDI_MSP_DeInit(huart);
//}

extern DMA_HandleTypeDef hdma_sai1_a;

extern DMA_HandleTypeDef hdma_sai1_b;

static uint32_t SAI1_client = 0;

void HAL_SAI_MspInit(SAI_HandleTypeDef *hsai)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	/* SAI1 */
	if (hsai->Instance == SAI1_Block_A)
	{
		/* Peripheral clock enable */
		if (SAI1_client == 0)
		{
			__HAL_RCC_SAI1_CLK_ENABLE();
		}
		SAI1_client++;

		/**SAI1_A_Block_A GPIO Configuration
    PE2     ------> SAI1_MCLK_A
    PE4     ------> SAI1_FS_A
    PE5     ------> SAI1_SCK_A
    PE6     ------> SAI1_SD_A
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Peripheral DMA init*/

		hdma_sai1_a.Instance = DMA2_Stream1;
		hdma_sai1_a.Init.Channel = DMA_CHANNEL_0;
		hdma_sai1_a.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_sai1_a.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sai1_a.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sai1_a.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sai1_a.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sai1_a.Init.Mode = DMA_NORMAL;
		hdma_sai1_a.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sai1_a.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_sai1_a) != HAL_OK)
		{
			BSP_Error_Handler();
		}

		/* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
		__HAL_LINKDMA(hsai, hdmarx, hdma_sai1_a);

		__HAL_LINKDMA(hsai, hdmatx, hdma_sai1_a);
	}
	if (hsai->Instance == SAI1_Block_B)
	{
		/* Peripheral clock enable */
		if (SAI1_client == 0)
		{
			__HAL_RCC_SAI1_CLK_ENABLE();
		}
		SAI1_client++;

		/**SAI1_B_Block_B GPIO Configuration
    PE3     ------> SAI1_SD_B
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF6_SAI1;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* Peripheral DMA init*/

		hdma_sai1_b.Instance = DMA2_Stream5;
		hdma_sai1_b.Init.Channel = DMA_CHANNEL_0;
		hdma_sai1_b.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_sai1_b.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sai1_b.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sai1_b.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sai1_b.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sai1_b.Init.Mode = DMA_NORMAL;
		hdma_sai1_b.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sai1_b.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_sai1_b) != HAL_OK)
		{
			BSP_Error_Handler();
		}

		/* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one stream to perform all the requested DMAs. */
		__HAL_LINKDMA(hsai, hdmarx, hdma_sai1_b);
		__HAL_LINKDMA(hsai, hdmatx, hdma_sai1_b);
	}
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/