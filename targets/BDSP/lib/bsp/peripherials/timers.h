/*
 * timers.h
 *
 *  Created on: 13 ????. 2018 ?.
 *      Author: Tim
 */

#ifndef BDSP_REVA_TIMERS_H_
#define BDSP_REVA_TIMERS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "../debug.h"

    void TIM2_init(void);
    void TIM2_start(void);

    void TIM_Callback(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* BDSP_REVA_TIMERS_H_ */
