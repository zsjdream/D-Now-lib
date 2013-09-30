/*
*   JSL D-NOW LIB for liblcd_12864  *
*   Author: Shengjia.zhu           *
*   Date: Nov 3, 2012               *
*/

#ifndef JLS_LCD_12864_H_
#define JLS_LCD_12864_H_
#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_common.h"
#define LCD_DataIn    P4DIR=0x00    //数据口方向设置为输入
#define LCD_DataOut   P4DIR=0xff    //数据口方向设置为输出
#define LCD2MCU_Data  P4IN
#define MCU2LCD_Data  P4OUT
#define LCD_CMDOut    P3DIR|=0xe0     //P3口的高二位设置为输出

#define LCD_RS_H      P3OUT|=0x20      //P3.5
#define LCD_RS_L      P3OUT&=0xdf     //P3.5
#define LCD_RW_H      P3OUT|=0x40      //P3.6
#define LCD_RW_L      P3OUT&=0xbf     //P3.6
#define LCD_EN_H      P3OUT|=0x80      //P3.7
#define LCD_EN_L      P3OUT&=0x7f     //P3.7

void _lcd_12864_delay(void);
void _lcd_12864_write_cmd(uchar cmd);
void _lcd_12864_write_data(uchar dat);
uchar _lcd_12864_read_data();
void _lcd_12864_clear_gdram();
void _lcd_12864_display_ascii(uchar ch, uchar x, uchar y);
void _lcd_12864_display_ascii8(uchar ch, uchar x, uchar y);
struct _lcd_12864_bar_parm
{
	u16 cur_val;
	u16 max_num;
	u8 y_pos;
};

#endif /* JLS_LCD_12864_H_ */
