/*
*   JSL D-NOW LIB for libtimer  *
*   Author: Shengjia.zhu           *
*   Date: Dec 03, 2012               *
*/

#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_common.h"
#include "jls_timer.h"
#include "jls_timer_api.h"
u8 jls_timer2_mod = 0;
u8 jls_timer2_list_id;
float jls_timer2_clk_per_ms;
void timer2_clear()
{
	TB0CTL=(TB0CTL & 0xFFFB) | ((1 & 0x0001) << 2);  //Clear TB0 | TACLR
	//TB0CTL=(TB0CTL & 0xFFFB) | ((0 & 0x0001) << 2);  //set TB0 | TACLR
}

void timer2_start()
{
	TB0CTL=(TB0CTL & 0xFCFF) | ((1 & 0x0003) << 8);  //Sel AClK
	TB0CTL=(TB0CTL & 0xFFFB) | ((1 & 0x0001) << 2);  //Clear TB0 | TACLR
	TB0CTL=(TB0CTL & 0xFFCF) | ((jls_timer2_mod & 0x0003) << 4);  //Sel Mod
}

void timer2_stop()
{
	TB0CTL=(TB0CTL & 0xFFCF) | ((0 & 0x0003) << 4);  //Sel Mod
}

u16 timer2_read_val()
{
	return TB0R;
}
void (*timer2_task_isr_call_back)( );
vcb timer2_list_task_isr_call_back[7];



__interrupt void timer2_task_isr1(void)
{
	switch(TB0IV)
	{
		case 0x02: //CCR1
			timer2_list_task_isr_call_back[0]();
			break;
		case 0x04: //CCR2
			timer2_list_task_isr_call_back[1]();
			break;
		case 0x06: //CCR3
			timer2_list_task_isr_call_back[2]();
			break;
		case 0x08: //CCR4
			timer2_list_task_isr_call_back[3]();
			break;
		case 0x0a: //CCR5
			timer2_list_task_isr_call_back[4]();
			break;
		case 0x0c: //CCR6
			timer2_list_task_isr_call_back[5]();
			break;
		case 0x0e: //TB0
			timer2_list_task_isr_call_back[6]();
			break;
	}
}

__interrupt void timer2_task_isr(void)
{
	timer2_task_isr_call_back( );
}

void timer2_set_task( u32 us, vcb call_back_fun ) //ms should <= 4194
{
	u8 div_ex, div;
	float base;
	if( us < 65535 )
	{
		div_ex = 0;
		div = 0;
		base = 1;
	}
	else if( us <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		base = 0.025; //25 / 1000;
	}
	else if( us <= 4194000 )
	{
		div_ex = 7;
		div = 3;
		base = 0.015625; //15.625 / 1000;
	}
	else
	{
		return;
	}
	timer2_task_isr_call_back = call_back_fun;
	FLASH_Writew((u16 *) TIMERB_IV_0, (u16) timer2_task_isr);
	jls_timer2_mod = 1;
	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
	TB0CCR0 = us * base - 1;
	TB0CCTL0=(TB0CCTL0 & 0xFFEF) | ((1 & 0x0001) << 4); //Enable Interrpute of CCR0
}

void timer2_task_list_init( u32 period )
{
	u8 div_ex, div;
	if( period < 65535 )
	{
		div_ex = 0;
		div = 0;
		jls_timer2_clk_per_ms = 1;
	}
	else if( period <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		jls_timer2_clk_per_ms = 0.025; //25/1000;
	}
	else if( period <= 4194000 )
	{
		div_ex = 7;
		div = 3;
		jls_timer2_clk_per_ms = 0.015625; //15.625/1000;
	}
	else
	{
		return;
	}
	FLASH_Writew((u16 *) TIMERB_IV_1, (u16) timer2_task_isr1);
	jls_timer2_mod = 1;
	jls_timer2_list_id = 1;
	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
    TB0CCR0 = period * jls_timer2_clk_per_ms - 1;
}

