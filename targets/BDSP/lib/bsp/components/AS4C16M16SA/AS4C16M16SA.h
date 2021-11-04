/*
 * AS4C16M16SA.h
 *
 *  Created on: 31 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_COMPONENTS_AS4C16M16SA_AS4C16M16SA_H_
#define BSP_COMPONENTS_AS4C16M16SA_AS4C16M16SA_H_

#include "stm32f4xx_hal.h"
#include "../../debug.h"

typedef struct SDRAM_handler
{
  SDRAM_HandleTypeDef     sdram;
  FMC_SDRAM_TimingTypeDef timing;
} SDRAM_handler;

/* Exported constants --------------------------------------------------------*/
#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)
#define SDRAM_BANK2_ADDR                 ((uint32_t)0xD0000000) //Block 6
#define SDRAM_BANK1_ADDR                 ((uint32_t)0xC0000000) //Block 5

#define SDRAM_BANK_ADDR                  SDRAM_BANK1_ADDR

#define SDRAM_AS4C16M16SA_SIZE           ((uint32_t)0x01e84800) //256Mbit in 8 bit addressing
#define SDRAM_SIZE                       SDRAM_AS4C16M16SA_SIZE
#define SDRAM_SIZE_U16                   (SDRAM_SIZE/2)
#define SDRAM_SIZE_S32					(SDRAM_SIZE/4)			//256MBit in 32 bit addressing


//SYSCLK rate should be 180Mhz
#define SDRAM_CLK_60MHZ 1
#define SDRAM_CLK_90MHZ 2
#define SDRAM_CLK       SDRAM_CLK_90MHZ

/**?????????????????????????????????????????????????????????????????????????????
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define SDRAM_REFRESH_COUNT       ((uint32_t)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */

void SDRAM_write_protection_disable(void);
void SDRAM_write_protection_enable(void);
void SDRAM_init_sequence(SDRAM_HandleTypeDef *hsdram);
void AS4C16M16SA_Init(void);
#endif /* BSP_COMPONENTS_AS4C16M16SA_AS4C16M16SA_H_ */
