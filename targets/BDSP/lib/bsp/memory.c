/*
 * memory.c
 *
 *  Created on: 31 Oct 2018
 *      Author: Tim
 */

#include "memory.h"

void Memory_RAM_Init(Memory_Handle_TypeDef *hMem)
{
	bsp_dbg_print("Memory_RAM_Init");
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		bsp_dbg_print("Launching AS4C16M16SA");
		AS4C16M16SA_Init();
		SDRAM_write_protection_disable();
	}
	else
	{
		BSP_Error_Handler();
	}
}

void Memory_Clean(Memory_Handle_TypeDef *hMem)
{
	signed int val = 0;
	uint32_t t_r_a = hMem->Read_addr;
	uint32_t t_w_a = hMem->Write_addr;
	Memory_Fill_Next_64b(hMem, val, val, SDRAM_SIZE_S32 / 2);
	hMem->Read_addr = t_r_a;
	hMem->Write_addr = t_w_a;
}

void Memory_Fill_Next_64b(Memory_Handle_TypeDef *hMem, signed int Data1, signed int Data2, uint32_t size)
{
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		for (uint32_t i = 0; i < size; i++)
		{

			Memory_Write_Next(hMem, Data1);
			Memory_Write_Next(hMem, Data2);
		}
	}
	else
	{
		BSP_Error_Handler();
	}
}

void Memory_Read_Next_Block(Memory_Handle_TypeDef *hMem, signed int *Data, uint32_t size)
{
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		for (volatile uint32_t i = 0; i < size; i++)
		{

			Data[i] = Memory_Read_Next(hMem);
		}
	}
	else
	{
		BSP_Error_Handler();
	}
}

void Memory_Write_Next_Block(Memory_Handle_TypeDef *hMem, signed int *Data, uint32_t size)
{
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		for (volatile uint32_t i = 0; i < size; i++)
		{
			Memory_Write_Next(hMem, Data[i]);
		}
	}
	else
	{
		BSP_Error_Handler();
	}
}

void Memory_Write_Next(Memory_Handle_TypeDef *hMem, signed int Data)
{
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		Memory_inc_write_addr(hMem);
		SDRAM_Write32(hMem->Write_addr, Data);
	}
	else
	{
		BSP_Error_Handler();
	}
}
signed int Memory_Read_Next(Memory_Handle_TypeDef *hMem)
{
	if (hMem->MemoryType == MEM_TYPE_SDRAM)
	{
		Memory_inc_read_addr(hMem);
		return SDRAM_Read32(hMem->Read_addr);
	}
	else
	{
		BSP_Error_Handler();
		return 0;
	}
}

static uint32_t inc_addr(uint32_t *pAdr, uint32_t IncVal, uint32_t Addr_max)
{
	return (*pAdr + IncVal) % (Addr_max + 1);
}
signed int SDRAM_Read_Addr(Memory_Handle_TypeDef *pHandle, uint32_t Addr)
{
	uint32_t r_a = inc_addr(&pHandle->Read_addr, Addr, pHandle->Addr_max);
	return SDRAM_Read32(r_a);
}
signed int SDRAM_Move_n_Read_Next_32b(Memory_Handle_TypeDef *pHandle, uint32_t val)
{
	Memory_Move_Read_Addr(pHandle, val);
	return Memory_Read_Next(pHandle);
}

signed int SDRAM_Move_n_Read_32b(Memory_Handle_TypeDef *pHandle, uint32_t val)
{
	Memory_Move_Read_Addr(pHandle, val);
	return SDRAM_Read32(pHandle->Read_addr);
}

signed int SDRAM_Move_n_read_n_Getback_32b(Memory_Handle_TypeDef *pHandle, uint32_t val)
{
	//	uint32_t asert_param_read_a=pHandle->Read_addr;
	signed int retval = 0;
	Memory_Move_Read_Addr(pHandle, val);
	//	assert_param(asert_param_read_a!=pHandle->Read_addr+1);
	retval = SDRAM_Read32(pHandle->Read_addr);
	Memory_Move_Read_Addr(pHandle, (pHandle->Addr_max + 1 - val + 1));
	return retval;
}

void Memory_inc_read_addr(Memory_Handle_TypeDef *hMem)
{
	hMem->Read_addr = (hMem->Read_addr + 1) % (hMem->Addr_max + 1);
}
void Memory_dec_read_addr(Memory_Handle_TypeDef *hMem)
{
	hMem->Read_addr--;
	if (hMem->Read_addr >= hMem->Addr_max)
	{
		hMem->Read_addr = hMem->Addr_max;
	}
}
void Memory_inc_write_addr(Memory_Handle_TypeDef *hMem)
{
	hMem->Write_addr = (hMem->Write_addr + 1) % (hMem->Addr_max + 1);
}
void Memory_inc_both_addr(Memory_Handle_TypeDef *hMem)
{
	Memory_inc_read_addr(hMem);
	Memory_inc_write_addr(hMem);
}

void Memory_Move_Read_Addr(Memory_Handle_TypeDef *hMem, uint32_t val)
{
	hMem->Read_addr = (hMem->Read_addr + val) % (hMem->Addr_max + 1);
}

int memory_test(Memory_Handle_TypeDef *hMem)
{
	uint32_t t_r_a = hMem->Read_addr;
	uint32_t t_w_a = hMem->Write_addr;
	signed int KeyWord = 0x59ABCDEF;
	uint32_t err = 0;

	signed int write_val;
	hMem->Read_addr = 0;
	hMem->Write_addr = 0;

	for (volatile int i = 0; i < (hMem->Addr_max - hMem->Addr_min); i++)
	{
		write_val = KeyWord * i;
		Memory_Write_Next(hMem, write_val);
		if (Memory_Read_Next(hMem) != write_val)
		{
			err++;
		}
	}

	HAL_Delay(1000);
	hMem->Read_addr = 0;
	hMem->Write_addr = 0;
	for (volatile int i = 0; i < (hMem->Addr_max - hMem->Addr_min); i++)
	{
		write_val = KeyWord * i;
		if (Memory_Read_Next(hMem) != write_val)
		{
			err++;
		}
	}

	hMem->Read_addr = t_r_a;
	hMem->Write_addr = t_w_a;
	if (!err)
		return 1;
	return 0;
}

void Memory_r_w_flipflop(Memory_Handle_TypeDef *hMem)
{
	uint32_t tval = hMem->Write_addr;
	hMem->Write_addr = hMem->Read_addr;
	hMem->Read_addr = tval;
}

//uint32_t * RingSub_GetTail_From_Ring(Ring_Handle_TypeDef * pRing)
//{
//	uint32_t * pTail;
//	pTail =
//	return pTail;
//}
