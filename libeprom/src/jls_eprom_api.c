/*
*   JSL D-NOW LIB for libeprom     
*   Author: Shengjia.zhu           
*   Date: Oct 24, 2012              
*/

#include "jls_common.h"
#include "jls_eprom_api.h"
#include "jls_eprom.h"
#include "jls_eprom_flash.h"
#include "jls_common.h"
#include <string.h>
unsigned int JLS_EPROM_InterruptVectors[256];
boolen eprom_write_word( u8 pos, u16 val )
{
	EPROM_FLASH_ReadSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	EPROM_FLASH_EraseSEG((u16 *)EPROM_BEGIN_ADDR);
	JLS_EPROM_InterruptVectors[pos] = val;
	EPROM_FLASH_WriteSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	return TURE;
}

u16 eprom_read_word( u8 pos )
{
	u16* addr = ((u16 *)EPROM_BEGIN_ADDR) + pos;
	u16 return_date;
	EPROM_FLASH_Readw(addr, &return_date);
	return return_date;
}

boolen eprom_write_char( u16 pos, u8 val )
{
	if( pos > 511 )
	{
		return FALSE;
	}
	EPROM_FLASH_ReadSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	EPROM_FLASH_EraseSEG((u16 *)EPROM_BEGIN_ADDR);
	u8 *u8arry = (u8 *)JLS_EPROM_InterruptVectors;
	memcpy( u8arry+pos, &val, 1);
	EPROM_FLASH_WriteSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	return TURE;
}

u8 eprom_read_char( u16 pos )
{
	if( pos > 511 )
	{
		return FALSE;
	}
	u8* addr = ((u8 *)EPROM_BEGIN_ADDR) + pos;
	u8 return_date;
	EPROM_FLASH_Readc(addr, &return_date);
	return return_date;
}

boolen eprom_write_buf( u16 begin, u8* buf, u16 len )
{
	if( begin + len > 511 )
	{
		return FALSE;
	}
	EPROM_FLASH_ReadSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	EPROM_FLASH_EraseSEG((u16 *)EPROM_BEGIN_ADDR);
	u8 *u8arry = (u8 *)JLS_EPROM_InterruptVectors;
	memcpy( u8arry+begin, buf, len);
	EPROM_FLASH_WriteSEG( (u16 *)EPROM_BEGIN_ADDR, JLS_EPROM_InterruptVectors );
	return TURE;
}

boolen eprom_read_buf( u16 begin, u8* buf, u16 len )
{
	if( begin + len > 511 )
	{
		return FALSE;
	}
	u8* addr = ((u8 *)EPROM_BEGIN_ADDR) + begin;
	EPROM_FLASH_ReadBuf(addr,buf,len);
	return TURE;
}
