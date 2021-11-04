/*
 * BDEL1_Conf.h
 *
 *  Created on: 24 Oct 2018
 *      Author: Tim
 */

#ifndef TESTS_BDEL1_CONF_H_
#define TESTS_BDEL1_CONF_H_
#include "stm32f4xx_hal.h"

//#include "BDSP_BSP_Base.h"

#define MAX_DELAY_TIME_MS 3000
#define SYNC_RESET_TIME MAX_DELAY_TIME_MS
#define LONG_ON_TIME_MS 1500

//THIS IS IN in ADC POT SAMPLES [mS*SAMPLE_MULT]
#define CALIB_VAL 1; //((0+((I2S_INPUT_SAMPLES_PER_BUFFER*1000)/I2S_SAMPLING_FREQ)))

#define LED_SYNC OD4
#define LED_CLIP OD5
#define LED_HOLD OD3
#define LED_REV OD2
#define LED_ADD OD0

#define SYNC_LED_ON OD_ON(LED_SYNC)
#define SYNC_LED_OFF OD_OFF(LED_SYNC)
#define CLIP_LED_ON OD_ON(LED_CLIP)
#define CLIP_LED_OFF OD_OFF(LED_CLIP)
#define HOLD_LED_ON OD_ON(LED_HOLD)
#define HOLD_LED_OFF OD_OFF(LED_HOLD)
#define REV_LED_ON OD_ON(LED_REV)
#define REV_LED_OFF OD_OFF(LED_REV)
#define ADD_LED_ON OD_ON(LED_ADD)
#define ADD_LED_OFF OD_OFF(LED_ADD)

#define ALL_LED_ON   \
    do               \
    {                \
        SYNC_LED_ON; \
        HOLD_LED_ON; \
        ADD_LED_ON;  \
        REV_LED_ON;  \
    } while (0U)

#define ALL_LED_OFF   \
    do                \
    {                 \
        SYNC_LED_OFF; \
        HOLD_LED_OFF; \
        ADD_LED_OFF;  \
        REV_LED_OFF;  \
    } while (0U)

#define CV_FEEDBACK CV_IN_2
#define CV_TIME CV_IN_0
#define POT_TIME ADC_IN_6
#define POT_FEEDBACK ADC_IN_3

#define POT_TIME_NUMBER (ADC_ReturnRank(POT_TIME) - 1)
#define POT_FEEDBACK_NUMBER (ADC_ReturnRank(POT_FEEDBACK) - 1)
#define CV_TIME_NUMBER (ADC_ReturnRank(CV_TIME) - 1)
#define CV_FEEDBACK_NUMBER (ADC_ReturnRank(CV_FEEDBACK) - 1)

#define SYNC_PB_PORT IO4_PORT
#define SYNC_PB_PIN IO4_PIN
#define SYNC_PB IO4
#define SYNC_PB_ENUM IO4_ENUM

#define SYNC_IN_PORT IO13_PORT
#define SYNC_IN_PIN IO13_PIN
#define SYNC_IN IO13
#define SYNC_IN_ENUM IO13_ENUM

#define isSYNC (SYNC_PB || SYNC_IN)

#define ADD_PB_PORT IO12_PORT
#define ADD_PB_PIN IO12_PIN
#define ADD_PB IO12
#define ADD_PB_ENUM IO12_ENUM

#define ADD_IN_PORT IO0_PORT
#define ADD_IN_PIN IO0_PIN
#define ADD_IN IO0
#define ADD_IN_ENUM IO0_ENUM

#define isADD (ADD_PB || ADD_IN)

#define HOLD_PB_PORT IO14_PORT
#define HOLD_PB_PIN IO14_PIN
#define HOLD_PB IO14
#define HOLD_PB_ENUM IO14_ENUM

#define HOLD_IN_PORT IO3_PORT
#define HOLD_IN_PIN IO3_PIN
#define HOLD_IN IO3
#define HOLD_IN_ENUM IO3_ENUM

#define isHOLD (HOLD_PB || HOLD_IN)

#define REV_PB_PORT IO15_PORT
#define REV_PB_PIN IO15_PIN
#define REV_PB IO15
#define REV_PB_ENUM IO15_ENUM

#define REV_IN_PORT IO10_PORT
#define REV_IN_PIN IO10_PIN
#define REV_IN IO10
#define REV_IN_ENUM IO10_ENUM

#define isREV (REV_PB || REV_IN)

#define isCALIB (REV_PB && HOLD_PB && ADD_PB && SYNC_PB)
#define isALT_MODE (REV_PB && HOLD_PB && ADD_PB && !SYNC_PB)

#define PINGPONG_PORT IO9_PORT
#define PINGPONG_PIN IO9_PIN
#define PINGPONG_PB IO9
#define PINGPONG_PB_ENUM IO9_ENUM

#define DELAY_TYPE_PORT IO11_PORT
#define DELAY_TYPE_PIN IO11_PIN
#define DELAY_TYPE_PB IO11
#define DELAY_TYPE_ENUM IO11_ENUM

typedef enum
{
    SW_PP = 0,
    SW_DEL_TYPE,
    PB_ADD,
    PB_REV,
    PB_HOLD,
    PB_SYNC,
    IO_REV,
    IO_ADD,
    IO_HOLD,
    SWPB_NUM
} Config_SWPBs_EnumTypeDef;

#endif /* TESTS_BDEL1_CONF_H_ */