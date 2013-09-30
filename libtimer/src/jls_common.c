/*
*   JSL D-NOW LIB common code      *
*   Author: Shengjia.zhu           *
*   Date: 2012/10/15               *
*/

#include "msp430f5438.h"
#include "jls_common.h"
void FLL_Init(void)
{
	PMMCTL0 = PMMPW + PMMCOREV_3;
	SVSMHCTL = SVSHRVL_3 + SVSMHRRL_3;
	P5SEL |= BIT2 + BIT3;
	UCSCTL6 &= ~XT2OFF;
	UCSCTL3 |= SELREF_2;
	UCSCTL4 |= SELA_2;
	do 
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
		SFRIFG1 &= ~OFIFG;
	}
	while (SFRIFG1&OFIFG);
	UCSCTL6 |= XT2DRIVE_3;
	UCSCTL4 = SELS__XT2CLK + SELM__XT2CLK;
}
void FLASH_Writew(unsigned int *Address,unsigned int nValue)
{
	FCTL1=FWKEY+WRT;							// WRT = 1
	FCTL3=FWKEY;								// LOCK = 0
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
	*Address=nValue;
	FCTL1=FWKEY;								// WRT = 0
	FCTL3=FWKEY+LOCK;							// LOCK = 1
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
}
void delay_ms(u16 t)
{
        u8 j;
	u16 i;
	for(i=0;i<t;i++)
		for(j=0;j<200;j++);
}
