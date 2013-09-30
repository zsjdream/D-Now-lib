/*
 *   JSL D-NOW LIB for serial port  *
 *   Author: Shengjia.zhu           *
 *   Date: 2012/10/15               *
 */
/*
 * Change Log:
 * 	- 10.29	use ACLK for calculate baudrate.
* 			when the  baudrate < 9600 select ACLK to 32k(32*1024 Hz);
* 			baudrate >= 9600 select ACLK to 1M(1024*1024 Hz).
*
 *	- 10.30 use ACLK for calculate baudrate.
 *			always set ACLK to 1M(1000*1000 Hz), re-calculate the BR0 BR1 BRS for all support baudrate.
 *
 *
 *
 *
 * */





#include "msp430x54x.h"
#include "jls_common.h"
#include "jls_serial.h"
#include "jls_serial_api.h"
#include <string.h>

/* UART INIT */

void set_ACLK_to_1M()
{
	P5SEL |= 0x0C; // Port select XT2
	UCSCTL6 &= ~XT2OFF; // Ena¡Á¡Áe XT2
	UCSCTL3 = 0;
	UCSCTL3 |= SELREF_2 + FLLREFDIV__1;
	UCSCTL2 = 0;
	UCSCTL2 |= 31 + FLLD__1;

	UCSCTL4 &= ~0x0700;
	UCSCTL4 |= SELA_5;
        UCSCTL5 &= ~0x0700;
	UCSCTL5 |= DIVA__16;
        
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG; // Clear fault flags
		__delay_cycles(100000); // Delay for Osc to stabilize
	} while ((SFRIFG1 & (~(0XFFFD))) >> 1 == 1); // Test oscillator fault flag
	P11SEL = 0x07;
	P11DIR = 0x07;
}


