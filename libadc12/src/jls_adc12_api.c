/*
*   JSL D-NOW LIB for libadc12  *
*   Author: Shengjia.zhu           *
*   Date: Dec 17, 2012               *
*/
#include <msp430f5438a.h>
#include "jls_adc12.h"
#include "jls_adc12_api.h"
#include "jls_common.h"
u8 jls_adc12_ch = 0;
void adc12_init( u8 inter_ref_vol, boolen is_always_run )
{
	ADC12CTL0 &= ~BIT1; //ENC = 0
	REFCTL0 &= ~REFMSTR; // Only in 5438A to close the ref module
	if( inter_ref_vol == 2 )//disable
	{
		ADC12CTL0 &= ~BIT5;  /* Open ref */
	}
	else
	{
		ADC12CTL0 |= BIT5;  /* Open ref */
		ADC12CTL0 &= ~BIT6; //clear
		ADC12CTL0 |= (inter_ref_vol<<6); //inter_ref_type == 0 (1.5v), inter_ref_type == 1 (2.5v)

	}
	ADC12CTL2 |= BIT2; // sampling rate > 50ksps
	ADC12CTL2 &= ~BIT0; // Reference buffer on only during sample-and-conversion
	ADC12CTL1 = (ADC12CTL1 & 0XFFE7) | ((0 & 0X0003) <<3); //Sel clk = modclk
	ADC12CTL2 &= ~BIT8; //Pre-divide by 1
	ADC12CTL1=(ADC12CTL1 & 0XFF1F) | ((0 & 0X0007) <<5); //ADC12_A clock divider = 1
	ADC12CTL1 &= ~BIT8; //The sample-input signal is not inverted.
	ADC12CTL1 = (ADC12CTL1 & 0X3FFF) | ((0 & 0X0003) <<10); // ADC12_A sample-and-hold source select to ADC12SC bit
	ADC12CTL1 |= BIT9; //SAMPCON signal is sourced from the sample-input signal.
	ADC12CTL0 |= BIT7; /*The first rising edge of the SHI signal triggers the sampling timer,
							but further sample-and-conversions are performed automatically as
							soon as the prior conversion is completed.*/
	ADC12CTL0 = (ADC12CTL0 & 0XF0FF) | ((1 & 0X000F) <<8); //ADC12_A sample-and-hold time = 8 ADC12CLK cycles for registers ADC12MEM0 to ADC12MEM7.
	ADC12CTL0 = (ADC12CTL0 & 0XF0FF) | ((1 & 0X0FFF) <<12); //ADC12_A sample-and-hold time = 8 ADC12CLK cycles for registers ADC12MEM8 to ADC12MEM15.
	ADC12CTL1 = (ADC12CTL1 & 0X0FFF) | ((0 & 0X000F) <<12); //ADC12_A conversion start address = 0

	//ADC12CTL1 = (ADC12CTL1 & 0XFFF9) | ((3 & 0X0003) <<1); //0: Single-channel, single-conversion
	ADC12CTL1 &= ~( BIT2 + BIT1);
	ADC12CTL1 |= (is_always_run << 2); //is_always_run == 1: always run(CONSEQ = 2 or 3)   is_always_run == 0: single time(CONSEQ = 0 or 1)
}

u16 adc12_add_channel( u8 channel, u8 ref_type )
{
	if( jls_adc12_ch >= 16 )
	{
		return -1;
	}
	reg_writec( ADC12_MEMCTL_BASE, jls_adc12_ch, 0 );
	reg_setc( ADC12_MEMCTL_BASE, jls_adc12_ch, channel);
	reg_setc( ADC12_MEMCTL_BASE, jls_adc12_ch, (ref_type << 4) );
	return jls_adc12_ch++;
}

void adc12_begin()
{
	if( jls_adc12_ch > 1 )
	{
		ADC12CTL1 |= BIT1;
		reg_setc( ADC12_MEMCTL_BASE, jls_adc12_ch - 1, BIT7 );
	}
	ADC12CTL0 |= BIT4;
	ADC12CTL0 |= BIT1; //ENC = 0
	ADC12CTL0 |= BIT0; //Start sample-and-conversion
	_NOP();
	ADC12CTL0 &= ~BIT0; //No sample-and-conversion-start
}

u16 adc12_get_channel_val( u8 channels_id )
{
	while( !(ADC12IFG & (1 << channels_id) ) );
	return reg_readw(ADC12_MEM_BASE,channels_id*2 );
}

void adc12_get_all_channels_val( u16 *vals )
{
	int ch_id;
	while( !(ADC12IFG & (1 << (jls_adc12_ch-1) ) ) );
	for( ch_id = 0; ch_id < jls_adc12_ch; ++ch_id )
	{
		vals[ch_id] = reg_readw( ADC12_MEM_BASE, ch_id*2 );
	}
}

u16 adc12_shift_and_get_val( u8 channels_id )
{
	adc12_begin();
	return adc12_get_channel_val(channels_id);
}

void adc12_shift_and_get_all_vals( u16 *vals )
{
	adc12_begin();
	adc12_get_all_channels_val( vals );
}

void adc12_link_all_channels( u16 **vals )
{
	*vals = (u16 *)ADC12_MEM_BASE;
}

void adc12_link_channel( u8 channels_id, u16 **val )
{
	*val = (u16 *) (ADC12_MEM_BASE + channels_id * 2);
}

icb adc12_all_channels_finnish_call_back;
__interrupt void adc12_channel_shift_finish_isr(void)
{
	if( (ADC12IV - 6) / 2 != (jls_adc12_ch-1) )
	{
		return;
	}
	adc12_all_channels_finnish_call_back( (u16*)ADC12_MEM_BASE );
}

void adc12_setup_all_channels_finish_isr( icb call_back_fun )
{
	adc12_all_channels_finnish_call_back = call_back_fun;
	FLASH_Writew((u16 *) ADC12_IV, (u16) adc12_channel_shift_finish_isr);
	ADC12IE |= 1 << (jls_adc12_ch-1);
}

