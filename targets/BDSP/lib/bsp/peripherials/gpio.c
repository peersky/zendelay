/*
 * gpio.c
 *
 *  Created on: 30 Oct 2018
 *      Author: Tim
 */

#include "gpio.h"

GPIO_BSP_TypeDef _IO_List[NUM_IO_ENUM] =
	{
		//	state,q, pin,	 port,		mode,		stamp,	irq,	prio,		subpiro,		is inited,	debounce	debounce time
		{OFF, 0, IO0_PIN, IO0_PORT, IO_IS_INPUT, 0, IO0_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO1_PIN, IO1_PORT, IO_IS_INPUT, 0, IO1_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO2_PIN, IO2_PORT, IO_IS_INPUT, 0, IO2_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO3_PIN, IO3_PORT, IO_IS_INPUT, 0, IO3_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO4_PIN, IO4_PORT, IO_IS_INPUT, 0, IO4_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO5_PIN, IO5_PORT, IO_IS_INPUT, 0, IO5_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO6_PIN, IO6_PORT, IO_IS_INPUT, 0, IO6_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO7_PIN, IO7_PORT, IO_IS_INPUT, 0, IO7_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO8_PIN, IO8_PORT, IO_IS_INPUT, 0, IO8_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO9_PIN, IO9_PORT, IO_IS_INPUT, 0, IO9_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO10_PIN, IO10_PORT, IO_IS_INPUT, 0, IO10_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO11_PIN, IO11_PORT, IO_IS_INPUT, 0, IO11_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO12_PIN, IO12_PORT, IO_IS_INPUT, 0, IO12_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO13_PIN, IO13_PORT, IO_IS_INPUT, 0, IO13_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO14_PIN, IO14_PORT, IO_IS_INPUT, 0, IO14_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0},
		{OFF, 0, IO15_PIN, IO15_PORT, IO_IS_INPUT, 0, IO15_IRQ, IO_NVIC_PRIO, IO_NVIC_SUBPRIO, IO_DISABLED, 0, 0}};

void GPIO_Clock_Check(GPIO_TypeDef *GPIOX)
{
	intptr_t INT_GPIOX = (intptr_t)GPIOX;
	switch (INT_GPIOX)
	{
	case (intptr_t)GPIOA:
		if (!__HAL_RCC_GPIOA_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOA CLK..");
			__HAL_RCC_GPIOA_CLK_ENABLE();
		}
		break;
	case (intptr_t)GPIOB:
		if (!__HAL_RCC_GPIOB_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOB CLK..");
			__HAL_RCC_GPIOB_CLK_ENABLE();
		}

		break;
	case (intptr_t)GPIOC:
		if (!__HAL_RCC_GPIOC_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOC CLK..");
			__HAL_RCC_GPIOC_CLK_ENABLE();
		}
		break;
	case (intptr_t)GPIOD:
		if (!__HAL_RCC_GPIOD_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOD CLK..");
			__HAL_RCC_GPIOD_CLK_ENABLE();
		}
		break;
	case (intptr_t)GPIOF:
		if (!__HAL_RCC_GPIOF_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOF CLK..");
			__HAL_RCC_GPIOF_CLK_ENABLE();
		}
		break;
	case (intptr_t)GPIOG:
		if (!__HAL_RCC_GPIOG_IS_CLK_ENABLED())
		{
			bsp_debug("%s\r\n", "Enabling GPIOG CLK..");
			__HAL_RCC_GPIOG_CLK_ENABLE();
		}
		break;
	}
}
void IO_configure(BSP_GPIO_InitTypeDef *ios, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		assert_param(((ios[i].mode == IO_IS_INPUT) || (ios[i].mode == IO_IS_OUTPUT) || (ios[i].mode == IO_IS_IT)));

		_IO_List[ios[i].IO_n].Mode = ios[i].mode;
		_IO_List[ios[i].IO_n].isInit = IO_ENABLED;
		_IO_List[ios[i].IO_n].debounce_time = ios[i].debounce_time;
	}
}

