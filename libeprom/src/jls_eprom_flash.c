/*
*   JSL D-NOW LIB for libeprom     
*   Author: Shengjia.zhu           
*   Date: Oct 24, 2012              
*/
#include "msp430f5438a.h"
#include <string.h>
void EPROM_FLASH_Readw( unsigned int *Address, unsigned int *buf )
{
        memcpy( buf, Address, 2 );
        //*buf = *Address;
}

void EPROM_FLASH_Readc( unsigned char *Address, unsigned char *buf )
{
        memcpy( buf, Address, 1 );
        //*buf = *Address;
}

void EPROM_FLASH_Writew(unsigned int *Address,unsigned int nValue)
{
	FCTL1=FWKEY+WRT;							// WRT = 1
	FCTL3=FWKEY;								// LOCK = 0
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
	*Address=nValue;
	FCTL1=FWKEY;								// WRT = 0
	FCTL3=FWKEY+LOCK;							// LOCK = 1
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
}

void EPROM_FLASH_EraseSEG(unsigned int *Address)
{
	_DINT();
	FCTL3=FWKEY;								// LOCK = 0
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
	FCTL1=FWKEY+ERASE;							// ERASE=1
	*Address=0;									// Write to the SEGment
	FCTL1=FWKEY;
	FCTL3=FWKEY+LOCK;
	while((FCTL3&BUSY)==BUSY);					// Waitint for FLASH
	_EINT();
}

void EPROM_FLASH_ReadSEG(unsigned int *Address, unsigned int *buffer )
{
    memcpy( buffer, Address, 0x200 );
}

void EPROM_FLASH_WriteSEG(unsigned int *Address, unsigned int *buffer )
{
    unsigned int index;
    for( index = 0; index < 0x100; ++index )
    {
        EPROM_FLASH_Writew( Address + index, *(buffer + index) );
    }
}

void EPROM_FLASH_ReadBuf( unsigned char *Address, unsigned char *buffer, unsigned int len )
{
	memcpy( buffer, Address, len );
}

