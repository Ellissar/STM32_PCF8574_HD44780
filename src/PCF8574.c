/*
 * PCF8574.c
 *
 *  Created on: 15 мар. 2018 г.
 *      Author: ellis
 */

#include "PCF8574.h"


void PCF8574_Write (I2C_HandleTypeDef *hi2c, uint8_t address, uint8_t data)
{
	uint8_t i[2] = {0x00, 0x00};
	//i[0] = data;
	i[1] = data;

	HAL_I2C_Master_Transmit(hi2c, address, i, 2, 1000);
}


/*
uint8_t PCF8574_Read (uint8_t data)
{

}
*/
