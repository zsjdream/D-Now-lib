/*
*   JSL D-NOW LIB for libwdt  *
*   Author: Shengjia.zhu           *
*   Date: Nov 1, 2012               *
*/

#include <msp430f5438.h>
#include "msp430f5438.h"
#include "jls_log_api.h"
#include "jls_common.h"
#include "jls_wdt_api.h"
void main()
{
//	WDTCTL = WDTPW + WDTHOLD;
    wdt_set_timeout_to_3p2s();
    wdt_set_enable(1);
    log_init_op(3);
    log_output("//Program Begin!!!\r\n");
     while(1)
     {
    	 wdt_keep_alive();
      __delay_cycles(1048576*4);
     }
       
}


