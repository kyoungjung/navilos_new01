#ifndef _UART_H
#define _UART_H

#include "stdint.h"

//** 첫번째 방법 C언어 매크로 사용 방법 ---
// UART Data Register
#define UART_BASE_ADDR                  0x10009000

#define UARTDR_OFFSET                   0x000
#define UARTDR_DATA                     (0)
#define UARTDR_FE                       (8)
#define UARTDR_PE                       (9)
#define UARTDR_BE                       (10)
#define UARTDR_OE                       (11)

// UART Control Register
#define UARTCR_OFFSET                   0x30


//** 두번째 방법 구조체 사용 ---

#define UART_BASE_ADDRESS0                  0x10009000
#define UART_INTERRUPT0                     44

//Data Register bits
typedef union UARTDR_t
{
    //union은 메모리를 공유함.
    //all 이라는 32비트크기 변수와, bits bit field 간 메모리 공유함
    //만약 bit field의 특정 비트가 변경되면
    //all 변수의 해당 비트값도 변경됨
    uint32_t all;
    struct
    {
        uint32_t DATA       :8;     //7:0
        uint32_t FE         :1;     //8
        uint32_t PE         :1;     //9
        uint32_t BE         :1;     //10
        uint32_t OE         :1;     //11
        uint32_t reserved   :3;     //12:15
    }bits;
}UARTDR_t;

//Receive Status Register / Error Clear Register bits
typedef union UARTRSR_t
{
    uint32_t all;
    struct 
    {
        uint32_t FE         :1;     // 0
        uint32_t PE         :1;     // 1
        uint32_t BE         :1;     // 2
        uint32_t OE         :1;     // 3
        uint32_t reserved   :28;    // 4 : 31
    }bits;    
}UARTRSR_t;

//Flag Register bits
typedef union UARTFR_t
{
    uint32_t all;
    struct
    {
        uint32_t CTS        :1;     // 0
        uint32_t DSR        :1;     // 1
        uint32_t DCD        :1;     // 2
        uint32_t BUSY       :1;     // 3
        uint32_t RXFE       :1;     // 4
        uint32_t TXFF       :1;     // 5
        uint32_t RXFF       :1;     // 6
        uint32_t TXFE       :1;     // 7
        uint32_t RI         :1;     // 8
        uint32_t reserved   :23;    // 9 : 31
    }bits;
}UARTFR_t;

//IrDA Low-Power Counter Register bits
typedef union UARTILPR_t
{
    uint32_t all;
    struct
    {
        uint32_t ILPDVSR    :8;     // 0:7
        uint32_t reversed   :24;    // 8:31
    }bits;
}UARTILPR_t;

//Integer Baud Rate Register bits
typedef union UARTIBRD_t
{
    uint32_t all;
    struct
    {
        uint32_t BAUDDIVINT :16;    // 0:15
        uint32_t reversed   :16;    // 16:31
    }bits;
}UARTIBRD_t;

//Fractional Baud Rate Register bits
typedef union UARTFBRD_t
{
    uint32_t all;
    struct
    {
        uint32_t BAUDDIVFRAC    :6;     // 0:5
        uint32_t reserved       :26;    // 6:31
    }bits;
}UARTFBRD_t;

//Line Control Register bits
typedef union UARTLCR_H_t
{
    uint32_t all;
    struct
    {
        uint32_t BRK            :1;     // 0
        uint32_t PEN            :1;     // 1
        uint32_t EPS            :1;     // 2
        uint32_t STP2           :1;     // 3
        uint32_t FEN            :1;     // 4
        uint32_t WLEN           :2;     // 5:6
        uint32_t SPS            :1;     // 7
        uint32_t reserved       :24;    // 8:31
    }bits;
}UARTLCR_H_t;

//Control Register bits
typedef union UARTCR_t
{
    uint32_t all;
    struct
    {
        uint32_t UARTEN     :1;     //0
        uint32_t SIREN      :1;     //1
        uint32_t SIRLP      :1;     //2
        uint32_t Reserved   :4;     //3:6
        uint32_t LBE        :1;     //7
        uint32_t TXE        :1;     //8
        uint32_t RXE        :1;     //9
        uint32_t DTR        :1;     //10
        uint32_t RTS        :1;     //11
        uint32_t Out1       :1;     //12
        uint32_t Out2       :1;     //13
        uint32_t TRSEn      :1;     //14
        uint32_t CTSEn      :1;     //15
    }bits;
    
}UARTCR_t;

