/*
*   JSL D-NOW LIB for libclock  *
*   Author: Shengjia.zhu           *
*   Date: Oct 30, 2012               *
*/
#include "jls_clock_api.h"
#include <msp430f5438.h>
#include "jls_common_api.h"
void main()
{
        WDTCTL = WDTPW + WDTHOLD;
	clock_init();
	clock_output_ACLK();
	clock_output_MCLK();
	clock_output_SMCLK();
	clock_set_to_4M(CLOCK_MCLK);
	clock_set_to_2M_D(CLOCK_ACLK);
	clock_set_to_2p5K(CLOCK_SMCLK);
	while(1);
}


