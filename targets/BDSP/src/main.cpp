#include <iostream>
#include "stm32f4xx_hal.h"
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO
#include "stdint.h"
// #include <string>
#define USE_BDSP
// #include "../../../src/App.h"
#include <errno.h>

using namespace std;
static void SystemClock_Config(void);
#define I2S_SAMPLING_FREQ I2S_AUDIOFREQ_48K
void delay_1ms(uint32_t count);
// extern void initialise_monitor_handles(void);
int custom_write(int file, char *ptr, int len);
int main()
{

	HAL_Init();
	SystemClock_Config();
	SystemCoreClockUpdate();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	static int i = 0;
	while (1)
	{
		i++;
		printf(i % 2 == 0 ? "tick!\n" : "tack!\n");
		fflush(stdout);
		HAL_Delay(1000);
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}

volatile static uint32_t delay = 0;
void delay_1ms(uint32_t count)
{
	delay = count;

	while (0U != delay)
	{
		delay--;
	}
}

static void SystemClock_Config(void)
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

//overwrite printf() output to send via ITM (SWO)
extern "C" int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		//__io_putchar(*ptr++);
		ITM_SendChar(*ptr++);
	}
	return len;
}