void timer2_add_list_task( u32 time_val, vcb call_back_fun )
{
	if( jls_timer2_list_id > 6 )
	{
	  return;
	}
	reg_writew(TIMERB_CCRX_BASE,
			jls_timer2_list_id * 2,
			time_val * jls_timer2_clk_per_ms - 1); //Set acquirer
	timer2_list_task_isr_call_back[jls_timer2_list_id-1] = call_back_fun; //Set interrupt callback function
	reg_setw(TIMERB_CCTLX_BASE,
				jls_timer2_list_id * 2,
				0x10); //Set acquirer
	++ jls_timer2_list_id;
}


void timer2_add_list_period_end_task( vcb call_back_fun )
{
	timer2_list_task_isr_call_back[6] = call_back_fun;
	TB0CTL=(TB0CTL & 0xFFFD) | ((1 & 0x0001) << 1);  //Enable TB0 IE
}



/* mono pulse out */
void timer2_mono_pulse( u8 out_pin, u32 keep_time, boolen steady_state )
{
	float base;
	u8 div_ex, div;
	if( keep_time < 65535 )
	{
		div_ex = 0;
		div = 0;
		base = 1;
	}
	else if( keep_time <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		base = 0.025; //25/1000;
	}
	else if( keep_time <= 4194000 )
	{
		div_ex = 7;
		div = 3;
		base = 0.015625; //15.625/1000;
	}
	else
	{
		return;
	}
    steady_state = !steady_state;
    u8 reg_offset;
    if( out_pin <= T2_MONO_PULSE_OUT_P4_6 )
    {
    	P4DIR |= 0x01 << out_pin;
    	P4SEL |= 0x01 << out_pin;
    	reg_offset = out_pin * 2;
    }
    else
    {
    	return;
    }


	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
	jls_timer2_mod = 2;

	reg_clearw( TIMERB_CCTLX_BASE, reg_offset, 0x00ff );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset, ( steady_state << 2 ) );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset, ( ( (steady_state << 2) + 1) << 5) );
	reg_writew(TIMERB_CCRX_BASE,
				reg_offset ,
				keep_time * base - 1); //Set acquirer
}


/* PWM Out */
void timer2_pwm_init( u32 period )
{
	float base;
	u8 div_ex, div;
	if( period < 65535 )
	{
		div_ex = 0;
		div = 0;
		base = 1;
	}
	else if( period <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		base = 0.025; //25/1000;
	}
	else if( period <= 4194000 )
	{
		div_ex = 7;
		div = 3;
		base = 0.015625; //15.625/1000;
	}
	else
	{
		return;
	}
	jls_timer2_mod = 1;
	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
	TB0CCR0 = period * base - 1;
}

void timer2_pwm_out( u8 out_pin, float duty_cycle )
{
	u8 reg_offset;
	if( out_pin <= T2_PWM_OUT_P4_6 )
	{
		P4DIR |= 0x01 << out_pin;
		P4SEL |= 0x01 << out_pin;
		reg_offset = out_pin * 2;
	}
	else
	{
		return;
	}
	reg_clearw( TIMERB_CCTLX_BASE, reg_offset, 0x00ff );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset, ( 0x07 << 5) );
	reg_writew(TIMERB_CCRX_BASE,
	reg_offset ,
	duty_cycle * ( TB0CCR0 + 1 ) - 1 ); //Set acquirer
}

void timer2_deadzone_pwm_init(  u32 period  )
{
	float base;
	u8 div_ex, div;
	if( period < 65535 )
	{
		div_ex = 0;
		div = 0;
		jls_timer2_clk_per_ms = 1;
	}
	else if( period <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		jls_timer2_clk_per_ms = 0.025;
	}
	else if( period <= 8388000 )
	{
		div_ex = 7;
		div = 3;
		jls_timer2_clk_per_ms = 0.015625;
	}
	else
	{
		return;
	}
	jls_timer2_mod = 3;
	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
	TB0CCR0 = period * jls_timer2_clk_per_ms / 2 - 1;
}

