/*
*   JSL D-NOW LIB for libwdt  *
*   Author: Shengjia.zhu           *
*   Date: Nov 1, 2012               *
*/

#ifndef JLS_WDT_API_H_
#define JLS_WDT_API_H_
#include "jls_common_api.h"

void wdt_set_enable( boolen en );

void wdt_keep_alive();

/* Use VLOCLK ¡Ö 9.8 * 1024 Hz * */
void wdt_set_timeout_to_59h26m35s();
void wdt_set_timeout_to_3h42m55s();
void wdt_set_timeout_to_13m56s();
void wdt_set_timeout_to_52s();
void wdt_set_timeout_to_3p2s();


/* Use ACLK = 1000000 Hz */
void wdt_set_timeout_to_35m47s();
void wdt_set_timeout_to_2m14s();
void wdt_set_timeout_to_8p4s();
void wdt_set_timeout_to_524p3ms();
void wdt_set_timeout_to_32p8ms();
void wdt_set_timeout_to_8p2ms();
void wdt_set_timeout_to_512us();



#endif /* JLS_WDT_API_H_ */
