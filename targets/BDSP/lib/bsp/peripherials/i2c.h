/*
 * i2c.h
 *
 *  Created on: 28 Oct 2018
 *      Author: Tim
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"
#include "../debug.h"
#include "../config.h"

    I2C_HandleTypeDef hi2c;

    void I2C_Init(I2C_HandleTypeDef *hi2c2);
    uint8_t I2C_IsReady_dbg(uint32_t I2c_ADDR, I2C_HandleTypeDef *pI2C);
    void I2C_Transmit(uint32_t Adr, uint8_t Data, I2C_HandleTypeDef *pI2C);
    void I2C_Transmit_pack(uint32_t Adr, uint8_t *pData, uint32_t size, I2C_HandleTypeDef *pI2C);
    void I2C_Transmit_data(uint32_t Adr, uint8_t Register, uint8_t Data, I2C_HandleTypeDef *pI2C);
    void I2C_Read_register(uint32_t Adr, uint8_t Register, uint8_t *pData, I2C_HandleTypeDef *pI2C);
    void I2C_scan_dbg(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}
#endif
#endif /* INC_I2C_H_ */
