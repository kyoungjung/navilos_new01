#ifndef LIB_STDIO_H
#define LIB_STDIO_H

#include "stdarg.h"

typedef enum utoa_t
{
    utoa_dec = 10,
    utoa_hex = 16,
}utoa_t;

uint32_t Hal_uart_put_string(const char *str);
uint32_t debug_printf(const char* format, ...);
uint32_t vsprintf(char *buf, const char* format, va_list arg);
uint32_t utoa(char* buf, uint32_t val, utoa_t base);

#endif //LIB_STDIO_H