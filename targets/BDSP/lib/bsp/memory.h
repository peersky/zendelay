/*
 * memory.h
 *
 *  Created on: 31 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_BDSP_MEMORY_H_
#define BSP_BDSP_MEMORY_H_

#include "stdint.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "../bsp/components/AS4C16M16SA/AS4C16M16SA.h"

	typedef enum
	{
		MEM_TYPE_SDRAM = 0,
		MEM_TYPE_EEPROM_1,
		MEM_TYPE_EEPROM_2,
		MEM_TYPES_NUM
	} Mem_Type_TypeDef;

	typedef struct Memory_Handle
	{
		uint32_t Addr_min;
		uint32_t Addr_max;
		uint32_t Read_addr;
		uint32_t Write_addr;
		uint32_t offset;
		Mem_Type_TypeDef MemoryType;
	} Memory_Handle_TypeDef;

#define SDRAM_Write32(address, value) (*(volatile uint32_t *)(SDRAM_BANK_ADDR + (address * 4)) = (value))
#define SDRAM_Read32(address) (*(volatile uint32_t *)(SDRAM_BANK_ADDR + (address * 4)))

	void Memory_RAM_Init(Memory_Handle_TypeDef *hMem);
	void Memory_Clean(Memory_Handle_TypeDef *hMem);

	void Memory_Fill_Next_64b(Memory_Handle_TypeDef *pHandle, signed int Data1, signed int Data2, uint32_t size);
	void Memory_Read_Next_Block(Memory_Handle_TypeDef *pHandle, signed int *Data, uint32_t size);
	void Memory_Write_Next_Block(Memory_Handle_TypeDef *pHandle, signed int *Data, uint32_t size);
	void Memory_Write_Next(Memory_Handle_TypeDef *pHandle, signed int Data);
	signed int Memory_Read_Next(Memory_Handle_TypeDef *hMem);
	signed int SDRAM_Move_n_Read_Next_32b(Memory_Handle_TypeDef *pHandle, uint32_t val);
	signed int SDRAM_Move_n_read_n_Getback_32b(Memory_Handle_TypeDef *pHandle, uint32_t val);
	signed int SDRAM_Move_n_Read_32b(Memory_Handle_TypeDef *pHandle, uint32_t val);
	void Memory_inc_read_addr(Memory_Handle_TypeDef *hMem);
	void Memory_dec_read_addr(Memory_Handle_TypeDef *hMem);
	void Memory_inc_write_addr(Memory_Handle_TypeDef *hMem);
	void Memory_inc_both_addr(Memory_Handle_TypeDef *hMem);
	void Memory_Move_Read_Addr(Memory_Handle_TypeDef *hMem, uint32_t val);
	signed int SDRAM_Read_Addr(Memory_Handle_TypeDef *pHandle, uint32_t Addr);
	int memory_test(Memory_Handle_TypeDef *hMem);
	void Memory_r_w_flipflop(Memory_Handle_TypeDef *hMem);

#ifdef __cplusplus
}
#endif
#endif /* BSP_BDSP_MEMORY_H_ */
