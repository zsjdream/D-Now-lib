/*
*   JSL D-NOW LIB for libwdt  *
*   Author: Shengjia.zhu           *
*   Date: Nov 1, 2012               *
*/
#include "msp430f5438.h"
#include <msp430f5438.h>
#include "jls_common_api.h"
#include "jls_wdt_api.h"


void wdt_set_enable( boolen en )
{
	WDTCTL=((WDTCTL & 0X007F) + 0x5A00) | (((~en) & 0X0001) <<7);
}

void wdt_keep_alive()
{
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((1 & 0X0001) <<3);
}

/* Use VLOCLK ¡Ö 9.8 * 1024 Hz * */
void wdt_set_timeout_to_59h26m35s()//2G
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((2 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3); // Do nothing whit the conter
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((0 & 0X0007) <<0); //Select WDTIS
}
void wdt_set_timeout_to_3h42m55s() //128M
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((2 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((1 & 0X0007) <<0); //Select WDTIS
}
void wdt_set_timeout_to_13m56s() //8192K
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((2 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((2 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_52s() // 512k
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((2 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((3 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_3p2s() //32k
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((2 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((4 & 0X0007) <<0); //Select WDTIS
}


/* Use ACLK = 1000000 Hz */

void wdt_set_timeout_to_35m47s() //2G
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((0 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_2m14s() //128M
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((1 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_8p4s() //8192k
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((2 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_524p3ms() //512k
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((3 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_32p8ms() // 32k
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((4 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_8p2ms()
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((5 & 0X0007) <<0); //Select WDTIS
}

void wdt_set_timeout_to_512us()
{
	WDTCTL=((WDTCTL & 0X009F) + 0x5A00) | ((1 & 0X0003) <<5); // Set clock source to VLOCLK
	WDTCTL=((WDTCTL & 0X00F7) + 0x5A00) | ((0 & 0X0001) <<3);
	WDTCTL=((WDTCTL & 0X00F8) + 0x5A00) | ((6 & 0X0007) <<0); //Select WDTIS
}

