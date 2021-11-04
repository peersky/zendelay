
#ifndef _BSP_BDSP_CONFIG_
#define _BSP_BDSP_CONFIG_

#ifdef __cplusplus
extern "C"
{
#endif


#include "stm32f4xx_hal.h"
#include "debug.h"


#define KNOB_MIN_CHANGE				0.7f
#define KNOB_TRACK_FOR				9000
#define KNOB_LPF_COEF				1.0f/1000.0f
#define CV_LPF_COEF					1.0f/25.0f
#define CV_MIN_CHANGE				15.0f
#define CV_TRACK_FOR				250

#define ADC_DMA_IRQ					DMA2_Stream0_IRQn
#define ADC_DMA_INSTANCE			DMA2_Stream0

#define ADC0_PIN					GPIO_PIN_6
#define ADC0_PORT					GPIOA
#define ADC0_CHAN					ADC_CHANNEL_6

#define ADC1_PIN					GPIO_PIN_7
#define ADC1_PORT					GPIOA
#define ADC1_CHAN					ADC_CHANNEL_7

#define ADC2_PIN					GPIO_PIN_4
#define ADC2_PORT					GPIOA
#define ADC2_CHAN					ADC_CHANNEL_4

#define ADC3_PIN					GPIO_PIN_5
#define ADC3_PORT					GPIOA
#define ADC3_CHAN					ADC_CHANNEL_5

#define ADC4_PIN					GPIO_PIN_2
#define ADC4_PORT					GPIOA
#define ADC4_CHAN					ADC_CHANNEL_2

#define ADC5_PIN					GPIO_PIN_3
#define ADC5_PORT					GPIOA
#define ADC5_CHAN					ADC_CHANNEL_3

#define ADC6_PIN					GPIO_PIN_1
#define ADC6_PORT					GPIOA
#define ADC6_CHAN					ADC_CHANNEL_1

#define ADC7_PIN					GPIO_PIN_0
#define ADC7_PORT					GPIOA
#define ADC7_CHAN					ADC_CHANNEL_0

#define ADC8_PIN					GPIO_PIN_1
#define ADC8_PORT					GPIOC
#define ADC8_CHAN					ADC_CHANNEL_11

#define ADC9_PIN					GPIO_PIN_4
#define ADC9_PORT					GPIOC
#define ADC9_CHAN					ADC_CHANNEL_14

#define ADC10_PIN					GPIO_PIN_5
#define ADC10_PORT					GPIOC
#define ADC10_CHAN					ADC_CHANNEL_15

#define ADC11_PIN					GPIO_PIN_0
#define ADC11_PORT					GPIOB
#define ADC11_CHAN					ADC_CHANNEL_8

#define ADC12_PIN					GPIO_PIN_1
#define ADC12_PORT					GPIOB
#define ADC12_CHAN					ADC_CHANNEL_9

#define CV_IN_0_PORT				ADC12_PORT
#define CV_IN_0_PIN					ADC12_PIN
#define CV_IN_0_CH					ADC12_CHAN

#define CV_IN_1_PORT				ADC11_PORT
#define CV_IN_1_PIN					ADC11_PIN
#define CV_IN_1_CH					ADC11_CHAN

#define CV_IN_2_PORT				ADC10_PORT
#define CV_IN_2_PIN					ADC10_PIN
#define CV_IN_2_CH					ADC10_CHAN

#define CV_IN_3_PORT				ADC9_PORT
#define CV_IN_3_PIN					ADC9_PIN
#define CV_IN_3_CH					ADC9_CHAN

#define EG_IN_0_PORT				ADC4_PORT
#define EG_IN_0_PIN					ADC4_PIN
#define EG_IN_0_CH					ADC4_CHAN

#define EG_IN_1_PORT				ADC5_PORT
#define EG_IN_1_PIN					ADC5_PIN
#define EG_IN_1_CH					ADC5_CHAN

#define EG_IN_2_PORT				ADC0_PORT
#define EG_IN_2_PIN					ADC0_PIN
#define EG_IN_2_CH					ADC0_CHAN

#define EG_IN_3_PORT				ADC1_PORT
#define EG_IN_3_PIN					ADC1_PIN
#define EG_IN_3_CH					ADC1_CHAN




#define IO_NVIC_PRIO 					10
#define IO_NVIC_SUBPRIO 				0

#define IO_INT0				EXTI2_IRQn
#define IO_INT1				EXTI3_IRQn
#define IO_INT2				EXTI4_IRQn
#define IO_INT3				EXTI9_5_IRQn
#define IO_INT4				EXTI15_10_IRQn

#define IO0_PIN 			GPIO_PIN_4
#define IO0_PORT			GPIOB
#define IO0_IRQ				IO_INT2

#define IO1_PIN 			GPIO_PIN_2
#define IO1_PORT			GPIOB
#define IO1_IRQ				IO_INT0

#define IO2_PIN 			GPIO_PIN_11
#define IO2_PORT			GPIOD
#define IO2_IRQ				IO_INT4

#define IO3_PIN 			GPIO_PIN_13
#define IO3_PORT			GPIOD
#define IO3_IRQ				IO_INT4

#define IO4_PIN 			GPIO_PIN_3
#define IO4_PORT			GPIOG
#define IO4_IRQ				IO_INT1

#define IO5_PIN 			GPIO_PIN_6
#define IO5_PORT			GPIOG
#define IO5_IRQ				IO_INT3

#define IO6_PIN 			GPIO_PIN_7
#define IO6_PORT			GPIOG
#define IO6_IRQ				IO_INT3

#define IO7_PIN 			GPIO_PIN_7
#define IO7_PORT			GPIOC
#define IO7_IRQ				IO_INT3

#define IO8_PIN 			GPIO_PIN_9
#define IO8_PORT			GPIOG
#define IO8_IRQ				IO_INT3

#define IO9_PIN 			GPIO_PIN_7
#define IO9_PORT			GPIOD
#define IO9_IRQ				IO_INT3

#define IO10_PIN 			GPIO_PIN_6
#define IO10_PORT			GPIOD
#define IO10_IRQ			IO_INT3

#define IO11_PIN 			GPIO_PIN_5
#define IO11_PORT			GPIOD
#define IO11_IRQ			IO_INT3

#define IO12_PIN 			GPIO_PIN_4
#define IO12_PORT			GPIOD
#define IO12_IRQ			IO_INT2

#define IO13_PIN 			GPIO_PIN_3
#define IO13_PORT			GPIOD
#define IO13_IRQ			IO_INT1

#define IO14_PIN 			GPIO_PIN_15
#define IO14_PORT			GPIOA
#define IO14_IRQ			IO_INT4

#define IO15_PIN 			GPIO_PIN_8
#define IO15_PORT			GPIOA
#define IO15_IRQ			IO_INT3


#define I2C_SCL_PIN GPIO_PIN_8
#define I2C_SDA_PIN GPIO_PIN_7
#define I2C_PORT GPIOB


#define OD0_PIN						GPIO_PIN_6
#define OD0_PORT					GPIOB
#define OD1_PIN						GPIO_PIN_5
#define OD1_PORT					GPIOB
#define OD2_PIN						GPIO_PIN_13
#define OD2_PORT					GPIOB
#define OD3_PIN						GPIO_PIN_14
#define OD3_PORT					GPIOG
#define OD4_PIN						GPIO_PIN_13
#define OD4_PORT					GPIOG
#define OD5_PIN						GPIO_PIN_12
#define OD5_PORT					GPIOG
#define OD6_PIN						GPIO_PIN_11
#define OD6_PORT					GPIOG


#define CODEC_RST_PIN GPIO_PIN_9
#define CODEC_RST_PORT GPIOB

//#define I2S_SAMPLING_FREQ       I2S_AUDIOFREQ_96K
#define I2S_SAMPLING_FREQ I2S_AUDIOFREQ_48K
#define I2S_DATA_FORMAT I2S_DATAFORMAT_24B
#define I2S_STANDARD I2S_STANDARD_PHILIPS
#define CODEC_CS4271 1

#define I2S_INPUT_SAMPLES_PER_BUFFER (48)


#ifdef __cplusplus
}
#endif

#endif //_BDSP_BDSP_CONFIG_