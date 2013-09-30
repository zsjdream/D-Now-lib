/*
*   JSL D-NOW LIB for libeprom     
*   Author: Shengjia.zhu           
*   Date: Oct 24, 2012              
*/


#ifndef JLS_EPROM_API_H_
#define JLS_EPROM_API_H_
#include "jls_common_api.h"
boolen eprom_write_word( u8 pos, u16 val );
u16 eprom_read_word( u8 pos );
boolen eprom_write_char( u16 pos, u8 val );
u8 eprom_read_char( u16 pos );
boolen eprom_write_buf( u16 begin, u8* buf, u16 len );
boolen eprom_read_buf( u16 begin, u8* buf, u16 len );
#endif /* JLS_EPROM_API_H_ */
