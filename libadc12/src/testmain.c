/*
*   JSL D-NOW LIB for libadc12  *
*   Author: Shengjia.zhu           *
*   Date: Dec 19, 2012               *
*/
#include <msp430f5438a.h>
#include "jls_adc12_api.h"
#include "jls_common_api.h"

int *x0,*x1,*x2,xx0,xx1,xx2,xx3,ch0,ch1,ch2,ch3;
u16 x[5];
void cb0( u16 *val )
{
	xx0 = val[ch0];
	xx1 = val[ch1];
	xx2 = val[ch2];
        xx3 = val[ch3];
}

void main()
{
	WDTCTL = WDTPW + WDTHOLD;
	
	adc12_init( INTER_REF_2_5V, 1 );
	ch0 = adc12_add_channel( CH_HALF_AVCC, REF_AVSS__AVCC );
        ch1 = adc12_add_channel( CH_HALF_AVCC, REF_AVSS__INTER_REF );
	ch2 = adc12_add_channel( CH_HALF_AVCC, REF_AVSS__AVCC );
	ch3 = adc12_add_channel( CH_HALF_AVCC, REF_AVSS__INTER_REF );
//	adc12_link_channel( ch0, &x0 );
//        adc12_link_channel( ch1, &x1 );
//        adc12_link_channel( ch2, &x2 );
	//adc12_link_all_channels(&x);
	adc12_begin();
	adc12_setup_all_channels_finish_isr( cb0 );
        __enable_interrupt();
	while(1)
	{
           /* xx0 = *x0;
            xx1 = *x1;
            xx2 = *x2;*/
//		adc12_get_all_channels_val(x);
//        x0 = adc12_shift_and_get_val( ch0 );
//        x0 = adc12_shift_and_get_val( ch2 );
		//adc12_shift_and_get_all_vals(x);
//		x0 = adc12_get_channel_val( ch0 );
//                x0 = adc12_get_channel_val( ch2 );
//		x0 = adc12_get_channel_val( ch1 );
		
	}
}
