/*
 *   JSL D-NOW LIB for liblcd_12864  *
 *   Author: Shengjia.zhu           *
 *   Date: Nov 3, 2012               *
 */
#include "jls_common.h"
#include "jls_lcd_12864.h"
#include "jls_lcd_12864_api.h"
#include <string.h>


struct _lcd_12864_bar_parm jls_lcd_12864_bar_parms;

void lcd_12864_display_clear(void)
{
	LCD_CMDOut; //液晶控制端口设置为输出
	//Delay_Nms(100);
	_lcd_12864_write_cmd(0x30); //基本指令集
	_lcd_12864_delay();
	_lcd_12864_write_cmd(0x02); // 地址归位
	_lcd_12864_delay();
	_lcd_12864_write_cmd(0x0c); //整体显示打开,游标关闭
	_lcd_12864_delay();
	_lcd_12864_write_cmd(0x01); //清除显示
	_lcd_12864_delay();
	_lcd_12864_write_cmd(0x06); //游标右移
	_lcd_12864_delay();
	_lcd_12864_write_cmd(0x80); //设定显示的起始地址
	_lcd_12864_write_cmd(0x34); //使用扩展指令集，关闭绘图显示
	_lcd_12864_write_cmd(0x36); //打开绘图显示
	_lcd_12864_clear_gdram();
}

