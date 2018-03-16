/*
 * PCF8574.h
 *
 *  Created on: 15 мар. 2018 г.
 *      Author: ellissar
 *
 *      Функция работает с PCF8574 и PCF8574А по I2C на скорости 100kHz (Standard mode) и 400kHz (Fast mode).
 *      PCF8574 и PCF8574А отличаются только адресом I2C.
 *
 */

#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_


#include "stm32f3xx_hal.h"


#define PCF8574_ADDRESS			0x40
#define PCF8574A_ADDRESS		0x70


void PCF8574_Write (I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t data);


#endif /* INC_PCF8574_H_ */
