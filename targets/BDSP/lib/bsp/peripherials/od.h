/*
 * OD_Outs.h
 *
 *  Created on: 25 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_BDSP_OD_OUTS_H_
#define BSP_BDSP_OD_OUTS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "../debug.h"
#include "../config.h"

#ifdef ll_bsp
#define OD0_ON OD0_PORT->BSRR = OD0_PIN
#define OD0_OFF OD0_PORT->BSRR = (OD0_PIN << 16)
#define OD1_ON OD1_PORT->BSRR = OD1_PIN
#define OD1_OFF OD1_PORT->BSRR = (OD1_PIN << 16)
#define OD2_ON OD2_PORT->BSRR = OD2_PIN
#define OD2_OFF OD2_PORT->BSRR = (OD2_PIN << 16)
#define OD3_ON OD3_PORT->BSRR = OD3_PIN
#define OD3_OFF OD3_PORT->BSRR = (OD3_PIN << 16)
#define OD4_ON OD4_PORT->BSRR = OD4_PIN
#define OD4_OFF OD4_PORT->BSRR = (OD4_PIN << 16)
#define OD5_ON OD5_PORT->BSRR = OD5_PIN
#define OD5_OFF OD5_PORT->BSRR = (OD5_PIN << 16)
#define OD6_ON OD6_PORT->BSRR = OD6_PIN
#define OD6_OFF OD6_PORT->BSRR = (OD6_PIN << 16)
#endif

	typedef enum
	{
		OD0 = 0,
		OD1,
		OD2,
		OD3,
		OD4,
		OD5,
		OD6,
		OD_NUM
	} OD_Outs_TypeDef;

	void OD_ON(OD_Outs_TypeDef Output);
	void OD_OFF(OD_Outs_TypeDef Output);
	void OD_Toggle(OD_Outs_TypeDef Output);
	void OD_All_ON(void);
	void OD_All_OFF(void);
	void OD_All_Toggle(void);
	void OD_Init_all(void);

	void OD_blink_blocking(uint32_t speed, uint8_t repeats);

#ifdef __cplusplus
}
#endif
#endif /* BSP_BDSP_OD_OUTS_H_ */