void lcd_12864_progress_bar(u16 Num, u16 Den, u8 Y)
{

	if( Num > Den )
	{
		return;
	}
	unsigned long DotNum = Num;

	if( (Num != 0)
			&& ( jls_lcd_12864_bar_parms.cur_val == Num )
			&& ( jls_lcd_12864_bar_parms.max_num == Den )
			&& ( jls_lcd_12864_bar_parms.y_pos == Y ) )
	{
		return;
	}
	jls_lcd_12864_bar_parms.cur_val = Num;
	jls_lcd_12864_bar_parms.max_num = Den;
	jls_lcd_12864_bar_parms.y_pos = Y;

	DotNum *= 112;
	DotNum /= Den;


	uint ByteNum = DotNum/8;
	uchar LastDate = 0xff << ( 8 - (DotNum%8) );
        uchar flag = 1;
	uchar Yaddr, Yaddr_Tmp;
	uchar Xaddr, Xaddr_Tmp;
	if( Y < 4 )
	{
		Yaddr_Tmp = Y*8 + 0x80 + 1;
		Xaddr_Tmp = 0x80;
	}
	else
	{
		Yaddr_Tmp = (Y-4)*8 + 0x80 + 1;
		Xaddr_Tmp = 0x88;
	}


	/*Draw the bar box*/
	Xaddr = Xaddr_Tmp;
	Yaddr =  Yaddr_Tmp - 1;
	_lcd_12864_write_cmd(Yaddr++); //Y地址
	_lcd_12864_write_cmd(Xaddr);
	_lcd_12864_read_data();
	_lcd_12864_write_data(0xff);
	for (int j = 0; j < 6; j++)
	{
		_lcd_12864_write_cmd(Yaddr++); //Y地址
		_lcd_12864_write_cmd(Xaddr);
		_lcd_12864_read_data();
		if ( DotNum >=8 )
		{
			_lcd_12864_write_data(0xff);
		}
		else
		{
			_lcd_12864_write_data(LastDate|0x80);
		}

	}
	_lcd_12864_write_cmd(Yaddr++); //Y地址
	_lcd_12864_write_cmd(Xaddr++);
	_lcd_12864_read_data();
	_lcd_12864_write_data(0xff);
	Yaddr =  Yaddr_Tmp - 1;
	for( int i = 0; i < 6; i++ )
	{
		_lcd_12864_write_cmd(Yaddr); //Y地址
		_lcd_12864_write_cmd(Xaddr);
		_lcd_12864_write_data(0xff);
		_lcd_12864_write_data(0xff);
		_lcd_12864_write_cmd(Yaddr+7); //Y地址
		_lcd_12864_write_cmd(Xaddr++);
		_lcd_12864_write_data(0xff);
		_lcd_12864_write_data(0xff);
	}

	Yaddr =  Yaddr_Tmp - 1;
	_lcd_12864_write_cmd(Yaddr++); //Y地址
	_lcd_12864_write_cmd(Xaddr);
	_lcd_12864_write_data(0xff);
	for (int j = 0; j < 6; j++)
	{
		_lcd_12864_write_cmd(Yaddr++); //Y地址
		_lcd_12864_write_cmd(Xaddr);
		if( ByteNum >= 13 )
		{
			_lcd_12864_write_data(LastDate|0x01);
		}
		else
		{
			_lcd_12864_write_data(0x01);
		}

	}
	_lcd_12864_write_cmd(Yaddr++); //Y地址
	_lcd_12864_write_cmd(Xaddr++);
	_lcd_12864_write_data(0xff);

	/*Draw val*/
	Xaddr = Xaddr_Tmp;
	if( ByteNum != 0 )
	{
		Yaddr =  Yaddr_Tmp;
		for (int j = 0; j < 6; j++)
		{
			_lcd_12864_write_cmd(Yaddr++); //Y地址
			_lcd_12864_write_cmd(Xaddr);
			_lcd_12864_read_data();
			_lcd_12864_write_data(0xff); //X地址
		}

		--ByteNum;
        Xaddr ++;
	}
    else
    {
      if(LastDate!=0)
      {
		  Yaddr =  Yaddr_Tmp;
		  for (int j = 0; j < 6; j++)
		  {
			  _lcd_12864_write_cmd(Yaddr++); //Y地址
			  _lcd_12864_write_cmd(Xaddr); //X地址
			  _lcd_12864_read_data();
			  _lcd_12864_write_data(LastDate);
		  }
      }
      flag = 0;
    }
    if(flag)
    {
      while( ByteNum >= 2 )
      {

          ByteNum -=2;
          Yaddr =  Yaddr_Tmp;
          for (int j = 0; j < 6; j++)
          {
              _lcd_12864_write_cmd(Yaddr++); //Y地址
              _lcd_12864_write_cmd(Xaddr); //X地址
              _lcd_12864_write_data(0xff);
              _lcd_12864_write_data(0xff);
          }
          Xaddr ++;
      }
      if(ByteNum)
      {

          Yaddr =  Yaddr_Tmp;
          for (int j = 0; j < 6; j++)
          {
              _lcd_12864_write_cmd(Yaddr++); //Y地址
              _lcd_12864_write_cmd(Xaddr); //X地址
              _lcd_12864_write_data(0xff);
              _lcd_12864_write_data(LastDate);
          }
      }
      else
      {
          Yaddr =  Yaddr_Tmp;
          for (int j = 0; j < 6; j++)
          {
              _lcd_12864_write_cmd(Yaddr++); //Y地址
              _lcd_12864_write_cmd(Xaddr); //X地址
              if((Xaddr == 0x87) || (Xaddr == 0x8e))
              {
            	  LastDate |= 0x01;
              }
              _lcd_12864_write_data(LastDate);
              _lcd_12864_write_data(0);
          }
      }
    }

	/*Fill space*/
	if( (Xaddr == 0x87) || (Xaddr == 0x8f) )
	{
		return;
	}
	Xaddr ++;
	while( (Xaddr != 0x87) && (Xaddr != 0x8f) )
	{

		Yaddr =  Yaddr_Tmp;
		for (int j = 0; j < 6; j++)
		{
			_lcd_12864_write_cmd(Yaddr++); //Y地址
			_lcd_12864_write_cmd(Xaddr); //X地址
			_lcd_12864_write_data(0);
			_lcd_12864_write_data(0);
		}
		Xaddr ++;
	}


	Yaddr =  Yaddr_Tmp - 1;
	_lcd_12864_write_cmd(Yaddr++); //Y地址
	_lcd_12864_write_cmd(Xaddr);
	_lcd_12864_write_data(0xff);
	for (int j = 0; j < 6; j++)
	{
		_lcd_12864_write_cmd(Yaddr++); //Y地址
		_lcd_12864_write_cmd(Xaddr);
		_lcd_12864_write_data(0x01); //X地址
	}
	_lcd_12864_write_cmd(Yaddr); //Y地址
	_lcd_12864_write_cmd(Xaddr);
	_lcd_12864_write_data(0xff);
}




