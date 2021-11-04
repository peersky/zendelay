/*
 * gpio.h
 *
 *  Created on: 30 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "../debug.h"
#include "../config.h"
#include "od.h"

#define IO_IS_OUTPUT (GPIO_MODE_OUTPUT_PP)
#define IO_IS_INPUT (GPIO_MODE_INPUT)
#define IO_IS_IT (GPIO_MODE_IT_RISING | GPIO_MODE_IT_FALLING | GPIO_MODE_INPUT)

#define IO0_ENABLE IO0_PORT->BSRR = IO0_PIN
#define IO0_DISABLE IO0_PORT->BRR = IO0_PIN
#define IO0 ((IO0_PORT->IDR & IO0_PIN))

#define IO1_ENABLE IO1_PORT->BSRR = IO1_PIN
#define IO1_DISABLE IO1_PORT->BRR = IO1_PIN
#define IO1 ((IO1_PORT->IDR & IO1_PIN))

#define IO2_ENABLE IO2_PORT->BSRR = IO2_PIN
#define IO2_DISABLE IO2_PORT->BRR = IO2_PIN
#define IO2 ((IO2_PORT->IDR & IO2_PIN))

#define IO3_ENABLE IO3_PORT->BSRR = IO3_PIN
#define IO3_DISABLE IO3_PORT->BRR = IO3_PIN
#define IO3 ((IO3_PORT->IDR & IO3_PIN))

#define IO4_ENABLE IO4_PORT->BSRR = IO4_PIN
#define IO4_DISABLE IO4_PORT->BRR = IO4_PIN
#define IO4 ((IO4_PORT->IDR & IO4_PIN))

#define IO5_ENABLE IO5_PORT->BSRR = IO5_PIN
#define IO5_DISABLE IO5_PORT->BRR = IO5_PIN
#define IO5 ((IO5_PORT->IDR & IO5_PIN))

#define IO6_ENABLE IO6_PORT->BSRR = IO6_PIN
#define IO6_DISABLE IO6_PORT->BRR = IO6_PIN
#define IO6 ((IO6_PORT->IDR & IO6_PIN))

#define IO7_ENABLE IO7_PORT->BSRR = IO7_PIN
#define IO7_DISABLE IO7_PORT->BRR = IO7_PIN
#define IO7 ((IO7_PORT->IDR & IO7_PIN))

#define IO8_ENABLE IO8_PORT->BSRR = IO8_PIN
#define IO8_DISABLE IO8_PORT->BRR = IO8_PIN
#define IO8 ((IO8_PORT->IDR & IO8_PIN))

#define IO9_ENABLE IO9_PORT->BSRR = IO9_PIN
#define IO9_DISABLE IO9_PORT->BRR = IO9_PIN
#define IO9 ((IO9_PORT->IDR & IO9_PIN))

#define IO10_ENABLE IO10_PORT->BSRR = IO10_PIN
#define IO10_DISABLE IO10_PORT->BRR = IO10_PIN
#define IO10 ((IO10_PORT->IDR & IO10_PIN))

#define IO11_ENABLE IO11_PORT->BSRR = IO11_PIN
#define IO11_DISABLE IO11_PORT->BRR = IO11_PIN
#define IO11 ((IO11_PORT->IDR & IO11_PIN))

#define IO12_ENABLE IO12_PORT->BSRR = IO12_PIN
#define IO12_DISABLE IO12_PORT->BRR = IO12_PIN
#define IO12 ((IO12_PORT->IDR & IO12_PIN))

#define IO13_ENABLE IO13_PORT->BSRR = IO13_PIN
#define IO13_DISABLE IO13_PORT->BRR = IO13_PIN
#define IO13 ((IO13_PORT->IDR & IO13_PIN))

#define IO14_ENABLE IO14_PORT->BSRR = IO14_PIN
#define IO14_DISABLE IO14_PORT->BRR = IO14_PIN
#define IO14 ((IO14_PORT->IDR & IO14_PIN))

#define IO15_ENABLE IO15_PORT->BSRR = IO15_PIN
#define IO15_DISABLE IO15_PORT->BRR = IO15_PIN
#define IO15 ((IO15_PORT->IDR & IO15_PIN))

#define DIRECT_IO0_PIN GPIO_PIN_10
#define DIRECT_IO0_PORT GPIOG
#define DIRECT_IO1_PIN GPIO_PIN_15
#define DIRECT_IO1_PORT GPIOC
#define DIRECT_IO2_PIN GPIO_PIN_14
#define DIRECT_IO2_PORT GPIOC
#define DIRECT_IO3_PIN GPIO_PIN_10
#define DIRECT_IO3_PORT GPIOF
#define DIRECT_IO4_PIN GPIO_PIN_12
#define DIRECT_IO4_PORT GPIOD
#define DIRECT_IO5_PIN GPIO_PIN_11
#define DIRECT_IO5_PORT GPIOB

	typedef enum
	{
		OFF = 0,
		ON,
		LONG_ON,
		NUM_SWPB_STATES
	} IO_States;

	typedef enum
	{
		IO_DISABLED = 0,
		IO_ENABLED
	} IO_Inited;

	//typedef enum
	//{
	//	IO_IS_INPUT=0,
	//	IO_IS_OUTPUT
	//}IO_Dir_Enum;
	typedef struct __GPIO_TypeDef
	{

		IO_States state;
		int8_t qeue;
		uint16_t pin;
		GPIO_TypeDef *GPIOx;
		uint32_t Mode;
		uint32_t timestamp;
		IRQn_Type IRQn;
		//	uint8_t  			IRQ_enable;
		uint8_t NVIC_Prio;
		uint8_t NVIC_SubPrio;
		IO_Inited isInit;
		uint32_t debounce;
		uint32_t debounce_time;
	} GPIO_BSP_TypeDef;

	typedef enum
	{
		IO0_ENUM = 0,
		IO1_ENUM,
		IO2_ENUM,
		IO3_ENUM,
		IO4_ENUM,
		IO5_ENUM,
		IO6_ENUM,
		IO7_ENUM,
		IO8_ENUM,
		IO9_ENUM,
		IO10_ENUM,
		IO11_ENUM,
		IO12_ENUM,
		IO13_ENUM,
		IO14_ENUM,
		IO15_ENUM,
		NUM_IO_ENUM
	} IO_ENUM_TypeDef;

	typedef struct __BSP_GPIO_InitTypeDef
	{
		IO_ENUM_TypeDef IO_n;
		uint32_t mode;
		uint32_t debounce_time;
	} BSP_GPIO_InitTypeDef;

	void GPIO_Clock_Check(GPIO_TypeDef *GPIOX);
	void IO_InitAll(void);
	void IO_configure(BSP_GPIO_InitTypeDef *ios, size_t size);
	void IO_IT(IO_ENUM_TypeDef num, IO_States Current_state);
	IO_States IO_Read_State(IO_ENUM_TypeDef num);

	void EXTI15_10_IRQHandler(void);
	void EXTI9_5_IRQHandler(void);
	void EXTI3_IRQHandler(void);
	void EXTI2_IRQHandler(void);
	void EXTI0_IRQHandler(void);
	void EXTI4_IRQHandler(void);

	void IO_IT_Callback(IO_ENUM_TypeDef num, IO_States Current_state);
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
	void IO_Update_State(IO_ENUM_TypeDef num, IO_States New_state);
	IO_States IO_Read_Pin(IO_ENUM_TypeDef num);

#ifdef __cplusplus
}
#endif
#endif /* BSP_GPIO_H_ */
