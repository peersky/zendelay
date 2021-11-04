/*
 * OD_Outs.c
 *
 *  Created on: 25 Oct 2018
 *      Author: Tim
 */

#include "od.h"

void OD_ON(OD_Outs_TypeDef Output)
{
	switch (Output)
	{
	case OD0:
		//		bsp_debug("%s\r\n","OD0 set to 1");
		OD0_PORT->BSRR = OD0_PIN;
		break;
	case OD1:
		//		bsp_debug("%s\r\n","OD1 set to 1");
		OD1_PORT->BSRR = OD1_PIN;
		break;
	case OD2:
		//		bsp_debug("%s\r\n","OD2 set to 1");
		OD2_PORT->BSRR = OD2_PIN;
		break;
	case OD3:
		//		bsp_debug("%s\r\n","OD3 set to 1");
		OD3_PORT->BSRR = OD3_PIN;
		break;
	case OD4:
		//		bsp_debug("%s\r\n","OD4 set to 1");
		OD4_PORT->BSRR = OD4_PIN;
		break;
	case OD5:
		//		bsp_debug("%s\r\n","OD5 set to 1");
		OD5_PORT->BSRR = OD5_PIN;
		break;
	case OD6:
		//		bsp_debug("%s\r\n","OD6 set to 1");
		OD6_PORT->BSRR = OD6_PIN;
		break;
	default:
		BSP_Error_Handler();
	}
}

void OD_OFF(OD_Outs_TypeDef Output)
{
	switch (Output)
	{
	case OD0:
		//		bsp_debug("%s\r\n","OD0 set to 0");
		OD0_PORT->BSRR = (OD0_PIN << 16);
		break;
	case OD1:
		//		bsp_debug("%s\r\n","OD1 set to 0");
		OD1_PORT->BSRR = (OD1_PIN << 16);
		break;
	case OD2:
		//		bsp_debug("%s\r\n","OD2 set to 0");
		OD2_PORT->BSRR = (OD2_PIN << 16);
		break;
	case OD3:
		//		bsp_debug("%s\r\n","OD3 set to 0");
		OD3_PORT->BSRR = (OD3_PIN << 16);
		break;
	case OD4:
		//		bsp_debug("%s\r\n","OD4 set to 0");
		OD4_PORT->BSRR = (OD4_PIN << 16);
		break;
	case OD5:
		//		bsp_debug("%s\r\n","OD5 set to 0");
		OD5_PORT->BSRR = (OD5_PIN << 16);
		break;
	case OD6:
		//		bsp_debug("%s\r\n","OD6 set to 0");
		OD6_PORT->BSRR = (OD6_PIN << 16);
		break;
	default:
		BSP_Error_Handler();
	}
}

void OD_Toggle(OD_Outs_TypeDef Output)
{
	switch (Output)
	{
	case OD0:
		bsp_debug("%s\r\n", "OD0 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD1:
		bsp_debug("%s\r\n", "OD1 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD2:
		bsp_debug("%s\r\n", "OD2 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD3:
		bsp_debug("%s\r\n", "OD3 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD4:
		bsp_debug("%s\r\n", "OD4 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD5:
		bsp_debug("%s\r\n", "OD5 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	case OD6:
		bsp_debug("%s\r\n", "OD6 toggled");
		HAL_GPIO_TogglePin(OD0_PORT, OD0_PIN);
		break;
	default:
		BSP_Error_Handler();
	}
}

void OD_Init_all(void)
{
	GPIO_TypeDef *GPIOX;
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;

	for (OD_Outs_TypeDef i = OD0; i < OD_NUM; i++)
	{
		switch (i)
		{
		case OD0:
			bsp_debug("%s\r\n", "OD0 init");
			GPIO_InitStruct.Pin = OD0_PIN;
			GPIOX = OD0_PORT;
			break;
		case OD1:
			bsp_debug("%s\r\n", "OD1 init");
			GPIO_InitStruct.Pin = OD1_PIN;
			GPIOX = OD1_PORT;
			break;
		case OD2:
			bsp_debug("%s\r\n", "OD2 init");
			GPIO_InitStruct.Pin = OD2_PIN;
			GPIOX = OD2_PORT;
			break;
		case OD3:
			bsp_debug("%s\r\n", "OD3 init");
			GPIO_InitStruct.Pin = OD3_PIN;
			GPIOX = OD3_PORT;
			break;
		case OD4:
			bsp_debug("%s\r\n", "OD4 init");
			GPIO_InitStruct.Pin = OD4_PIN;
			GPIOX = OD4_PORT;
			break;
		case OD5:
			bsp_debug("%s\r\n", "OD5 init");
			GPIO_InitStruct.Pin = OD5_PIN;
			GPIOX = OD5_PORT;
			break;
		case OD6:
			bsp_debug("%s\r\n", "OD6 init");
			GPIO_InitStruct.Pin = OD6_PIN;
			GPIOX = OD6_PORT;
			break;
		default:
			BSP_Error_Handler();
		}

		switch ((uint32_t)GPIOX)
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
		HAL_GPIO_Init(GPIOX, &GPIO_InitStruct);
	}
}

void OD_All_ON(void)
{
	for (OD_Outs_TypeDef i = OD0; i < OD_NUM; i++)
	{
		OD_ON(i);
	}
}
void OD_All_OFF(void)
{
	for (OD_Outs_TypeDef i = OD0; i < OD_NUM; i++)
	{
		OD_OFF(i);
	}
}

void OD_All_Toggle(void)
{
	for (OD_Outs_TypeDef i = OD0; i < OD_NUM; i++)
	{
		OD_Toggle(i);
	}
}

void OD_blink_blocking(uint32_t speed, uint8_t repeats)
{
	for (int i = 0; i < repeats; i++)
	{
		OD_All_ON();
		HAL_Delay(speed / 2);
		OD_All_OFF();
		HAL_Delay(speed / 2);
	}
}
