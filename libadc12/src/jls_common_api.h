/*
 *   JSL D-NOW LIB for libeprom
 *   Author: Shengjia.zhu
 *   Date: Oct 24, 2012
 */

/* Do Not Edit This File !! */

#ifndef JLS_COMMON_API_H_
#define JLS_COMMON_API_H_

/* Type Define */
#define uchar unsigned char
#define u8 unsigned char
#define uint unsigned int
#define u16 unsigned int
#define ulong unsigned long
#define u32 unsigned long
#define boolen u8
#define TURE 1
#define FALSE 0

/* Interrupt */
#define EnableInterrupt	__enable_interrupt()
#define DisableInterrupt	__disable_interrupt()

typedef void (*icb)(u16*);
typedef void (*pcb)(uchar);
typedef void (*vcb)();

#endif /* JLS_COMMON_API_H_ */