void timer2_deadzone_pwm_out( u8 out_pin1, float duty_cycle1, u8 out_pin2, float duty_cycle2, u32 deadzone_time )
{
	u8 reg_offset1, reg_offset2;
	if( out_pin1 <= T2_PWM_OUT_P4_6 )
	{
		P4DIR |= 0x01 << out_pin1;
		P4SEL |= 0x01 << out_pin1;
		reg_offset1 = out_pin1 * 2;
	}
	else
	{
		return;
	}

	if( out_pin2 <= T2_PWM_OUT_P4_6 )
	{
		P4DIR |= 0x01 << out_pin2;
		P4SEL |= 0x01 << out_pin2;
		reg_offset2 = out_pin2 * 2;
	}
	else
	{
		return;
	}

	/* calculate the comparer value 1 and value 2*/
	u16 half_period = (TB0CCR0 + 1);
	u16 cmp_val1 = half_period * (1 - duty_cycle1);
	u16 cmp_val2 = half_period * duty_cycle1;
	u16 deadzone_val = deadzone_time * jls_timer2_clk_per_ms;
	if( (cmp_val1 - cmp_val2) < deadzone_val )
	{
		u16 mid_val = (cmp_val1 + cmp_val2)/2;
		cmp_val1 = mid_val + (deadzone_val/2);
		cmp_val2 = mid_val - (deadzone_val/2);
	}

	reg_clearw( TIMERB_CCTLX_BASE, reg_offset1, 0x00ff );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset1, ( 0x06 << 5) );
	reg_writew(TIMERB_CCRX_BASE,
	reg_offset1 ,
	cmp_val1 - 1 ); //Set acquirer

	reg_clearw( TIMERB_CCTLX_BASE, reg_offset2, 0x00ff );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset2, ( 0x02 << 5) );
	reg_writew(TIMERB_CCRX_BASE,
	reg_offset2 ,
	cmp_val2 - 1 ); //Set acquirer
}

void timer2_phaseshift_squarewave_init(  u32 period  )
{
	float base;
	u8 div_ex, div;
	if( period < 65535 )
	{
		div_ex = 0;
		div = 0;
		jls_timer2_clk_per_ms = 1;
	}
	else if( period <= 2621000 )
	{
		div_ex = 4;
		div = 3;
		jls_timer2_clk_per_ms = 0.025;
	}
	else if( period <= 8388000 )
	{
		div_ex = 7;
		div = 3;
		jls_timer2_clk_per_ms = 0.015625;
	}
	else
	{
		return;
	}
	jls_timer2_mod = 1;
	TB0EX0=(TB0EX0 & 0xFFF8) | ((div_ex & 0x0007) << 0);  //Sel divex
	TB0CTL=(TB0CTL & 0xFF3F) | ((div & 0x0003) << 6);	 //Sel div 1
	TB0CCR0 = period * jls_timer2_clk_per_ms / 2 - 1;
}

void timer2_phaseshift_squarewave_out( u8 out_pin, u16 phase )
{
	phase %= 360;
	u8 reg_offset;
	if( out_pin <= T2_PWM_OUT_P4_6 )
	{
		P4DIR |= 0x01 << out_pin;
		P4SEL |= 0x01 << out_pin;
		reg_offset = out_pin * 2;
	}
	else
	{
		return;
	}
	boolen out_val;
	if( phase >= 180)
	{
		out_val = 1;
	}
	else
	{
		out_val = 0;
	}
	u16 cmp_val = ( (u32)phase % 180 ) * ( TB0CCR0 + 1 ) / 180;
        if( cmp_val == 0 )
        {
          cmp_val = 1;
        }
	reg_clearw( TIMERB_CCTLX_BASE, reg_offset, 0x00ff );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset, ( out_val << 2 ) );
	reg_setw( TIMERB_CCTLX_BASE, reg_offset, ( 0x04 << 5) );
	reg_writew(TIMERB_CCRX_BASE,
	reg_offset ,
	cmp_val - 1 ); //Set acquirer
}
