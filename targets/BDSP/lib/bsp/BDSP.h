/*
 * BDSP.h
 *
 *  Created on: 3 ???. 2019 ?.
 *      Author: Tim
 */

#ifndef BSP_BDSP_BDSP_H_
#define BSP_BDSP_BDSP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "debug.h"
#include "config.h"
#include "peripherials/gpio.h"
#include "peripherials/i2c.h"
#include "peripherials/adc.h"
#include "peripherials/timers.h"
#include "memory.h"
#include "codec.h"

    void BDSP_Init_SysClk(void)
    {
        RCC_OscInitTypeDef RCC_OscInitStruct;
        RCC_ClkInitTypeDef RCC_ClkInitStruct;
        RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

        /**Macro to configure SAI1BlockB clock source selection
  */
        __HAL_RCC_SAI_BLOCKBCLKSOURCE_CONFIG(SAI_CLKSOURCE_PLLI2S);

        /**Macro to configure SAI1BlockA clock source selection
  */
        __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(SAI_CLKSOURCE_PLLI2S);

        /**Configure the main internal regulator output voltage
    */
        __HAL_RCC_PWR_CLK_ENABLE();

        __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

        /**Initializes the CPU, AHB and APB busses clocks
    */
        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
        RCC_OscInitStruct.HSEState = RCC_HSE_ON;
        RCC_OscInitStruct.HSICalibrationValue = 16;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
        RCC_OscInitStruct.PLL.PLLM = 4;
        RCC_OscInitStruct.PLL.PLLN = 180;
        RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
        RCC_OscInitStruct.PLL.PLLQ = 7;
        if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        {
            //    _Error_Handler(__FILE__, __LINE__);
        }

        /**Activate the Over-Drive mode
    */
        if (HAL_PWREx_EnableOverDrive() != HAL_OK)
        {
            //    _Error_Handler(__FILE__, __LINE__);
        }

        /**Initializes the CPU, AHB and APB busses clocks
  */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

        if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
        {
            //    _Error_Handler(__FILE__, __LINE__);
        }

        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S | RCC_PERIPHCLK_SAI_PLLI2S;

        if (I2S_SAMPLING_FREQ == I2S_AUDIOFREQ_48K)
        {
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 50;
            PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
            PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
            PeriphClkInitStruct.PLLI2SDivQ = 1;
        }
        else if (I2S_SAMPLING_FREQ == I2S_AUDIOFREQ_96K)
        {
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 424;
            PeriphClkInitStruct.PLLI2S.PLLI2SR = 3;
        }
        else
        {
            // _Error_Handler(__FILE__, __LINE__);
        }
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
        {
            // _Error_Handler(__FILE__, __LINE__);
        }

        /*Configure GPIO pin : PC9 */
        __HAL_RCC_GPIOC_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        /**Configure the Systick interrupt time
  */
        HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

        /**Configure the Systick
  */
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

        /* SysTick_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

        __HAL_RCC_SYSCFG_CLK_ENABLE();
        HAL_EnableCompensationCell();
    }

    void bsp_init(BSP_GPIO_InitTypeDef *ios, size_t ios_size, BSP_ADC_InitTypeDef *adcs, size_t adcs_size)
    {
        HAL_Init();
        BDSP_Init_SysClk();
        SystemCoreClockUpdate();

        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOH_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();

        IO_configure(ios, ios_size);
        IO_InitAll();
        I2C_Init(&hi2c);
        Codec_configure_CodecA();
        OD_Init_all();
        ADC_Prepare(adcs, adcs_size);
        ADC_Init();
        TIM2_init();
    }

#ifdef __cplusplus
}
#endif

#endif /* BSP_BDSP_BDSP_H_ */
