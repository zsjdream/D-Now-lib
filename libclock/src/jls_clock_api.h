/*
 *   JSL D-NOW LIB for libclock  *
 *   Author: Shengjia.zhu           *
 *   Date: Oct 30, 2012               *
 */

#ifndef JLS_CLOCK_API_H_
#define JLS_CLOCK_API_H_

#include "jls_common_api.h"

void clock_init();
void clock_output_ACLK();
void clock_output_MCLK();
void clock_output_SMCLK();

#define set_cpu_speed_16M_D		clock_set_to_16M_D(CLOCK_MCLK)
#define set_cpu_speed_8M_D		clock_set_to_8M_D(CLOCK_MCLK)
#define set_cpu_speed_4M_D		clock_set_to_4M_D(CLOCK_MCLK)
#define set_cpu_speed_2M_D		clock_set_to_2M_D(CLOCK_MCLK)
#define set_cpu_speed_1M_D		clock_set_to_1M_D(CLOCK_MCLK)
#define set_cpu_speed_500K_D	clock_set_to_500K_D(CLOCK_MCLK)

#define set_cpu_speed_4M		clock_set_to_4M(CLOCK_MCLK)
#define set_cpu_speed_2M		clock_set_to_2M(CLOCK_MCLK)
#define set_cpu_speed_1M		clock_set_to_1M(CLOCK_MCLK)
#define set_cpu_speed_512K		clock_set_to_512K(CLOCK_MCLK)
/* Decimal frequency 1M = 1000K, 1K = 1000Hz */

/* Use clock source XT2CLK */
void clock_set_to_16M_D(u8 clock_type);
void clock_set_to_8M_D(u8 clock_type);
void clock_set_to_4M_D(u8 clock_type);
void clock_set_to_2M_D(u8 clock_type);
void clock_set_to_1M_D(u8 clock_type);
void clock_set_to_500K_D(u8 clock_type);

/* Hexadecimal frequency 1M = 1024K, 1K = 1024Hz */
/* Use clock source DCOCLK */
void clock_set_to_4M(u8 clock_type);
void clock_set_to_2M(u8 clock_type);
/* Use clock source DCOCLKDIV */
void clock_set_to_1M(u8 clock_type);
void clock_set_to_512K(u8 clock_type);
void clock_set_to_256K(u8 clock_type);
void clock_set_to_128K(u8 clock_type);
void clock_set_to_64K(u8 clock_type);
/* Use clock source REFOCLK */
void clock_set_to_32K(u8 clock_type);
void clock_set_to_16K(u8 clock_type);
void clock_set_to_8K(u8 clock_type);
void clock_set_to_4K(u8 clock_type);
void clock_set_to_2K(u8 clock_type);
void clock_set_to_1K(u8 clock_type);
/* Use clock source VLOCLK */
void clock_set_to_10K(u8 clock_type);
void clock_set_to_5K(u8 clock_type);
void clock_set_to_2p5K(u8 clock_type);

#define CLOCK_ACLK 		2
#define	CLOCK_SMCLK		1
#define	CLOCK_MCLK		0

#endif /* JLS_CLOCK_API_H_ */
