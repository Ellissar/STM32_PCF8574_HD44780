/*
 * PCF8574A_LCD.c
 *s
 *  Created on: 13 мар. 2018 г.
 *      Author: ellissar
 */


#include "PCF8574_LCD_HAL.h"


void LCD_SendByte (uint8_t data, uint8_t com, uint8_t dat)
{
	uint8_t buff;
	buff = data;
	buff = (buff & LH)|E|com|dat|ON_BLACKLIGHT;
	PCF8574_Write (&hi2c2, PCF8574A_ADDRESS, buff);
	buff &= ~E;
	PCF8574_Write (&hi2c2, PCF8574A_ADDRESS, buff);
	//HAL_Delay(1);		//У меня работает без задержки по I2C как на 100kHz так и на 400kHz
	buff = data;
	buff = (buff <<4)|E|com|dat|ON_BLACKLIGHT;
	PCF8574_Write (&hi2c2, PCF8574A_ADDRESS, buff);
	buff &= ~E;
	PCF8574_Write (&hi2c2, PCF8574A_ADDRESS, buff);
}


void LCD_Command(uint8_t data)
{
	LCD_SendByte (data, 0x00, 0x00);
}


void LCD_Data(uint8_t data)
{
	LCD_SendByte (data, 0x00, RS);
}


//Инициализация дисплея.
//Необходимо вызвать перед использованием дисплея.
void LCD_Init(void)
{
	HAL_Delay(20);
	LCD_Command(0x33);
	HAL_Delay(1);
	LCD_Command(0x32);
	HAL_Delay(1);

	LCD_Command(0x28);		//0x0010 1000 [5:0] 4-х разрядная шина данных, [4:1] две строки, [3:0] 5х8 точек
	LCD_Command(0x08);		//0x0000 1000 [3:0] выключить вывод изображения на экран (Display off)
	LCD_Command(0x01);		//0x0000 0001 [0:1] очистить экран (Display clear)

	HAL_Delay(1);
	LCD_Command(0x06);		//0x0000 0110 [0:0] сдвиг содержимого экрана [1:1] вправо (Entry mode set)
	LCD_Command(0x0E);		//0x0000 1110 [3:1] включить вывод изобажения на экран, [2:1] отобразить курсор в виде черты [0:0] без мигания
}


//Отправка массива символов на дисплей
void LCD_Puts(uint8_t *p)
{
	while(*p) LCD_Data(*p++);
}


//Установить курсор в указанную позицию дисплея
//Корректно будет работать для дисплея 16х2
void LCD_GotoXY(int row, char col)
{
	uint8_t cursor_pos = 0x80;
	//Если строка = 2 установить курсор на 2-ю строку
	if (row == 2) {
		cursor_pos |= 0x40;
	} else { //в остальных случаях установить курсор на 1-ю строку
		cursor_pos |= 0x00;
	}

	//Если значение столбца не превышает 16, установить курсор в позицию col
	if (col < 16) {
		cursor_pos |= col;
	} else { //в остальных случаях установить курсор в начало строки
		cursor_pos |= 0x00;
	}
	LCD_Command(cursor_pos);
}


//Очистить дисплей
void LCD_Clear(void)
{
	LCD_Command(0x01);
	HAL_Delay(2);
}
