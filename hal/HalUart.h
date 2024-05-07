#ifndef HAL_HALUART_H_
#define HAL_HALUART_H_

/*
    @ kjkim
    @ 24.1.11
    @ UART공용 인터페이스 선언
 */

#include "stdint.h"

void Hal_uart_init(void);
void Hal_uart_put_char(uint8_t ch);
uint8_t Hal_uart_get_char(void);
#endif //HAL_HALUART_H_