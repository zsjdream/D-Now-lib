/*
*   JSL D-NOW LIB for libeprom     
*   Author: Shengjia.zhu           
*   Date: Oct 24, 2012              
*/


#ifndef JLS_EPROM_FLASH_H_
#define JLS_EPROM_FLASH_H_

void EPROM_FLASH_Readw( unsigned int *Address, unsigned int *buf );
void EPROM_FLASH_Readc( unsigned char *Address, unsigned char *buf );
void EPROM_FLASH_Writew(unsigned int *Address,unsigned int nValue);
void EPROM_FLASH_EraseSEG(unsigned int *Address);
void EPROM_FLASH_ReadSEG(unsigned int *Address, unsigned int *buffer );
void EPROM_FLASH_WriteSEG(unsigned int *Address, unsigned int *buffer );
void EPROM_FLASH_ReadBuf( unsigned char *Address, unsigned char *buffer, unsigned int len );


#endif /* JLS_EPROM_FLASH_H_ */
