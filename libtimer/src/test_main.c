/*
*   JSL D-NOW LIB for libtimer  *
*   Author: Shengjia.zhu           *
*   Date: Nov 19, 2012               *
*/
#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_common_api.h"
#include "jls_timer_api.h"
void callback_function0()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function1()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function2()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function3()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function4()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function5()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void callback_function6()
{
	P3OUT ^= BIT0;
	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
}
void set_ACLK_to_1M()
{
	P5SEL |= 0x0C; // Port select XT2
	UCSCTL6 &= ~XT2OFF; // Ena¡Á¡Áe XT2
	UCSCTL3 = 0;
	UCSCTL3 |= SELREF_2 + FLLREFDIV__1;
	UCSCTL2 = 0;
	UCSCTL2 |= 31 + FLLD__1;

	UCSCTL4 &= ~0x0700;
	UCSCTL4 &= ~0x0007;
	UCSCTL4 |= SELA_5;
	UCSCTL4 |= SELM_5;
	UCSCTL5 &= ~0x0700;
	UCSCTL5 &= ~0x0007;
	UCSCTL5 |= DIVA__16;
	UCSCTL5 |= DIVM__1;

	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG; // Clear fault flags
		__delay_cycles(100000); // Delay for Osc to stabilize
	} while ((SFRIFG1 & (~(0XFFFD))) >> 1 == 1); // Test oscillator fault flag
	P11SEL = 0x07;
	P11DIR = 0x07;
}
u16 a,b,c;
void main()
{
	WDTCTL = WDTPW + WDTHOLD;         
	__enable_interrupt();
	P3DIR |= 0x01;
	set_ACLK_to_1M();

//	timer2_task_list_init(4000000);
//	timer2_add_list_task(1000000,callback_function0);
//	timer2_add_list_task(1500000,callback_function1);
//	timer2_add_list_task(2000000,callback_function2);
//	timer2_add_list_task(2500000,callback_function3);
//        timer2_add_list_task(3000000,callback_function4);
//        timer2_add_list_task(3500000,callback_function5);
//        timer2_add_list_period_end_task(callback_function6);
//
//  timer0_task_list_init(4000000);
//	timer0_add_list_period_end_task(callback_function4);
//	timer0_add_list_task(1000000,callback_function0);
//	timer0_add_list_task(2000000,callback_function1);

//	timer0_add_list_task(3000,callback_function2);
//	timer0_add_list_task(4000000,callback_function3);
//	timer2_mono_pulse( T2_MONO_PULSE_OUT_P4_1, 4000000, 0 );
//	timer2_set_task( 4000000,  callback_function0 );
//	timer2_pwm_init(1000);
//        timer1_pwm_init(500);
//         timer0_pwm_init(2000);
//	timer0_pwm_init(500);
//
//	timer2_pwm_out( T2_PWM_OUT_P4_1, 0.4 );
//	timer1_pwm_out( T1_PWM_OUT_P2_3, 0.5 );
//    timer0_pwm_out( T0_PWM_OUT_P1_2, 0.5 );
//////
//        timer2_pwm_out( T2_PWM_OUT_P4_1, 0.1 );
//        timer2_pwm_out( T2_PWM_OUT_P4_2, 0.2 );
//        timer2_pwm_out( T2_PWM_OUT_P4_3, 0.3 );
//        timer2_pwm_out( T2_PWM_OUT_P4_4, 0.4 );
//        timer2_pwm_out( T2_PWM_OUT_P4_5, 0.5 );
//        timer2_pwm_out( T2_PWM_OUT_P4_6, 0.6 );
//          timer1_deadzone_pwm_init(5000000);
//          timer1_deadzone_pwm_out(T1_PWM_OUT_P8_6,0.4,T1_PWM_OUT_P7_3,0.4,0);
//          timer0_phaseshift_squarewave_init(8000000);
//          timer0_phaseshift_squarewave_out( T0_PWM_OUT_P8_3, 0 );
//          timer0_phaseshift_squarewave_out( T0_PWM_OUT_P8_4, 90 );
//          timer0_start();
//           timer1_start();
          timer2_start();
	  while(1);
}
//int i;
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void TA0_ISR(void)
//{
//	P3OUT ^= BIT0;
//	TA0CCTL0=(TA0CCTL0 & 0xFFFE) | ((0 & 0x0001) << 0);
////        if(++i == 10 )
////        {
////          i = 0;
////        }
//	//TA0CTL=(TA0CTL & 0xFFFE) | ((0 & 0x0001) << 0);
//}
