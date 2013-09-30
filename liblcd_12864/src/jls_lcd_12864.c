/*
*   JSL D-NOW LIB for liblcd_12864  *
*   Author: Shengjia.zhu           *
*   Date: Nov 3, 2012               *
*/

#include "jls_lcd_12864.h"
#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_lcd_12864_ascii8.h"
void _lcd_12864_display_ascii(uchar ch, uchar x, uchar y)
{
	uchar addr;
	if(x > 15)
	{
		return;
	}
	switch (y)
	{
	case 0:
		addr = 0x80 + x / 2;
		break;
	case 1:
		addr = 0x90 + x / 2;
		break;
	case 2:
		addr = 0x88 + x / 2;
		break;
	case 3:
		addr = 0x98 + x / 2;
		break;
	}
	_lcd_12864_write_cmd(0x30);
	_lcd_12864_write_cmd(addr);
	if (x % 2 == 1)
	{
		_lcd_12864_read_data();
	}
	_lcd_12864_write_data(ch);
	_lcd_12864_write_cmd(0x34);
	_lcd_12864_write_cmd(0x36); //打开绘图显示
}

void _lcd_12864_display_ascii8( uchar ASCII, unsigned char x, unsigned char y )
{
	uchar Xaddr;
	uchar Yaddr;
	uchar *lcd_dot;
	if(x > 15)
	{
		return;
	}
	lcd_dot = lcd_12864_ascii8_code[ASCII - 32];
	if (y < 4)
	{
		Xaddr = x / 2 + 0x80;
		Yaddr = y * 8 + 0x80;
	}
	else
	{
		Xaddr = x / 2 + 0x88;
		Yaddr = (y - 4) * 8 + 0x80;
	}

	uchar j;
	uchar k = 0;
	//Write_Cmd(0x34); //使用扩展指令集，关闭绘图显示
	for (j = 0; j < 8; j++)
	{
		_lcd_12864_write_cmd(Yaddr++); //Y地址
		_lcd_12864_write_cmd(Xaddr); //X地址
		if (x % 2 == 1)
		{
			_lcd_12864_read_data();
		}
		_lcd_12864_write_data(lcd_dot[k++]);
	}
// 	Write_Cmd(0x36); //打开绘图显示
// 	Write_Cmd(0x30);  //回到基本指令集模式
}

void _lcd_12864_clear_gdram()
{
	uchar i, j, k;

	//Write_Cmd(0x34); //打开扩展指令集
	i = 0x80;
	for (j = 0; j < 32; j++)
	{
		_lcd_12864_write_cmd(i++);
		_lcd_12864_write_cmd(0x80);
		for (k = 0; k < 16; k++)
		{
			_lcd_12864_write_data(0x00);
		}
	}
	i = 0x80;
	for (j = 0; j < 32; j++)
	{
		_lcd_12864_write_cmd(i++);
		_lcd_12864_write_cmd(0x88);
		for (k = 0; k < 16; k++)
		{
			_lcd_12864_write_data(0x00);
		}
	}
	//Write_Cmd(0x30); //回到基本指令集
}


void _lcd_12864_delay(void) {
	__delay_cycles(1000);
}

void _lcd_12864_write_cmd(uchar cmd) {
	uchar lcdtemp = 0;

	LCD_RS_L;
	LCD_RW_H;
	LCD_DataIn;
	do //判忙
	{
		LCD_EN_H;
		_NOP();
		lcdtemp = LCD2MCU_Data;
		LCD_EN_L;

	} while (lcdtemp & 0x80);

	LCD_DataOut;
	LCD_RW_L;
	MCU2LCD_Data = cmd;
	LCD_EN_H;
	_NOP();
	LCD_EN_L;
}

void _lcd_12864_write_data(uchar dat) {
	uchar lcdtemp = 0;

	LCD_RS_L;
	LCD_RW_H;
	LCD_DataIn;
	do //判忙
	{
		LCD_EN_H;
		_NOP();
		lcdtemp = LCD2MCU_Data;
		LCD_EN_L;
	} while (lcdtemp & 0x80);

	LCD_DataOut;
	LCD_RS_H;
	LCD_RW_L;

	MCU2LCD_Data = dat;
	LCD_EN_H;
	_NOP();
	LCD_EN_L;
}

uchar _lcd_12864_read_data() {
	uchar data = 0;

	LCD_RS_L;
	LCD_RW_H;
	LCD_DataIn;
	do //判忙
	{
		LCD_EN_H;
		_NOP();
		data = LCD2MCU_Data;
		LCD_EN_L;
	} while (data & 0x80);
	data = 0xff;
	//LCD_DataIn;
	LCD_RS_H;
	LCD_RW_H;
	LCD_EN_L;
	LCD_EN_H;
	data = LCD2MCU_Data;
	LCD_EN_L;
	//_NOP();
	// LCD_EN_L;
	return data;
}

