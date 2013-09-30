/*
 *   JSL D-NOW LIB common code      *
 *   Author: Shengjia.zhu           *
 *   Date: 2012/10/15               *
 */

#ifndef __JSL_COMMON__H__
#define __JSL_COMMON__H__

#define uchar unsigned char
#define u8 unsigned char
#define uint unsigned int
#define u16 unsigned int
#define ulong unsigned long
#define u32 unsigned long

/* Bootloader Evn */
#define	BL_EVN_VERSION		0
#define BL_EVN_SERIALHANDLE	1

#define BootEnv_Addr	0xF7F0
#define EnableInterrupt	__enable_interrupt()
#define DisableInterrupt	__disable_interrupt()

#define reg_readc( base, off )            (*(uchar *)(base+off))

#define reg_readw( base, off )            (*(uint *)(base+off))

#define reg_readw_l( base, off )          (uchar)(*(uint *)(base+off)&0x00ff)

#define reg_readw_h( base, off )          (uchar)(*(uint *)(base+off)>>8)

#define reg_writec( base, off, val )      *(uchar *)(base+off) = val

#define reg_writew( base, off, val )      *(uint *)(base+off) = val

#define reg_writew_l( base, off, val )    *(uint *)(base+off) = (*(uint *)(base+off)&0xff00) + (uint)val

#define reg_writew_h( base, off, val )    *(uint *)(base+off) = *(uint *)(base+off)&0x00ff + ((uint)val<<8)

#define reg_setc( base, off, val )        *(uchar *)(base+off) |= val

#define reg_setw( base, off, val )        *(uint *)(base+off) |= val

#define reg_setw_l( base, off, val )      *(uint *)(base+off) |= (uint)val

#define reg_setw_h( base, off, val )      *(uint *)(base+off) |= (uint)val<<8

#define reg_clearc( base, off, val )        *(uchar *)(base+off) &= ~val

#define reg_clearw( base, off, val )        *(uint *)(base+off) &= ~val

#define reg_clearw_l( base, off, val )      *(uint *)(base+off) &= ~((uint)val)

#define reg_clearw_h( base, off, val )      *(uint *)(base+off) &= ~((uint)val<<8)

typedef void (*pcb)(uchar);

void FLL_Init(void);
void FLASH_Writew(unsigned int *Address, unsigned int nValue);
void delay_ms(u16 t);
void FLASH_Bootloader_ENV_Set( unsigned char Pos, unsigned int val);
u16 FLASH_Bootloader_ENV_Get( u8 Pos);
#endif
