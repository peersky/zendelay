// BUILD TARGET MACRO CAN MUST BE SET IN ORDER TO SELECT PROPER HEADERS OF TARGET PLATFORM
// JUCE PLUGIN:
//#define BUILD_TARGET_DAWPLUGIN
// Zen BDSP:
#define BUILD_TARGET_BDSP
#define BDP_DEBUG 1U
#include "../../../src/App.h"
#include "bsp.h"
#include "io_config.h"
#define I2S_SAMPLING_FREQ I2S_AUDIOFREQ_48K
void delay_1ms(uint32_t count);
using namespace std;
// extern void initialise_monitor_handles(void);
int custom_write(int file, char *ptr, int len);
int main()
{
	const int NUM_IO_INIT = 10U;
	BSP_GPIO_InitTypeDef gpiosInitArray[NUM_IO_INIT] = {
		{SYNC_IN_ENUM, IO_IS_INPUT, 0},
		{SYNC_PB_ENUM, IO_IS_INPUT, 15},
		{ADD_PB_ENUM, IO_IS_INPUT, 15},
		{ADD_IN_ENUM, IO_IS_INPUT, 35},
		{HOLD_PB_ENUM, IO_IS_INPUT, 35},
		{HOLD_IN_ENUM, IO_IS_INPUT, 5},
		{REV_PB_ENUM, IO_IS_INPUT, 35},
		{REV_IN_ENUM, IO_IS_INPUT, 5},
		{PINGPONG_PB_ENUM, IO_IS_INPUT, 35},
		{DELAY_TYPE_ENUM, IO_IS_INPUT, 35}};

	const size_t NUM_ADCS_INIT = 4U;
	BSP_ADC_InitTypeDef adcsInitArray[NUM_ADCS_INIT] = {
		{CV_FEEDBACK, CV_LPF_COEF, CV_TRACK_FOR, CV_MIN_CHANGE},
		{CV_TIME, CV_LPF_COEF, CV_TRACK_FOR, CV_MIN_CHANGE},
		{POT_FEEDBACK, KNOB_LPF_COEF, KNOB_TRACK_FOR, KNOB_MIN_CHANGE},
		{POT_TIME, KNOB_LPF_COEF, KNOB_TRACK_FOR, KNOB_MIN_CHANGE},

	};

	bsp_init(gpiosInitArray, NUM_IO_INIT, adcsInitArray, NUM_ADCS_INIT);

	static int i = 0;
	while (1)
	{
		i++;
		i = i > 100 ? 0 : i;
		// printf(i % 2 == 0 ? "tick!\n" : "tack!\n");
		for (int sk = 0; sk < i; sk++)
		{
			printf("*");
			// HAL_Delay(10);
		}
		printf("\n");
		// fflush(stdout);
		HAL_Delay(1);
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
