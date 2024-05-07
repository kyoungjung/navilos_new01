#include "stdint.h"
#include "HalUart.h"

#include "stdio.h"

//하드웨어 초기화 프로토타입 선언
static void Hw_Init(void);

//프린터 테스트 함수 프로토타입 선언
static void Printf_test(void);

void main(void)
{
    Hw_Init();  //하드웨어 초기화

    uint32_t i = 100;

    
    while(i--)
    {
        Hal_uart_put_char('A');        
    }
    Hal_uart_put_char('\n');
    Hal_uart_put_char('\n');
   
   Hal_uart_put_string("Hello World!\n");
   Hal_uart_put_string("Hello World!\n");
   Hal_uart_put_string("Hello World!\n");

    Printf_test();

    while(1)   // 무한루프
    {
        if('q' == Hal_uart_get_char())
        {
            return;
        }
    }
}

static void Hw_Init(void)
{    
    //Hal_uart_init()함수에서 인터럽트 관련 함수를 호출하므로
    //인터럽트 초기화를 먼저 해줘야 한다.
    Hal_interrupt_init();
    Hal_uart_init();    
}

static void Printf_test(void)
{
    char* str = "printf pointer test";
    char* nullptr = 0;
    uint32_t i = 5;

    debug_printf("%s\r\n", "Hello Printf");
    debug_printf("output string pointer : %s\r\n", str);
    debug_printf("%s is null pointer, %u number\r\n", nullptr, 10);
    debug_printf("%u = 5\r\n", i);
    debug_printf("dec : %u, hex : %x\r\n", 0xff, 0xff);
    debug_printf("print zero %u\r\n", 0);    
}