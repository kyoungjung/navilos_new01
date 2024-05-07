#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

#define TIMER_CPU_BASE                  0x10011000
#define TIMER_INTERRUPT                 36

#define TIMER_FREERNNING                0
#define TIMER_PERIOIC                   1

#define TIMER_16BITS_COUNTER            0
#define TIMER_32BITS_COUNTER            1

#define TIMER_1MZ_INTERVAL              (1024 * 1024)


typedef union TimerXControl_t
{
    uint32_t all;
    struct
    {
        uint32_t OneShot            :1;     // 0
        uint32_t TimerSize          :1;     // 1
        uint32_t TimerPre           :2;     // 2:3
        uint32_t reserved1          :1;     // 4
        uint32_t IntEnable          :1;     // 5
        uint32_t TimerMode          :1;     // 6
        uint32_t TimerEn            :1;     // 7
        uint32_t reserved2          :24;    // 8 : 31
    }bits;
}TimerXControl_t;

typedef union TimerXRIS_t
{
    uint32_t all;
    struct
    {
        uint32_t TimerXRIS_t        :1;     // 0
        uint32_t reserved           :31;    // 1 : 31
    }bits;
}TimerXRIS_t;

typedef union TimerXMIS_t
{
    uint32_t all;
    struct
    {
        uint32_t TimerXMIS          :1;     // 0
        uint32_t reserned           :31;    // 1 : 31
    }bits;
}TimerXMIS_t

typedef struct Timer_t
{
    uint32_t                    timerxload;             // 0x00
    uint32_t                    timerxvalue;            // 0x04
    TimerXControl_t             timerxcontrol;          // 0x08
    uint32_t                    timerxintclr;           // 0x0C
    TimerXRIS_t                 timerxris;              // 0x10
    TimerXMIS_t                 timerxmis;              // 0x14
    uint32_t                    timerxbgload;           // 0x18
}Timer_t;

#endif //_TIMER_H