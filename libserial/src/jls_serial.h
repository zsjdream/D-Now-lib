/*
*   JSL D-NOW LIB for serial port  *
*   Author: Shengjia.zhu           *
*   Date: 2012/10/15               *
*/

#ifndef __SERIAL__H__
#define __SERIAL__H__

#define UARTREG(A,B,C) A##B##C
#define UCAREG(B,C) UARTREG(UCA,B,C)

/* offset of serial reg */
#define SERIAL_ICTL     0x1C  //  L:IE   H:IFG
//#define SERIAL_IE       0x1C
//#define SERIAL_IFG      0x1D
#define SERIAL_TXBUF    0x0E
#define SERIAL_RXBUF    0x0C
#define SERIAL_IV_0     0xFFF2
#define SERIAL_IV_1     0xFFDC
#define SERIAL_IV_2     0xFFE8
#define SERIAL_IV_3     0xFFD8

#define SERIAL_BASE_0   0x05C0
#define SERIAL_BASE_1   0x0600
#define SERIAL_BASE_2   0x0640
#define SERIAL_BASE_3   0x0680


#define serial_write_txbuf(base, val)  reg_writec( base, SERIAL_TXBUF, val )

#define serial_write_ie(base, val)  reg_writew_l( base, SERIAL_ICTL, val )



#define serial_set_ie(base, val)  reg_setw_l( base, SERIAL_ICTL, val )

#define serial_clear_ie(base, val)  reg_clearw_l( base, SERIAL_ICTL, val )

#define serial_read_ie(base)  reg_readw_l( base, SERIAL_ICTL )

#define serial_read_ifg(base)  reg_readw_h( base, SERIAL_ICTL)

#define serial_read_rxbuf(base)  reg_readc( base, SERIAL_RXBUF)

/*#define UCAIE(reg_base) DEFCW(UCAIE##reg_base, reg_base); UCAIE##reg_base_L

#define UCAIFG(reg_base) DEFCW(UCAIE##reg_base, reg_base); UCAIE##reg_base_H*/
        



#define SERIAL_IE()

/* algorithm:  n = clk/baudrate,  
               BRx = INT(n), 
               UCBRS = ROUND((n - INT(n))*8) 
*/

#define BaudRate115200( id )						\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x08;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) |= UCBRS_6 + UCBRF_0

#define BaudRate57600( id )						\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x11;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) |= UCBRS_3 + UCBRF_0

#define BaudRate38400( id )						\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x1A;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) |= UCBRS_0 + UCBRF_0

#define BaudRate19200( id )						\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x34;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) |= UCBRS_0 + UCBRF_0

#define BaudRate9600( id )						\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x68;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) |= UCBRS_1 + UCBRF_0


#define BaudRate4800( id )					\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0xD0;							\
	UCAREG(id,BR1) = 0x00;							\
	UCAREG(id,MCTL) = UCBRS_2+UCBRF_0

#define BaudRate2400( id )					\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0xA0;							\
	UCAREG(id,BR1) = 0x01;							\
	UCAREG(id,MCTL) = UCBRS_5+UCBRF_0


#define BaudRate1200( id )					\
	UCAREG(id,CTL1) |= UCSSEL_1;					\
	UCAREG(id,BR0) = 0x41;							\
	UCAREG(id,BR1) = 0x03;							\
	UCAREG(id,MCTL) = UCBRS_2+UCBRF_0
          
#endif
