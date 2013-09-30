/*
*   JSL D-NOW LIB for libclock  *
*   Author: Shengjia.zhu           *
*   Date: Oct 30, 2012               *
*/


/*
 * Change Log:
 * 	- 2012.10.30 Initial version.
 *
 *
 * */
#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_common.h"
#include "jls_clock_api.h"

void clock_init()
{
	P5SEL |= 0x0C; // Port select XT2
	UCSCTL6 |= XT1OFF;
	UCSCTL6 &= ~XT2OFF; // Ena¡Á¡Áe XT2
	UCSCTL3 = 0;
	UCSCTL3 |= SELREF_2 + FLLREFDIV__1;
	UCSCTL2 = 0;
	UCSCTL2 |= 31 + FLLD__4;
        if( (UCSCTL4 & 0x0700) == 0 )
        {
          UCSCTL4 &= ~0x0700;
          UCSCTL4 |= 0x0500;
        }
        do
	{
                UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG; // Clear fault flags
		__delay_cycles(100000); // Delay for Osc to stabilize
	}
	while ((SFRIFG1 & (~(0XFFFD)))>>1 == 1); // Test oscillator fault flag
}

void clock_clear_clksel( u8 offset )
{
	UCSCTL4 &= ~(0x007 << offset);
	UCSCTL5 &= ~(0x007 << offset);
}
/** Decimal frequency 1M = 1000K, 1K = 1000Hz **/

  /* Use clock source XT2CLK */
void clock_set_to_16M_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;

}

void clock_set_to_8M_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;
	UCSCTL5 |= 0x001 << offset;
}

void clock_set_to_4M_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;
	UCSCTL5 |= 0x002 << offset;
}

void clock_set_to_2M_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;
	UCSCTL5 |= 0x003 << offset;
}

void clock_set_to_1M_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;
	UCSCTL5 |= 0x004 << offset;
}

void clock_set_to_500K_D( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x005 << offset;
	UCSCTL5 |= 0x005 << offset;
}

/* Hexadecimal frequency 1M = 1024K, 1K = 1024Hz */

    /* Use clock source DCOCLK */
void clock_set_to_4M( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x003 << offset;
}

void clock_set_to_2M( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x003 << offset;
	UCSCTL5 |= 0x001 << offset;
}

    /* Use clock source DCOCLKDIV */
void clock_set_to_1M( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x004 << offset;
}

void clock_set_to_512K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x004 << offset;
	UCSCTL5 |= 0x001 << offset;
}

void clock_set_to_256K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x004 << offset;
	UCSCTL5 |= 0x002 << offset;
}

void clock_set_to_128K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x004 << offset;
	UCSCTL5 |= 0x003 << offset;
}

void clock_set_to_64K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x004 << offset;
	UCSCTL5 |= 0x004 << offset;
}

/* Use clock source REFOCLK */
void clock_set_to_32K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
}
void clock_set_to_16K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
	UCSCTL5 |= 0x001 << offset;
}
void clock_set_to_8K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
	UCSCTL5 |= 0x002 << offset;
}

void clock_set_to_4K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
	UCSCTL5 |= 0x003 << offset;
}

void clock_set_to_2K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
	UCSCTL5 |= 0x004 << offset;
}

void clock_set_to_1K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x002 << offset;
	UCSCTL5 |= 0x005 << offset;
}
/* Use clock source VLOCLK */
void clock_set_to_10K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x001 << offset;
}
void clock_set_to_5K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x001 << offset;
	UCSCTL5 |= 0x001 << offset;
}
void clock_set_to_2p5K( u8 clock_type )
{
	u8 offset = clock_type*4;
	clock_clear_clksel(offset);
	UCSCTL4 |= 0x001 << offset;
	UCSCTL5 |= 0x002 << offset;
}

void clock_output_ACLK()
{
	P11SEL |= 0x01;
	P11DIR |= 0x01;
}

void clock_output_MCLK()
{
	P11SEL |= 0x02;
	P11DIR |= 0x02;
}

void clock_output_SMCLK()
{
	P11SEL |= 0x04;
	P11DIR |= 0x04;
}
