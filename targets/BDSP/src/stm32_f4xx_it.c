/* Includes ------------------------------------------------------------------*/
#include "stm32_f4xx_it.h"
// #include "codec.h"
//#include <adc.h>

/** @addtogroup Template
  * @{
  */
//extern TIM_HandleTypeDef TIM4_handler;
// extern TIM_HandleTypeDef TIM2_handler;
// extern DMA_HandleTypeDef *hdma_spi2_tx;
// extern DMA_HandleTypeDef *hdma_i2s2_ext_rx;
void NMI_Handler(void)
{
}
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}
void SVC_Handler(void)
{
}
void DebugMon_Handler(void)
{
}
void PendSV_Handler(void)
{
}
void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
// void TIM2_IRQHandler(void)
// {
//     HAL_TIM_IRQHandler(&TIM2_handler);
// }

// void DMA1_Stream3_IRQHandler(void)
// {
//     HAL_DMA_IRQHandler(hdma_i2s2_ext_rx);
//     //  printf("DMA1_0\n");
// }

// void DMA1_Stream4_IRQHandler(void)
// {
//     HAL_DMA_IRQHandler(hdma_spi2_tx);
//     //  printf("DMA1_5\n");
// }
//

//void TIM4_IRQHandler(void)
//{
//	static __IO uint32_t cntr=0;
//	cntr++;
//	if (cntr>=0xFFFF)
//	{
//			printf("break!");
//		cntr=0;
//	}
//  HAL_TIM_IRQHandler(&TIM4_handler);
//}
//
//
//void EXTI4_IRQHandler(void)
//{
//  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
//}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
