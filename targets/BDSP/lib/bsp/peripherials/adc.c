/*
 * adc.c
 *
 *  Created on: 26 Oct 2018
 *      Author: Tim
 */

#include "adc.h"
static void periph_init(void);
inline static float absolute_diff(float val1, float val2);
inline static float ADC_Filter(float Current, float New, float c);
static ADC_HandleTypeDef hadc1;
static DMA_HandleTypeDef hdma_adc1;
static uint16_t adc_raw_vals[ADC_NUM];
static ADC_StructTypedef *pADC[ADC_NUM];
static uint32_t nbr_of_conversions = 0;

static ADC_StructTypedef ADC_List[ADC_NUM] = {
	//Name;	 Port,			Pin,			ADC_CH			ADCx		CH_RANK		isOn
	{CV_IN_0_PORT, CV_IN_0_PIN, CV_IN_0_CH, ADC1, 0, 0},
	{CV_IN_1_PORT, CV_IN_1_PIN, CV_IN_1_CH, ADC1, 0, 0},
	{CV_IN_2_PORT, CV_IN_2_PIN, CV_IN_2_CH, ADC1, 0, 0},
	{CV_IN_3_PORT, CV_IN_3_PIN, CV_IN_3_CH, ADC1, 0, 0},
	{EG_IN_0_PORT, EG_IN_0_PIN, EG_IN_0_CH, ADC1, 0, 0},
	{EG_IN_1_PORT, EG_IN_1_PIN, EG_IN_1_CH, ADC1, 0, 0},
	{EG_IN_2_PORT, EG_IN_2_PIN, EG_IN_2_CH, ADC1, 0, 0},
	{EG_IN_3_PORT, EG_IN_3_PIN, EG_IN_3_CH, ADC1, 0, 0},
	{ADC2_PORT, ADC2_PIN, ADC2_CHAN, ADC1, 0, 0},
	{ADC3_PORT, ADC3_PIN, ADC3_CHAN, ADC1, 0, 0},
	{ADC6_PORT, ADC6_PIN, ADC6_CHAN, ADC1, 0, 0},
	{ADC7_PORT, ADC7_PIN, ADC7_CHAN, ADC1, 0, 0},
	{ADC8_PORT, ADC8_PIN, ADC8_CHAN, ADC1, 0, 0},
};

void ADC_Prepare(BSP_ADC_InitTypeDef *adcs, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		nbr_of_conversions++;
		ADC_List[adcs[i].channel].isOn = 1;
		ADC_List[adcs[i].channel].CH_RANK = nbr_of_conversions;
		ADC_List[adcs[i].channel].LPF_Coef = adcs[i].LPF_Coef;
		ADC_List[adcs[i].channel].Track_For = adcs[i].track_for;
		ADC_List[adcs[i].channel].Treshold = adcs[i].Treshold;
		pADC[nbr_of_conversions - 1] = &ADC_List[adcs[i].channel];
	}

	// return nbr_of_conversions - 1;
}

int ADC_ReturnRank(ADC_In_TypeDef channel)
{
	return ADC_List[channel].CH_RANK;
}
void ADC_Init(void)
{
	ADC_ChannelConfTypeDef sConfig;

	periph_init();

	for (ADC_In_TypeDef i = CV_IN_0; i < ADC_NUM; i++)
	{

		if (ADC_List[i].isOn)
		{
			/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
			 */
			sConfig.Channel = ADC_List[i].ADC_CH;
			sConfig.Rank = ADC_List[i].CH_RANK;
			sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
			if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
			{
				BSP_Error_Handler();
			}
		}

		adc_raw_vals[i] = 0xFFF;
	}
}

