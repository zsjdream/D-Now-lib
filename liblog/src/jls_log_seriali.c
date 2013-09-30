/*
*   JSL D-NOW LIB for serial port  *
*   Author: Shengjia.zhu           *
*   Date: 2012/10/15               *
*/

#include "msp430x54x.h"
#include "jls_serial.h"
#include "jls_log_serial.h"
#include <string.h>



/* UART INIT */
void _log_set_ACLK_to_1M()
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

u16 _log_serial_init_0_9600( )
{
  _log_set_ACLK_to_1M();
  P3SEL |= 0x30;							// P3.4,5 = USCI_A0 TXD/RXD
  P3DIR |= 0x10;
  P3DIR &= ~0x20;
  UCA0CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate9600(0);
  UCA0CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA0IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_0;
}

u16 _log_serial_init_0_115200( )
{
  _log_set_ACLK_to_1M();
  P3SEL |= 0x30;							// P3.4,5 = USCI_A0 TXD/RXD
  P3DIR |= 0x10;
  P3DIR &= ~0x20;
  UCA1CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate115200(0);
  UCA1CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_0;
}

/* Port1 */

u16 _log_serial_init_1_9600( )
{
  _log_set_ACLK_to_1M();
  P5SEL |= 0xC0;							// P3.4,5 = USCI_A0 TXD/RXD
  P5DIR |= 0x40;
  P5DIR &= ~0x80;
  UCA1CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate9600(1);
  UCA1CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_1;
}

u16 _log_serial_init_1_115200( )
{
  _log_set_ACLK_to_1M();
  P5SEL |= 0xC0;							// P3.4,5 = USCI_A0 TXD/RXD
  P5DIR |= 0x40;
  P5DIR &= ~0x80;
  UCA1CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate115200(1);
  UCA1CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA1IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_1;
}

/* Port2 */


u16 _log_serial_init_2_9600( )
{
  _log_set_ACLK_to_1M();
  P9SEL |= 0x30;     // P3.4,5 = USCI_A0 TXD/RXD
  P9DIR |= 0x10;
  P9DIR &= ~0x20;
  UCA2CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate9600(2);
  UCA2CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_2;
}


u16 _log_serial_init_2_115200( )
{
  _log_set_ACLK_to_1M();
  P9SEL |= 0x30;     // P3.4,5 = USCI_A0 TXD/RXD
  P9DIR |= 0x10;
  P9DIR &= ~0x20;
  UCA2CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate115200(2);
  UCA2CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA2IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_2;
}

/* Port3 */

u16 _log_serial_init_3_9600( )
{
  _log_set_ACLK_to_1M();
  P10SEL |= 0x30;     // P3.4,5 = USCI_A0 TXD/RXD
  P10DIR |= 0x10;
  P10DIR &= ~0x20;
  UCA3CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate9600(3);
  UCA3CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_3;
}


u16 _log_serial_init_3_115200( )
{
  _log_set_ACLK_to_1M();
  P10SEL |= 0x30;     // P3.4,5 = USCI_A0 TXD/RXD
  P10DIR |= 0x10;
  P10DIR &= ~0x20;
  UCA3CTL1 |= UCSWRST;					// **Put state machine in reset**
  BaudRate115200(3);
  UCA3CTL1 &= ~UCSWRST;					// **Initialize USCI state machine**
  //UCA3IE |= UCRXIE;						// Enable USCI_A0 RX interrupt
  return SERIAL_BASE_3;
}

void log_serial_send_byte( u16 handle, u8 val )
{
  //uint reg_base = handle;
  while (!(log_serial_read_ifg(handle)&UCTXIFG));				// USCI_A0 TX buffer ready?
  log_serial_write_txbuf( handle, val );
}


u8 log_serial_receive_byte( u16 handle )
{
    u8  ie_val = log_serial_read_ie(handle);
    u8 ch;
    log_serial_clear_ie(handle, UCRXIE);
    while(!(log_serial_read_ifg(handle)&UCRXIFG));
    ch = log_serial_read_rxbuf(handle);
    log_serial_write_ie(handle, ie_val);
    return ch;
}
