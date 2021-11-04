/*
 * i2c.c
 *
 *  Created on: 28 Oct 2018
 *      Author: Tim
 */


#include "i2c.h"
static uint8_t tx_data[5];

/* I2C2 init function */
void I2C_Init(I2C_HandleTypeDef  * hi2c2)
{

  hi2c2->Instance = I2C1;
  hi2c2->Init.ClockSpeed = 10000;
  hi2c2->Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2->Init.OwnAddress1 = 0;
  hi2c2->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2->Init.OwnAddress2 = 0;
  hi2c2->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(hi2c2) != HAL_OK)
  {
    BSP_Error_Handler();
  }

    /**Configure Analogue filter
    */
  if (HAL_I2CEx_ConfigAnalogFilter(hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    BSP_Error_Handler();
  }

    /**Configure Digital filter
    */
  if (HAL_I2CEx_ConfigDigitalFilter(hi2c2, 0) != HAL_OK)
  {
    BSP_Error_Handler();
  }

}

uint8_t I2C_IsReady_dbg(uint32_t I2c_ADDR, I2C_HandleTypeDef  * pI2C)
{
	if(HAL_I2C_IsDeviceReady(pI2C, I2c_ADDR, 1, 1000)!=HAL_OK)
	{
//		bsp_debug("%s%02X\t","I2C Device ",I2c_ADDR);
//		bsp_debug("%s\n"," is not ready");
		return 0;
	}
	else
	{
		bsp_debug("%s%02X\t","I2C Device ",(uint)I2c_ADDR);
		bsp_debug("%s","OK!\n");
		return 1;
	}
}


void I2C_Transmit(uint32_t Adr, uint8_t Data,I2C_HandleTypeDef  * pI2C)
{
	tx_data[0]=Data;
	if( HAL_I2C_Master_Transmit(pI2C,Adr, tx_data, 1, 10)!=HAL_OK)
	{
//		 BSP_Error_Handler();
		bsp_debug("%s",":(!\n");
	}
}

void I2C_Transmit_pack(uint32_t Adr, uint8_t *pData, uint32_t size, I2C_HandleTypeDef  * pI2C)
{
	if( HAL_I2C_Master_Transmit(pI2C,Adr, pData, size, 1000)!=HAL_OK)
	{
		 BSP_Error_Handler();
	}
}
void I2C_Transmit_data(uint32_t Adr, uint8_t Register, uint8_t Data, I2C_HandleTypeDef  * pI2C)
{
	tx_data[0]=Register;
	tx_data[1]=Data;

	if( HAL_I2C_Master_Transmit(pI2C,Adr, tx_data, 2, 1000)!=HAL_OK)
	{
//		 BSP_Error_Handler();
		bsp_debug("%s",":(!\n");
	}
}

void I2C_Read_register(uint32_t Adr, uint8_t Register, uint8_t * pData, I2C_HandleTypeDef  * pI2C)
{
	if(HAL_I2C_Mem_Read(pI2C,Adr,Register,1,pData,1,1000)!=HAL_OK)
	{
		 BSP_Error_Handler();
	}
}

void I2C_scan_dbg(I2C_HandleTypeDef  * hi2c)
{
	for(int i=0; i<0xFF; i++)
	{
		HAL_Delay(10);
		I2C_IsReady_dbg(i,hi2c);
	}
}