static void periph_init(void)
{

	__ADC1_CLK_ENABLE();

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
		 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = nbr_of_conversions;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		BSP_Error_Handler();
	}
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if (hadc->Instance == ADC1)
	{

		__HAL_RCC_ADC1_CLK_ENABLE();
		__HAL_RCC_DMA2_CLK_ENABLE();

		//		HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
		//		HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 10, 0);

		HAL_NVIC_SetPriority(ADC_DMA_IRQ, 3, 0);
		HAL_NVIC_EnableIRQ(ADC_DMA_IRQ);

		for (int i = 0; i < ADC_NUM; i++)
		{
			switch ((uint32_t)ADC_List[i].GPIOx)
			{
			case (uint32_t)GPIOA:
				if (!__HAL_RCC_GPIOA_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOA CLK..");
					__HAL_RCC_GPIOA_CLK_ENABLE();
				}
				break;
			case (uint32_t)GPIOB:
				if (!__HAL_RCC_GPIOB_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOB CLK..");
					__HAL_RCC_GPIOB_CLK_ENABLE();
				}

				break;
			case (uint32_t)GPIOC:
				if (!__HAL_RCC_GPIOC_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOC CLK..");
					__HAL_RCC_GPIOC_CLK_ENABLE();
				}
				break;
			case (uint32_t)GPIOD:
				if (!__HAL_RCC_GPIOD_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOD CLK..");
					__HAL_RCC_GPIOD_CLK_ENABLE();
				}
				break;
			case (uint32_t)GPIOF:
				if (!__HAL_RCC_GPIOF_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOF CLK..");
					__HAL_RCC_GPIOF_CLK_ENABLE();
				}
				break;
			case (uint32_t)GPIOG:
				if (!__HAL_RCC_GPIOG_IS_CLK_ENABLED())
				{
					bsp_debug("%s\r\n", "Enabling GPIOG CLK..");
					__HAL_RCC_GPIOG_CLK_ENABLE();
				}
				break;
			default:
				BSP_Error_Handler();
			}

			GPIO_InitStruct.Pin = ADC_List[i].Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			//			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
			HAL_GPIO_Init(ADC_List[i].GPIOx, &GPIO_InitStruct);
		}

		hdma_adc1.Instance = ADC_DMA_INSTANCE;
		hdma_adc1.Init.Channel = DMA_CHANNEL_0;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode = DMA_CIRCULAR;
		hdma_adc1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
		hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;
		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{
			BSP_Error_Handler();
		}

		__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);
		//		PWR->CR |= PWR_CR_ADCDC1;
	}
}

void ADC_Val_Update(float *adc)
{
	static uint32_t i = 0;
	//	signed int filter[4];
	static float filter[ADC_NUM];
	static float filter_prev[ADC_NUM];
	static uint32_t counter[ADC_NUM];

	//	i++;
	//	if (i>=KNOBS_NUM){i=0;}
	for (i = 0; i < nbr_of_conversions; i++)
	{
		filter[i] = ADC_Filter(filter[i], (float)adc_raw_vals[i], pADC[i]->LPF_Coef);

		if (counter[i] != 0)
		{
			counter[i]--;
			adc[i] = filter[i];
		}
		else if (absolute_diff(filter[i], filter_prev[i]) > pADC[i]->Treshold)
		{
			{
				filter_prev[i] = filter[i];
				counter[i] = pADC[i]->Track_For;
				//				counter[i]=0;
			}
		}
	}
}

inline static float absolute_diff(float val1, float val2)
{
	if (val1 > val2)
	{
		return val1 - val2;
	}
	else
	{
		return val2 - val1;
	}
}

inline static float ADC_Filter(float Current, float New, float c)
{
	return (Current * (1.0f - c)) + (New * c);
}

void ADC_start(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_raw_vals, nbr_of_conversions);
}

void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(hadc1.DMA_Handle);
}

void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc1);
}

float Knobs_get_multiplier(uint16_t KnobVal)
{
	float ret; //
	if (KnobVal < 2400)
	{
		ret = 1.0f;
	}
	else if (KnobVal < 2600)
	{
		ret = 1.5f;
	}
	else if (KnobVal < 3100)
	{
		ret = 2.0f;
	}
	else if (KnobVal < 3200)
	{
		ret = 3.0f;
	}
	else if (KnobVal < 3700)
	{
		ret = 4.0f;
	}
	else if (KnobVal < 3980)
	{
		ret = 6.0f;
	}
	else
	{
		ret = 8.0f;
	}
	return ret;
}

float Knobs_get_divider(uint16_t KnobVal)
{
	float ret; //
	if (KnobVal > 1850)
	{
		ret = 1.0f;
	}
	else if (KnobVal > 1550)
	{
		ret = 1.5f;
	}
	else if (KnobVal > 1130)
	{
		ret = 2.0f;
	}
	else if (KnobVal > 918)
	{
		ret = 3.0f;
	}
	else if (KnobVal > 470)
	{
		ret = 4.0f;
	}
	else if (KnobVal > 230)
	{
		ret = 6.0f;
	}
	else
	{
		ret = 8.0f;
	}

	return ret;
}
