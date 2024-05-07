#include "armcpu.h"

void enable_irq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS r0, cpsr");
    __asm__("BIC r1, r0, #0x80");   //BIC : 해당 비트를 0으로 클리어
    __asm__("MSR cpsr, r1");
    __asm__("POP {r0, r1}");
}

void enable_frq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS r0, cpsr");
    __asm__("BIC r1, r0, #0x40");   //BIC : 해당 비트를 0으로 클리어
    __asm__("MSR cpsr, r1");
    __asm__("POP {r0, r1}");
}

void disable_irq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS r0, cpsr");
    __asm__("ORR r1, r0, #0x80");   //ORR : 해당 비트를 1로 설정
    __asm__("MSR cpsr, r1");
    __asm__("POP {r0, r1}");
}

void disable_frq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS r0, cpsr");
    __asm__("ORR r1, r0, #0x40");   //ORR : 해당 비트를 1로 설정
    __asm__("MSR cpsr, r1");
    __asm__("POP {r0, r1}");
}