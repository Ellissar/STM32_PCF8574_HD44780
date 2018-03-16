/*
 * PCF8574_LCD_HAL.h
 *
 *  Created on: 15 мар. 2018 г.
 *      Author: ellissar
 *
 *
 */

#ifndef INC_PCF8574_LCD_HAL_H_
#define INC_PCF8574_LCD_HAL_H_


#include "stm32f3xx_hal.h"
#include "PCF8574.h"


extern I2C_HandleTypeDef	hi2c2;


#define RS					0x01
#define RW					0x02
#define E					0x04
#define LH					0xF0
#define ON_BLACKLIGHT		0x08


void LCD_Init(void);
void LCD_Puts(uint8_t *p);
void LCD_GotoXY(int row, char col);
void LCD_Clear(void);


#endif /* INC_PCF8574_LCD_HAL_H_ */
