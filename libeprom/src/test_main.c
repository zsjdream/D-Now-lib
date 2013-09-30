/*
*   JSL D-NOW LIB for libeprom     
*   Author: Shengjia.zhu           
*   Date: Oct 24, 2012              
*/
#include "msp430f5438a.h"
#include "jls_eprom_api.h"
#include "jls_common_api.h"
u16 val;
u8 valc;

void main()
{
  
    WDTCTL = WDTPW + WDTHOLD;
    char buf[] = "zsjdream";
    eprom_write_word(0, 5632);
    eprom_write_word(16, 1234);
    eprom_write_char(500, 'a');
    eprom_write_char(510, 231);
    eprom_write_char(511, 1);
    val = eprom_read_word(16);
    val = eprom_read_word(0);
    val = eprom_read_word(254);
    val = eprom_read_word(255);
    valc = eprom_read_char(0);
    valc = eprom_read_char(1);
    valc = eprom_read_char(2);
    valc = eprom_read_char(31);
    valc = eprom_read_char(32);
    valc = eprom_read_char(33);
    valc = eprom_read_char(509);
  
    eprom_write_buf(501, buf, 7);
    eprom_read_buf(500,buf,7);
    valc = eprom_read_char(510);
    valc = eprom_read_char(511);
}


