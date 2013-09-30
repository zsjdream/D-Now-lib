/*
 * jls_log_api.h
 *
 *  Created on: Oct 20, 2012
 *      Author: Administrator
 */

#ifndef JLS_LOG_API_H_
#define JLS_LOG_API_H_
#include <stdio.h>
#include "jls_common.h"
extern u16 JLS_LOG_sh;

u16 _log_serial_init_0_9600();
u16 _log_serial_init_0_115200();


u16 _log_serial_init_1_9600();
u16 _log_serial_init_1_115200();


u16 _log_serial_init_2_9600();
u16 _log_serial_init_2_115200();


u16 _log_serial_init_3_9600();
u16 _log_serial_init_3_115200();

void _log_send_input_flag();
/* For Optimize*/
#define log_init_op(id) JLS_LOG_sh = _log_serial_init_##id##_9600()
#define log_input( fmt, ...)   \
{                              \
  _log_send_input_flag();      \
  scanf( fmt, __VA_ARGS__ );\
}\

void log_init();
void log_output( u8 *format, ... );
void log_output_d( u8 *format, ... );
void log_output_i( u8 *format, ... );
void log_output_w( u8 *format, ... );
void log_output_e( u8 *format, ... );
#endif /* JLS_LOG_API_H_ */
