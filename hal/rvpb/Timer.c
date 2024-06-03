#include "stdint.h"
#include "Timer.h"
#include "HalTimer.h"
#include "HalInterrupt.h"

extern volatile Timer_t*    Timer;

static void interrupt_handler(void);

static uint32_t interval_1ms_counter;   // 전역변수, 핸들러에서 1씩 증가용 카운터 변수        

void Hal_timer_init(void)
{
    // interrupt reset
    Timer->timerxcontrol.bits.TimerEn       = 0;            //Timer module disable
    Timer->timerxcontrol.bits.TimerMode     = 0;            // free-running mode
    Timer->timerxcontrol.bits.OneShot       = 0;            // wrapping mode
    Timer->timerxcontrol.bits.TimerSize     = 0;            // 16bit counter
    Timer->timerxcontrol.bits.TimerPre      = 0;            // prescaler 1
    Timer->timerxcontrol.bits.IntEnable     = 1;            // Timer module interrupt enable
    Timer->timerxload                       = 0;            // 
    Timer->timerxvalue                      = 0xFFFFFFFF;   //

    // set periodic mode
    // periodic mode 는 timerxload값이 timerxvlaue로 복사되어
    // 타이머가 켜지면 timerxvalue값이 감소되면서 0이 되면 인터럽트 발생한다.
    Timer->timerxcontrol.bits.TimerMode     = 1;            // periodic mode
    Timer->timerxcontrol.bits.TimerSize     = 1;            // 32bit counter
    Timer->timerxcontrol.bits.OneShot       = 0;            // wrapping mode
    Timer->timerxcontrol.bits.TimerPre      = 0;            // prescaler 1
    Timer->timerxcontrol.bits.IntEnable     = 1;            // Timer module interrupt enable

    uint32_t interval_1ms = TIMER_1MZ_INTERVAL / 1000;      //  (1024 x 1024) / 1000

    Timer->timerxload                       = interval_1ms; 
    Timer->timerxcontrol.bits.TimerEn       = 1;            // timer interrupt enable

    interval_1ms_counter = 0;
}

static void interrupt_handler(void)
{
    interval_1ms_counter++;

    Timer->timerxintclr = 1;        //
}