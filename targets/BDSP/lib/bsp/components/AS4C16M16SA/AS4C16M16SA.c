/*
 * AS4C16M16SA.c
 *
 *  Created on: 31 Oct 2018
 *      Author: Tim
 */


#include "AS4C16M16SA.h"

SDRAM_handler __SDRAM_handler[1];
uint32_t _SDRAM_num = (sizeof(__SDRAM_handler)/sizeof(SDRAM_handler));

void AS4C16M16SA_Init(void)
{
	SDRAM_HandleTypeDef     *SDRAM=&__SDRAM_handler[0].sdram;
	FMC_SDRAM_TimingTypeDef *SDRAM_Timing=&__SDRAM_handler[0].timing;

  /*##-1- Configure the SDRAM device #########################################*/
  /* SDRAM device configuration */
  SDRAM->Instance = FMC_SDRAM_DEVICE;

  /****************************************************************************/
  /*90Mhz*/
#if SDRAM_CLK == SDRAM_CLK_90MHZ
  //SDRAM->Init.SDBank             = FMC_SDRAM_BANK2;
  SDRAM->Init.SDBank             = FMC_SDRAM_BANK1;
  SDRAM->Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
  SDRAM->Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_13;
  SDRAM->Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_16;
  SDRAM->Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  SDRAM->Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
  SDRAM->Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  SDRAM->Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_2; // 90Mhz
  SDRAM->Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE	;
//  SDRAM->Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;
  SDRAM->Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;

  /* Timing configuration for 90 MHz of SDRAM clock frequency (180MHz/2) */
  /* TMRD: 2 Clock cycles */
  SDRAM_Timing->LoadToActiveDelay    = 2;
  /* TXSR: min->70ns (6x11.90ns) */
  SDRAM_Timing->ExitSelfRefreshDelay = 7;
  /* TRAS: min->42ns (4x11.90ns) max=120k (ns) */
  SDRAM_Timing->SelfRefreshTime      = 4;
  /* TRC:  min->63 (6x11.90ns) */
  SDRAM_Timing->RowCycleDelay        = 7;//was 7
  /* TWR:  2 C->ock cycles */
  SDRAM_Timing->WriteRecoveryTime    = 2;
  /* TRP:  15n-> => 2x11.90ns */
  SDRAM_Timing->RPDelay              = 2;
  /* TRCD: 15n-> => 2x11.90ns */
  SDRAM_Timing->RCDDelay             = 2;

  /****************************************************************************/
  /*60Mhz*/
#elif SDRAM_CLK == SDRAM_CLK_60MHZ
  SDRAM->Init.SDBank             = FMC_SDRAM_BANK2;
  SDRAM->Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
  SDRAM->Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
  SDRAM->Init.MemoryDataWidth    = FMC_SDRAM_MEM_BUS_WIDTH_16;
  SDRAM->Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  SDRAM->Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
  SDRAM->Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  SDRAM->Init.SDClockPeriod      = FMC_SDRAM_CLOCK_PERIOD_3; //60Mhz
  SDRAM->Init.ReadBurst          = FMC_SDRAM_RBURST_DISABLE;
  SDRAM->Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_1;

  /* Timing configuration for 90 MHz of SDRAM clock frequency (180MHz/3) */
  /* TMRD: 2 Clock cycles */
  SDRAM_Timing->LoadToActiveDelay    = 3;
  /* TXSR: min->70ns (6x17ns) */
  SDRAM_Timing->ExitSelfRefreshDelay = 5;//5
  /* TRAS: min->42ns (4x17ns) max=120k (ns) */
  SDRAM_Timing->SelfRefreshTime      = 3;
  /* TRC:  min->63 (6x17ns) */
  SDRAM_Timing->RowCycleDelay        = 5;//5
  /* TWR:  2 C->ock cycles */
  SDRAM_Timing->WriteRecoveryTime    = 1;
  /* TRP:  15n-> => 2x17ns */
  SDRAM_Timing->RPDelay              = 1;
  /* TRCD: 15n-> => 2x17ns */
  SDRAM_Timing->RCDDelay             = 1;
#endif


  /* Initialize the SDRAM controller */
  if(HAL_SDRAM_Init(SDRAM, SDRAM_Timing) != HAL_OK)
  {
    /* Initialization Error */
    _bsp_error(NULL,0);
  }

  /*##-2- Program SDRAM external device ######################################*/
  SDRAM_init_sequence(SDRAM);

}

void SDRAM_write_protection_enable(void)
{
  SDRAM_HandleTypeDef     *SDRAM=&__SDRAM_handler[0].sdram;

  HAL_SDRAM_WriteProtection_Enable(SDRAM);
}

void SDRAM_write_protection_disable(void)
{
  SDRAM_HandleTypeDef     *SDRAM=&__SDRAM_handler[0].sdram;

  HAL_SDRAM_WriteProtection_Disable(SDRAM);
}

void SDRAM_init_sequence(SDRAM_HandleTypeDef *hsdram)
{
	FMC_SDRAM_CommandTypeDef Command;

    __IO uint32_t tmpmrd =0;
  /* Step 3:  Configure a clock configuration enable command */
  Command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(100);

  /* Step 5: Configure a PALL (precharge all) command */
  Command.CommandMode            = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  /* Step 6 : Configure a Auto-Refresh command */
  Command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 4;
  Command.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4         |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  Command.AutoRefreshNumber      = 1;
  Command.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, &Command, 0x1000);

#if SDRAM_CLK == SDRAM_CLK_90MHZ
  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 = 1386, 0x56A*/
  /* Set the device refresh counter */
  //HAL_SDRAM_ProgramRefreshRate(hsdram, 0x562-0x100);
  HAL_SDRAM_ProgramRefreshRate(hsdram, 0x56A-20);
#elif SDRAM_CLK == SDRAM_CLK_60MHZ
  /* Step 8: Set the refresh rate counter */
  /* (7.8 us x Freq) - 20 = 448, 0x56A*/
  /* Set the device refresh counter */
  HAL_SDRAM_ProgramRefreshRate(hsdram, 448);
#endif

}