void lcd_12864_display_number(u32 Number, u8 x, u8 y,
		u16 integer, u8 decimal)
{
	u8 DispNum, Lenth;
	x += (integer + decimal);
	for (Lenth = decimal; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii(DispNum, x, y);
		x -= 1;
		Number = Number / 10;
	}
	_lcd_12864_display_ascii('.', x, y);
	x -= 1;
	for (Lenth = integer; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii(DispNum, x, y);
		x -= 1;
		Number = Number / 10;
	}
}

void lcd_12864_display_number_tiny(u32 Number, u8 x, u8 y,
		u16 integer, u8 decimal)
{
	u8 DispNum, Lenth;
	x += (integer + decimal);
	for (Lenth = decimal; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii8(DispNum, x, y);
		x -= 1;
		Number = Number / 10;
	}
	_lcd_12864_display_ascii8('.', x, y);
	x -= 1;
	for (Lenth = integer; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii8(DispNum, x, y);
		x -= 1;
		Number = Number / 10;
	}
}

void Display_Decimal8(unsigned long int Number, char X, unsigned char Y,
		unsigned char INT, unsigned char DEC)
{
	uchar DispNum, Lenth;
	X += 6 * (INT + DEC);
	for (Lenth = DEC; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii8(DispNum, X, Y);
		X -= 6;
		Number = Number / 10;
	}
	_lcd_12864_display_ascii8('.', X, Y);
	X -= 6;
	for (Lenth = INT; Lenth > 0; Lenth--)
	{
		DispNum = Number % 10 + 0x30;
		_lcd_12864_display_ascii8(DispNum, X, Y);
		X -= 6;
		Number = Number / 10;
	}
}



void lcd_12864_display_string( uchar *string, uchar x, uint y )
{
	uchar addr;
	uchar i, len;
	u8 space = ' ';
	switch (y)
	{
	case 0:
		addr = 0x80 + x/2;
		break;
	case 1:
		addr = 0x90 + x/2;
		break;
	case 2:
		addr = 0x88 + x/2;
		break;
	case 3:
		addr = 0x98 + x/2;
		break;
	}
	len = strlen((char *) string);
	if (len + x > 16)
	{
		len = 16 - x;
	}
	_lcd_12864_write_cmd(0x30);
	_lcd_12864_write_cmd(addr);
	if(x % 2)
	{
		_lcd_12864_read_data();
	}
	for (i = 0; i < len; i++)
	{
        /* If the next u16 is a Hanzi. */
		if( (i+x)%2 )
		{
			if( ( *string > 127) && ( *(string-1) <= 127) )
			{
				_lcd_12864_write_data(space);
				++ i;
				if( x + len < 16)
				{
					++len;
				}
			}
		}

		_lcd_12864_write_data(*(string++));

	}
	_lcd_12864_write_cmd(0x34);
	_lcd_12864_write_cmd(0x36); //open draw display
}

void lcd_12864_display_string_tiny(uchar *string, uchar x, uchar y)
{
	uchar len;
	len = strlen((char *) string);
	if( len + x > 16 )
	{
		len = 16 - x;
	}
	for (int i = 0; i < len; i++)
	{
		_lcd_12864_display_ascii8(*(string + i), x+i, y);
	}
}