//Interrupt FIFO Level Select Register bits
typedef union UARTIFLS_t
{
    uint32_t all;
    struct
    {
        uint32_t TXIFLSEL   :3;     // 0:2
        uint32_t RXIFLSEL   :3;     // 3:5
        uint32_t reserved   :26;    // 6:31
    }bits;
}UARTIFLS_t;

// Interrupt Mask Set/Clear Register bits
typedef union UARTIMSC_t
{
    uint32_t all;
    struct
    {
        uint32_t RIMIM      :1;     // 0
        uint32_t CTSMIM     :1;     // 1
        uint32_t DCDMIM     :1;     // 2
        uint32_t DSRMIM     :1;     // 3
        uint32_t RXIM       :1;     // 4
        uint32_t TXIM       :1;     // 5
        uint32_t RTIM       :1;     // 6
        uint32_t FEIM       :1;     // 7
        uint32_t PEIM       :1;     // 8
        uint32_t BEIM       :1;     // 9
        uint32_t OEIM       :1;     // 10
        uint32_t reserved   :21;    // 11:31
    }bits;
}UARTIMSC_t;

//Raw Interrupt Status Register bits
typedef union UARTRIS_t
{
    uint32_t all;
    struct
    {
        uint32_t RIRMIS     :1;     // 0
        uint32_t CTSRMIS    :1;     // 1
        uint32_t DCDRMIS    :1;     // 2
        uint32_t DSRRMIS    :1;     // 3
        uint32_t RXRIS      :1;     // 4
        uint32_t TXRIS      :1;     // 5
        uint32_t RTRIS      :1;     // 6
        uint32_t FERIS      :1;     // 7
        uint32_t PERIS      :1;     // 8
        uint32_t BERIS      :1;     // 9
        uint32_t OERIS      :1;     // 10
        uint32_t reserved   :21     // 11:31
    }bits;
}UARTRIS_t;

//Masked Interrupt Status Register bits
typedef union UARTMIS_t
{
    uint32_t all;
    struct
    {
        uint32_t RIMMIS     :1;     // 0
        uint32_t CTSMMIS    :1;     // 1
        uint32_t DCDMMIS    :1;     // 2
        uint32_t DSRMMIS    :1;     // 3
        uint32_t RXMIS      :1;     // 4
        uint32_t TXMIS      :1;     // 5
        uint32_t RTMIS      :1;     // 6
        uint32_t FEMIS      :1;     // 7
        uint32_t PEMIS      :1;     // 8
        uint32_t BEMIS      :1;     // 9
        uint32_t OEMIS      :1;     // 10
        uint32_t reserved   :21;    // 11:31
    }bits;
}UARTMIS_t;

//Interrupt Clear Register bits
typedef union UARTICR_t
{
    uint32_t all;
    struct
    {
        uint32_t RIMIC      :1;     // 0
        uint32_t CTSMIC     :1;     // 1
        uint32_t DCDMIC     :1;     // 2
        uint32_t DSRMIC     :1;     // 3
        uint32_t RXIC       :1;     // 4
        uint32_t TXIC       :1;     // 5
        uint32_t RTIC       :1;     // 6
        uint32_t FEIC       :1;     // 7
        uint32_t PEIC       :1;     // 8
        uint32_t BEIC       :1;     // 9
        uint32_t OEIC       :1;     // 10
        uint32_t reserved   :21;    // 11:31
    }bits;
}UARTICR_t;


//DMA Control Register bits
typedef union UARTDMACR_t
{
    uint32_t all;
    struct
    {
        uint32_t RXDMAE     :1;     // 0
        uint32_t TXDMAE     :1;     // 1
        uint32_t DMAONERR   :1;     // 2
        uint32_t reserved   :29;    // 3:31       
    }bits;
    
}UARTDMACR_t;

//PL011
typedef struct PL011_t
{
    UARTDR_t        uartdr;             //0x000
    UARTRSR_t       uartrsr;            //0x004
    uint32_t        reserved0[4];       //0x008-0x014
    UARTFR_t        uartfr;             //0x018
    uint32_t        reserved1;          //0x01C
    UARTILPR_t      uartilpr;           //0x020
    UARTIBRD_t      uartibrd;           //0x024
    UARTFBRD_t      uartfbrd;           //0x028
    UARTLCR_H_t     uartlcr_h;          //0x02C
    UARTCR_t        uartcr;             //0x030
    UARTIFLS_t      uartifls;           //0x034
    UARTIMSC_t      uartimsc;           //0x038
    UARTRIS_t       uartris;            //0x03C
    UARTMIS_t       uartmis;            //0x040
    UARTICR_t       uarticr;            //0x044
    UARTDMACR_t     uartdmacr;          //0x048    
}PL011_t;




#endif //_UART_H