void IO_InitAll(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	for (IO_ENUM_TypeDef i = IO0_ENUM; i < NUM_IO_ENUM; i++)
	{
		if (_IO_List[i].isInit == IO_ENABLED)
		{
			GPIO_Clock_Check(_IO_List[i].GPIOx);
			GPIO_InitStruct.Pin = _IO_List[i].pin;
			GPIO_InitStruct.Mode = _IO_List[i].Mode;
			if (_IO_List[i].Mode != IO_IS_OUTPUT)
			{
				GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			}
			else
			{
				GPIO_InitStruct.Pull = GPIO_NOPULL;
			}
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			GPIO_InitStruct.Alternate = 0;
			HAL_GPIO_Init(_IO_List[i].GPIOx, &GPIO_InitStruct);

			HAL_Delay(100);

			if (HAL_GPIO_ReadPin(_IO_List[i].GPIOx, _IO_List[i].pin))
			{
				_IO_List[i].state = ON;
			}
			else
			{
				_IO_List[i].state = OFF;
			}

			if (_IO_List[i].Mode == (IO_IS_IT))
			{
				HAL_NVIC_SetPriority(_IO_List[i].IRQn, _IO_List[i].NVIC_Prio, _IO_List[i].NVIC_SubPrio);
				HAL_NVIC_EnableIRQ(_IO_List[i].IRQn);
			}
		}
	}
	//
	//		GPIO_Clock_Check(GPIOG);
	//		GPIO_InitStruct.Pin = GPIO_PIN_3;
	//		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING|GPIO_MODE_IT_FALLING|GPIO_MODE_INPUT;
	//		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	//		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	//		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	//		HAL_NVIC_SetPriority(EXTI3_IRQn, 10, 0);
	//		HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void IO_IT(IO_ENUM_TypeDef num, IO_States Current_state)
{
	//	debug_print("%s\t%d\n","PB_IT State:",Current_state);
	if (Current_state == ON)
	{
		_IO_List[num].timestamp = HAL_GetTick();
	}
	_IO_List[num].state = Current_state;
	IO_IT_Callback(num, Current_state);
}

IO_States IO_Read_State(IO_ENUM_TypeDef num)
{
	uint32_t current_time = HAL_GetTick();
	uint32_t timedif = current_time - _IO_List[num].timestamp;
	if (_IO_List[num].state == ON)
	{
		if (timedif > 1000)
		{
			_IO_List[num].state = LONG_ON;
		}
	}
	return _IO_List[num].state;
}

void IO_Update_State(IO_ENUM_TypeDef num, IO_States New_state)
{
	_IO_List[num].state = New_state;
}

static GPIO_PinState prevstates[NUM_IO_ENUM];
IO_States IO_Read_Pin(IO_ENUM_TypeDef num)
{
	uint32_t current_time = HAL_GetTick();
	GPIO_PinState check = HAL_GPIO_ReadPin(_IO_List[num].GPIOx, _IO_List[num].pin);

	if (check != prevstates[num])
	{

		__IO uint32_t checkdif = current_time - _IO_List[num].debounce;
		if (checkdif > _IO_List[num].debounce_time)
		{
			prevstates[num] = check;
			_IO_List[num].debounce = current_time;

			if (HAL_GPIO_ReadPin(_IO_List[num].GPIOx, _IO_List[num].pin))
			{
				_IO_List[num].timestamp = current_time;
				_IO_List[num].state = ON;
			}
			else
			{
				_IO_List[num].state = OFF;
			}
		}
	}
	else
	{

		if ((_IO_List[num].state == ON))
		{
			uint32_t timedif = current_time - _IO_List[num].timestamp;
			if (timedif > 1000)
			{
				_IO_List[num].state = LONG_ON;
				return _IO_List[num].state;
			}
		}
	}

	return _IO_List[num].state;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	for (IO_ENUM_TypeDef i = IO0_ENUM; i < NUM_IO_ENUM; i++)
	{

		if ((_IO_List[i].Mode == IO_IS_IT) && (_IO_List[i].pin == GPIO_Pin) && (_IO_List[i].isInit == IO_ENABLED))
		{
			__IO uint32_t timedif = HAL_GetTick() - _IO_List[i].debounce;
			if (HAL_GPIO_ReadPin(_IO_List[i].GPIOx, GPIO_Pin))
			{
				_IO_List[i].state = ON;
			}
			else
			{
				_IO_List[i].state = OFF;
			}

			if (timedif > _IO_List[i].debounce_time)
			{
				bsp_dbg_print("exti callback. Bounce OK");
				_IO_List[i].debounce = HAL_GetTick();
				IO_IT(i, _IO_List[i].state);
				return;
			}
		}
	}

	//This might occur if contact is still bouncing.

	//	BSP_Error_Handler();
}

void EXTI15_10_IRQHandler(void)
{
	//	bsp_dbg_print("exti15_10");
	if (EXTI->PR & (1 << 10))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	if (EXTI->PR & (1 << 11))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
	if (EXTI->PR & (1 << 12))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	if (EXTI->PR & (1 << 13))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	if (EXTI->PR & (1 << 14))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
	if (EXTI->PR & (1 << 15))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}

void EXTI9_5_IRQHandler(void)
{
	//	bsp_dbg_print("exti9_5");
	if (EXTI->PR & (1 << 5))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	if (EXTI->PR & (1 << 6))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
	if (EXTI->PR & (1 << 7))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
	if (EXTI->PR & (1 << 8))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
	if (EXTI->PR & (1 << 9))
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

void EXTI4_IRQHandler(void)
{
	//	debug_print("%s\n","EXTI1");
	//	bsp_dbg_print("exti4");
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void EXTI3_IRQHandler(void)
{
	//	bsp_dbg_print("exti3");
	//	debug_print("%s\n","EXTI1");
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXTI2_IRQHandler(void)
{
	//	bsp_dbg_print("exti2");
	//	debug_print("%s\n","EXTI1");
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI0_IRQHandler(void)
{
	//	debug_print("%s\n","EXTI0");
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

__weak void IO_IT_Callback(IO_ENUM_TypeDef num, IO_States Current_state)
{
	UNUSED(num);
}
