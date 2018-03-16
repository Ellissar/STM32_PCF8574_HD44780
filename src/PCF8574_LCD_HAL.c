/*
 * PCF8574A_LCD.c
 *s
 *  Created on: 13 ���. 2018 �.
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
	//HAL_Delay(1);		//� ���� �������� ��� �������� �� I2C ��� �� 100kHz ��� � �� 400kHz
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


//������������� �������.
//���������� ������� ����� �������������� �������.
void LCD_Init(void)
{
	HAL_Delay(20);
	LCD_Command(0x33);
	HAL_Delay(1);
	LCD_Command(0x32);
	HAL_Delay(1);

	LCD_Command(0x28);		//0x0010 1000 [5:0] 4-� ��������� ���� ������, [4:1] ��� ������, [3:0] 5�8 �����
	LCD_Command(0x08);		//0x0000 1000 [3:0] ��������� ����� ����������� �� ����� (Display off)
	LCD_Command(0x01);		//0x0000 0001 [0:1] �������� ����� (Display clear)

	HAL_Delay(1);
	LCD_Command(0x06);		//0x0000 0110 [0:0] ����� ����������� ������ [1:1] ������ (Entry mode set)
	LCD_Command(0x0E);		//0x0000 1110 [3:1] �������� ����� ���������� �� �����, [2:1] ���������� ������ � ���� ����� [0:0] ��� �������
}


//�������� ������� �������� �� �������
void LCD_Puts(uint8_t *p)
{
	while(*p) LCD_Data(*p++);
}


//���������� ������ � ��������� ������� �������
//��������� ����� �������� ��� ������� 16�2
void LCD_GotoXY(int row, char col)
{
	uint8_t cursor_pos = 0x80;
	//���� ������ = 2 ���������� ������ �� 2-� ������
	if (row == 2) {
		cursor_pos |= 0x40;
	} else { //� ��������� ������� ���������� ������ �� 1-� ������
		cursor_pos |= 0x00;
	}

	//���� �������� ������� �� ��������� 16, ���������� ������ � ������� col
	if (col < 16) {
		cursor_pos |= col;
	} else { //� ��������� ������� ���������� ������ � ������ ������
		cursor_pos |= 0x00;
	}
	LCD_Command(cursor_pos);
}


//�������� �������
void LCD_Clear(void)
{
	LCD_Command(0x01);
	HAL_Delay(2);
}
