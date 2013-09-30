/*
 *   JSL D-NOW LIB for liblcd_12864  *
 *   Author: Shengjia.zhu           *
 *   Date: Nov 3, 2012               *
 */

#ifndef JLS_LCD_12864_API_H_
#define JLS_LCD_12864_API_H_

void lcd_12864_display_clear(void);

void lcd_12864_display_string(uchar *string, uchar x, uint y);
void lcd_12864_display_string_tiny(uchar *string, uchar x, uchar y);

void lcd_12864_display_number(u32 Number, u8 x, u8 y, u16 integer, u8 decimal);
void lcd_12864_display_number_tiny(u32 Number, u8 x, u8 y, u16 integer,
		u8 decimal);

void lcd_12864_progress_bar(uint Num, uint Den, uchar y);

#endif /* JLS_LCD_12864_API_H_ */
