#include "msp430f5438.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "jls_log_serial.h"
#include "jls_log.h"
#include "jls_log_api.h"
u16 JLS_LOG_sh;
int putchar(int ch)
{
    log_serial_send_byte(JLS_LOG_sh, ch);
    return ch;
}

int getchar(void)
{
    char ch;
    ch = log_serial_receive_byte(JLS_LOG_sh);
    if (ch == 0x0d)
    {
        ch = 0x0a;
    }
    log_serial_send_byte(JLS_LOG_sh, ch);
    return ch;
}

void FLASH_Readw( u16 *Address, u16 *buf )
{
        memcpy( buf, Address, 2 );
        //*buf = *Address;
}

u16 FLASH_Bootloader_ENV_Get( u8 Pos)
{
        u16 *FlxAdr;
        u16 EnvVal;
        FlxAdr = (u16*)( Pos * 2 + BootEnv_Addr );
        FLASH_Readw(FlxAdr,&EnvVal);
        return EnvVal;
}

void log_init()
{
    JLS_LOG_sh = FLASH_Bootloader_ENV_Get(BL_EVN_SERIALHANDLE);
}
void log_output(u8 *format, ... )
{
    va_list arg_ptr;
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1);
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2);
    va_start(arg_ptr, format);
    vprintf( format, arg_ptr);
    va_end(arg_ptr);
    log_serial_send_byte( JLS_LOG_sh, LOG_END_FLAG);
}
void log_output_d(u8 *format, ... )
{
    va_list arg_ptr;
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1);
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2);
    log_serial_send_byte( JLS_LOG_sh, LOG_DEBUG_PREFIX);
    va_start(arg_ptr, format);
    vprintf( format, arg_ptr);
    va_end(arg_ptr);
    log_serial_send_byte( JLS_LOG_sh, LOG_END_FLAG);
}

void log_output_i(u8 *format, ... )
{
    va_list arg_ptr;
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1);
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2);
    log_serial_send_byte( JLS_LOG_sh, LOG_INFO_PREFIX);
    va_start(arg_ptr, format);
    vprintf( format, arg_ptr);
    va_end(arg_ptr);
    log_serial_send_byte( JLS_LOG_sh, LOG_END_FLAG);
}

void log_output_w(u8 *format, ... )
{
    va_list arg_ptr;
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1);
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2);
    log_serial_send_byte( JLS_LOG_sh, LOG_WARNING_PREFIX);
    va_start(arg_ptr, format);
    vprintf( format, arg_ptr);
    va_end(arg_ptr);
    log_serial_send_byte( JLS_LOG_sh, LOG_END_FLAG);
}

void log_output_e(u8 *format, ... )
{
    va_list arg_ptr;
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1 );
    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2 );
    log_serial_send_byte( JLS_LOG_sh, LOG_ERROR_PREFIX );
    va_start(arg_ptr, format);
    vprintf( format, arg_ptr);
    va_end(arg_ptr);
    log_serial_send_byte( JLS_LOG_sh, LOG_END_FLAG);
}
void _log_send_input_flag()
{
  log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1 );
  log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2 );
  log_serial_send_byte( JLS_LOG_sh, LOG_INPUT_PREFIX );
}
//void log_set_sh( u16 sh )
//{
//  JLS_LOG_sh = sh;
//}
//void log_input(u8 *format, ...)
//{
//    va_list arg_ptr;
//    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG1 );
//    log_serial_send_byte( JLS_LOG_sh, LOG_BEGIN_FLAG2 );
//    log_serial_send_byte( JLS_LOG_sh, LOG_INPUT_PREFIX );
//    va_start(arg_ptr, format);
//    //vscanf( format, arg_ptr );
//    va_end(arg_ptr);
//}
/*void main()
{
    WDTCTL = WDTPW + WDTHOLD;
    //  float b = 10.23;
    int a;
    float b;


    a = 10;
    b = 3.1415;

    log_init();
    //log_init_op(2);

    u8 buf[7];
    u16 d =123;
    log_input( "%d", &d);
    log_output_e("d = %d\n", d);


    //printf("zsj !!!!!!! JLS_LOG_sh = %x\n", JLS_LOG_sh);
    log_input("%d,%f", &a, &b);
    log_output_d("zsj !!!!!!! a = %d, b =%f\n", a, b);

    while (1)
        ;
}*/

