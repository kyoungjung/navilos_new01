#include "Uart.h"
#include "HalUart.h"
#include "stdint.h"
#include "HalInterrupt.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init(void)
{
    //Uart Init
    //UARTEN 을 disable 먼저 수행한 후
    //Control Register Programming
    //UARTEN enable 절차 수행
    Uart->uartcr.bits.UARTEN    = 0;
    Uart->uartcr.bits.TXE       = 1;
    Uart->uartcr.bits.RXE       = 1;
    Uart->uartcr.bits.UARTEN    = 1;

    //RX interrupt Enable
    Uart->uartimsc.bits.RXIM    = 1;

    //interrupt id : 44(UART0 인터럽트)
    Hal_interrupt_enable(UART_INTERRUPT0);
    //interrupt_handler함수를 인터럽트 발생 시 실행하는 함수로 등록, uart0 인터럽트와 연결
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);

}

/*
    @ 인터럽트 발생 시 실행되는 핸들러 함수
*/
static void interrupt_handler(void)
{
    uint8_t ch = Hal_uart_get_char();
    Hal_uart_put_char(ch);
}

void Hal_uart_put_char(uint8_t ch)
{
    //TXFF(Transmit FIFO)가 0이 되면(전송할 준비가 됬다면) 루프탈출    
    while(Uart->uartfr.bits.TXFF != 0); 
    //데이터 레지스터에 전송할 1바이트 데이터 ch를 저장한다.
    Uart->uartdr.all = (ch & 0xFF);
}

#if 0
/*
    @ 비효율적인 uart 수신함수
*/
uint8_t Hal_uart_get_char(void)
{
    uint8_t data;   //수신 데이터 저장 변수

    //uart flag register의 RXFE(Fifo Empty)가
    //0이면 receive Fifo에 data가 있다.    
    while(Uart->uartfr.bits.RXFE);

    //data 레지스터의 error bit를 체크하여 error check
    if((Uart->uartdr.bits.OE) || (Uart->uartdr.bits.BE) ||
        (Uart->uartdr.bits.PE) || (Uart->uartdr.bits.FE))
        {
            Uart->uartrsr.bits.OE = 1;  //overrun error clear??
            Uart->uartrsr.bits.BE = 1;  //Break error 
            Uart->uartrsr.bits.PE = 1;  //Parity error clear
            Uart->uartrsr.bits.FE = 1;  //Framing error clear

            return 0;   //error 발생했으므로 리턴
        }

    //data register에 있는 uart 수신 데이터를 가져와 data변수에 저장
    data = Uart->uartdr.bits.DATA;
    //uart 수신데이터 return
    return data;
}
#endif

#if 0
/*
    @ 비효율적인 uart 수신함수
            --> 1단계 최적화 코드작성
*/
uint8_t Hal_uart_get_char(void)
{
    uint8_t data;

    //uart flag register의 RXFE(Fifo Empty)가
    //0이면 receive Fifo에 data가 있다.    
    while(Uart->uartfr.bits.RXFE);

    //check error flag
    //FE(8), PE(9), BE(10), OE(11)
    if(Uart->uartdr.all & 0x00000F00)
    {
        Uart->uartrsr.all = 0x0000000F;

        return 0;
    }

    data = Uart->uartdr.bits.DATA;

    return data;
}
#endif

#if 1
/*
    @ 비효율적인 uart 수신함수
            --> 1단계 최적화 코드작성
                ---> 2단계 최적화 코드작성
*/
uint8_t Hal_uart_get_char(void)
{
    uint32_t data;

    //uart flag register의 RXFE(Fifo Empty)가
    //0이면 receive Fifo에 data가 있다.    
    //receive Fifo에 data가 있으므로(0) while빠져나온다
    while(Uart->uartfr.bits.RXFE);

    //32bits uartdr(data register)값을 data변수에 저장
    //uartdr구조
    //  [31 : 12] Reserved
    //  [11]OE, [10]BE, [9]PE, [8]FE
    //  [7 : 0] DATA
    data = Uart->uartdr.all;

    if(data & 0x00000F00)
    {
        //Clear error
        Uart->uartrsr.all = 0x0000000F;
        return 0;
    }

    return (uint8_t)(data & 0x000000FF);
}
#endif