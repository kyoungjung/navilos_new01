#include "stdbool.h"
#include "stdint.h"
#include "HalInterrupt.h"

/*
    @ Define IRQ exception handler function    
*/
__attribute__ ((interrupt ("IRQ"))) void Irq_Handler(void)
{
    Hal_interrupt_run_handler();    
}

/*
    @ Define FIQ exception handler function
*/
__attribute__ ((interrupt ("FIQ"))) void Fiq_Handler(void)
{
    while(true);
}