/* Port0 */
u16 _serial_init_0_1200()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate1200(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_2400()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate2400(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_4800()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate4800(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_9600()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate9600(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_19200()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate19200(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_38400()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate38400(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_57600()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate57600(0);
	UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

u16 _serial_init_0_115200()
{
	set_ACLK_to_1M();
	P3SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P3DIR |= 0x10;
	P3DIR &= ~0x20;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate115200(0);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_0;
}

/* Port1 */u16 _serial_init_1_1200()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate1200(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_2400()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate2400(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_4800()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate4800(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_9600()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate9600(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_19200()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate19200(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_38400()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate38400(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_57600()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate57600(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

u16 _serial_init_1_115200()
{
	set_ACLK_to_1M();
	P5SEL |= 0xC0; // P3.4,5 = USCI_A0 TXD/RXD
	P5DIR |= 0x40;
	P5DIR &= ~0x80;
	UCA1CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate115200(1);
	UCA1CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_1;
}

/* Port2 */
u16 _serial_init_2_1200()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate1200(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_2400()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate2400(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_4800()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate4800(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_9600()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate9600(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_19200()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate19200(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_38400()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate38400(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_57600()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate57600(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

u16 _serial_init_2_115200()
{
	set_ACLK_to_1M();
	P9SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P9DIR |= 0x10;
	P9DIR &= ~0x20;
	UCA2CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate115200(2);
	UCA2CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_2;
}

/* Port3 */

u16 _serial_init_3_1200()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate1200(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_2400()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate2400(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_4800()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate4800(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_9600()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate9600(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_19200()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate19200(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_38400()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate38400(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_57600()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate57600(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}

u16 _serial_init_3_115200()
{
	set_ACLK_to_1M();
	P10SEL |= 0x30; // P3.4,5 = USCI_A0 TXD/RXD
	P10DIR |= 0x10;
	P10DIR &= ~0x20;
	UCA3CTL1 |= UCSWRST; // **Put state machine in reset**
	BaudRate115200(3);
	UCA3CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
	return SERIAL_BASE_3;
}


void serial_deinit(u16 handle)
{
	//serial_write_ie(handle,0x00);					// Disable USCI_A0 RX interrupt
	serial_clear_ie(handle, UCRXIE);
}

void serial_send_byte(u16 handle, u8 val)
{
	//uint reg_base = handle;
	while (!(serial_read_ifg(handle) & UCTXIFG))
		; // USCI_A0 TX buffer ready?
	serial_write_txbuf( handle, val);
}

void serial_send_str(u16 handle, uchar *str)
{
	while (*str)
	{
		serial_send_byte(handle, *str);
		str++;
	}
}

void serial_send_buf(u16 handle, uchar *buf, u16 len)
{
	while (len--)
	{
		serial_send_byte(handle, *buf);
		buf++;
	}
}

u8 serial_receive_byte(u16 handle)
{
	u8 ie_val = serial_read_ie(handle);
	u8 ch;
	serial_clear_ie(handle, UCRXIE);
	while (!(serial_read_ifg(handle) & UCRXIFG))
		;
	ch = serial_read_rxbuf(handle);
	serial_write_ie(handle, ie_val);
	return ch;
}

u16 serial_receive_buf(u16 handle, uchar *buf, u16 len)
{
	u16 index;
	u8 ie_val = serial_read_ie(handle);
	serial_clear_ie(handle, UCRXIE);
	for (index = 0; index < len; ++index)
	{
		while (!(serial_read_ifg(handle) & UCRXIFG))
			;
		buf[index] = serial_read_rxbuf(handle);
	}serial_write_ie(handle, ie_val);
	return index;
}
u16 serial_receive_str(u16 handle, uchar *buf)
{
	u16 index;
	u8 ie_val = serial_read_ie(handle);
	serial_clear_ie(handle, UCRXIE);
	for (index = 0;; ++index)
	{
		while (!(serial_read_ifg(handle) & UCRXIFG))
			;
		buf[index] = serial_read_rxbuf(handle);
		if (!buf[index])
		{
			serial_write_ie(handle, ie_val);
			return index - 1;
		}
	}
}

//with wait time out
u16 serial_receive_buf_wt(u16 handle, uchar *buf, u16 len, u16 timeout)
{
	u16 index;
	u8 ie_val = serial_read_ie(handle);
	serial_clear_ie(handle, UCRXIE);
	for (index = 0; index < len; ++index)
	{
		u32 tv = (u32) (timeout * 65.535);
		while (!(serial_read_ifg(handle) & UCRXIFG))
		{
			if (!(--tv))
			{
				goto END;
			}
		}
		buf[index] = serial_read_rxbuf(handle);
	}
	END:
	serial_write_ie(handle, ie_val);
	return index;
}

u16 serial_receive_str_wt(u16 handle, uchar *buf, u16 timeout)
{
	u16 index;
	u8 ie_val = serial_read_ie(handle);
	serial_clear_ie(handle, UCRXIE);
	for (index = 0;; ++index)
	{
		u32 tv = (u32) (timeout * 65.535);
		while (!(serial_read_ifg(handle) & UCRXIFG))
		{
			if (!(--tv))
			{
				goto END;
			}
		}
		buf[index] = serial_read_rxbuf(handle);
		if (!buf[index])
		{
			goto END;
		}
	}
	END:
	serial_write_ie(handle, ie_val);
	return index;
}

u16 hd;
//pcb call_fun;
void (*serial_isr_call_back_0)(uchar recv_char);
void (*serial_isr_call_back_1)(uchar recv_char);
void (*serial_isr_call_back_2)(uchar recv_char);
void (*serial_isr_call_back_3)(uchar recv_char);

__interrupt void serial_port_isr_0(void)
{
	unsigned char temp;
	switch (__even_in_range(UCA0IV, 4))
	{
	case 0:
		break; // Vector 0 - no interrupt
	case 2: // Vector 2 - RXIFG
		while (!(UCA0IFG & UCTXIFG))
			; // USCI_A0 TX buffer ready?

		temp = UCA0RXBUF;
		serial_isr_call_back_0(temp);
		break;
	case 4:
		break; // Vector 4 - TXIFG
	default:
		break;
	}
	// return fun;
}

__interrupt void serial_port_isr_1(void)
{
	unsigned char temp;
	switch (__even_in_range(UCA1IV, 4))
	{
	case 0:
		break; // Vector 0 - no interrupt
	case 2: // Vector 2 - RXIFG
		while (!(UCA1IFG & UCTXIFG))
			; // USCI_A0 TX buffer ready?

		temp = UCA1RXBUF;
		serial_isr_call_back_1(temp);
		break;
	case 4:
		break; // Vector 4 - TXIFG
	default:
		break;
	}
	// return fun;
}

__interrupt void serial_port_isr_2(void)
{
	unsigned char temp;
	switch (__even_in_range(UCA2IV, 4))
	{
	case 0:
		break; // Vector 0 - no interrupt
	case 2: // Vector 2 - RXIFG
		while (!(UCA2IFG & UCTXIFG))
			; // USCI_A0 TX buffer ready?

		temp = UCA2RXBUF;
		serial_isr_call_back_2(temp);
		break;
	case 4:
		break; // Vector 4 - TXIFG
	default:
		break;
	}
	// return fun;
}

__interrupt void serial_port_isr_3(void)
{
	unsigned char temp;
	switch (__even_in_range(UCA3IV, 4))
	{
	case 0:
		break; // Vector 0 - no interrupt
	case 2: // Vector 2 - RXIFG
		while (!(UCA3IFG & UCTXIFG))
			; // USCI_A0 TX buffer ready?

		temp = UCA3RXBUF;
		serial_isr_call_back_3(temp);
		break;
	case 4:
		break; // Vector 4 - TXIFG
	default:
		break;
	}
	// return fun;
}
u8 get_port_num(u16 handle)
{
	return (u8) ((handle - SERIAL_BASE_0) / 0x40);
}
void setup_serial_isr(u16 handle, pcb call_back_fun)
{
	/*if( handle ==  SERIAL_BASE_0 )
	 {
	 isr_call_back_0 = call_back_fun;
	 FLASH_Writew( (u16 *)SERIAL_IV_0, (u16)serial_port_isr_0);
	 return;
	 }

	 if( handle ==  SERIAL_BASE_1 )
	 {
	 isr_call_back_1 = call_back_fun;
	 FLASH_Writew( (u16 *)SERIAL_IV_1, (u16)serial_port_isr_1);
	 return;
	 }

	 if( handle ==  SERIAL_BASE_2 )
	 {
	 isr_call_back_2 = call_back_fun;
	 FLASH_Writew( (u16 *)SERIAL_IV_2, (u16)serial_port_isr_2);
	 return;
	 }

	 if( handle ==  SERIAL_BASE_3 )
	 {
	 isr_call_back_3 = call_back_fun;
	 FLASH_Writew( (u16 *)SERIAL_IV_3, (u16)serial_port_isr_3);
	 return;
	 }*/
	switch (handle)
	{
	case SERIAL_BASE_0:
		serial_isr_call_back_0 = call_back_fun;
		FLASH_Writew((u16 *) SERIAL_IV_0, (u16) serial_port_isr_0);
		break;
	case SERIAL_BASE_1:
		serial_isr_call_back_1 = call_back_fun;
		FLASH_Writew((u16 *) SERIAL_IV_1, (u16) serial_port_isr_1);
		break;
	case SERIAL_BASE_2:
		serial_isr_call_back_2 = call_back_fun;
		FLASH_Writew((u16 *) SERIAL_IV_2, (u16) serial_port_isr_2);
		break;
	case SERIAL_BASE_3:
		serial_isr_call_back_3 = call_back_fun;
		FLASH_Writew((u16 *) SERIAL_IV_3, (u16) serial_port_isr_3);
		break;
	}
	//UCA3IE |= UCRXIE;
	serial_set_ie(handle, UCRXIE);
}

/* for optimize the code bulk  */

void _setup_serial_isr_0(pcb call_back_fun)
{
	serial_isr_call_back_0 = call_back_fun;
	FLASH_Writew((u16 *) SERIAL_IV_0, (u16) serial_port_isr_0);
	UCA0IE |= UCRXIE;
}
void _setup_serial_isr_1(pcb call_back_fun)
{
	serial_isr_call_back_1 = call_back_fun;
	FLASH_Writew((u16 *) SERIAL_IV_1, (u16) serial_port_isr_1);
	UCA1IE |= UCRXIE;
}
void _setup_serial_isr_2(pcb call_back_fun)
{
	serial_isr_call_back_2 = call_back_fun;
	FLASH_Writew((u16 *) SERIAL_IV_2, (u16) serial_port_isr_2);
	UCA2IE |= UCRXIE;
}
void _setup_serial_isr_3(pcb call_back_fun)
{
	serial_isr_call_back_3 = call_back_fun;
	FLASH_Writew((u16 *) SERIAL_IV_3, (u16) serial_port_isr_3);
	UCA3IE |= UCRXIE;
}

void cb(uchar recv_char)
{
	serial_send_byte(hd, recv_char);
}

/*void main()
{

	WDTCTL = WDTPW + WDTHOLD;
	//fun = Serial_port2_isr;
	//serial_init(1);
	u8 buffer[16];
	hd = serial_init( 3, 115200 );
	//setup_serial_isr( hd, cb);
	//setup_serial_isr_op( 3, cb );
	//EnableInterrupt;
	serial_send_buf(hd, "ÖìÊ¤¼Ñ zsjdream \n", 12);
	while (1)
		serial_send_byte(hd, serial_receive_byte(hd));

	//serial_deinit(hd);
}*/

/*#pragma vector=USCI_A2_VECTOR
 __interrupt Serial_port2_isr;*/

