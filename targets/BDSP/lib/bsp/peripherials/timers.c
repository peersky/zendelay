/*
 * timers.c
 *
 *  Created on: 13 ????. 2018 ?.
 *      Author: Tim
 */

#include "timers.h"

TIM_HandleTypeDef TIM2_handler;



void TIM2_init(void)
{
	//uint16_t uwPrescalerValue = 0;

	//uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;

	TIM2_handler.Instance               = TIM2;
	TIM2_handler.Init.Prescaler         = 30;
	TIM2_handler.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TIM2_handler.Init.Period            = 100;
	TIM2_handler.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	//TIM2_handler.Init.RepetitionCounter = ;
	//TIM2_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	HAL_TIM_Base_Init(&TIM2_handler);
}

void TIM2_start(void)
{
	HAL_TIM_Base_Start_IT(&TIM2_handler);
}

__weak void TIM_Callback(TIM_HandleTypeDef *htim)
{


}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	TIM_Callback(htim);
}
