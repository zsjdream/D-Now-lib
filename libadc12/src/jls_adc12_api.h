/*
*   JSL D-NOW LIB for libadc12  *
*   Author: Shengjia.zhu           *
*   Date: Dec 17, 2012               *
*/

#ifndef JLS_ADC12_API_H_
#define JLS_ADC12_API_H_

#include "jls_common_api.h"

/* inter_ref_vol: internal reference voltage */
#define INTER_REF_1_5V		0
#define INTER_REF_2_5V		1
#define INTER_REF_DISABLE	2

/* channel: ADC channels */
#define CH_INPUT_P6_0		0x00
#define CH_INPUT_P6_1		0x01
#define CH_INPUT_P6_2		0x02
#define CH_INPUT_P6_3		0x03
#define CH_INPUT_P6_4		0x04
#define CH_INPUT_P6_5		0x05
#define CH_INPUT_P6_6		0x06
#define CH_INPUT_P6_7		0x07
#define CH_INPUT_P7_4		0x0C
#define CH_INPUT_P7_5		0x0D
#define CH_INPUT_P7_6		0x0E
#define CH_INPUT_P7_7		0x0F
#define CH_EXTER_REF_P		0x08
#define CH_EXTER_REF_N		0x09
#define CH_EXTER_TEMP		0x0A
#define CH_HALF_AVCC		0x0B

/* ref_type*/
#define REF_AVSS__AVCC						0
#define REF_AVSS__INTER_REF					1
#define REF_AVSS__EXTER_REF_P				2
#define REF_EXTER_REF_N__AVCC				4
#define REF_EXTER_REF_N__INTER_REF			5
#define REF_EXTER_REF_N__EXTER_REF_P		6


void adc12_init( u8 inter_ref_vol, boolen is_always_run );
u16 adc12_add_channel( u8 channel, u8 ref_type );
void adc12_begin();
u16 adc12_get_channel_val( u8 channels_id );
void adc12_get_all_channels_val( u16 *vals );
u16 adc12_get_channel_val( u8 channels_id );

u16 adc12_shift_and_get_val( u8 channels_id );
void adc12_shift_and_get_all_vals( u16 *vals );

void adc12_link_channel( u8 channels_id, u16 **val );
void adc12_link_all_channels( u16 **vals );
void adc12_setup_all_channels_finish_isr( icb call_back_fun );

#endif /* JLS_ADC12_API_H_ */
