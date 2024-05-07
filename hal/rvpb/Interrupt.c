#include "stdint.h"
#include "memio.h"
#include "Interrupt.h"
#include "HalInterrupt.h"
#include "armcpu.h"

extern volatile GIC_CPU_InterFace_t* GicCpu;
extern volatile GIC_Ditribution_t* GicDist;

//인터럽트 핸들러를 저장할 변수, 함수포인터 255개를 저장할 수 있는 배열
static InterHdlr_fptr sHandlers[INTERRUPT_HANDLER_NUM];

void Hal_interrupt_init(void)
{
    GicCpu->GIC_CPU_control.bits.Enable = 1;                                    //CPU INterface 인터럽트 컨트롤러를 활성화 한다.
    GicCpu->GIC_Priority_mask.bits.Priority_mask = GIC_PRIORITY_MASK_NONE;
    GicDist->Dis_Distributor_control.bits.Enable = 1;                           //Distributor 인터럽트 컨트롤러를 활성화 한다.

    for(uint32_t i=0;i<INTERRUPT_HANDLER_NUM;i++)
    {
        sHandlers[i] = NULL;    //함수 포인터변수 배열 초기화
    }

    enable_irq();    
}

/*
    GIC_IRQ_START                           32
    GIC_IRQ_END                             95

    @ func : Hal_interrupt_enable
        - 인터럽트 활성화
    @ in
        - uint32_t interrupt_num
            > 활성화할 인터럽트 번호(ID)
*/
void Hal_interrupt_enable(uint32_t interrupt_num)
{
    //인터럽트 번호 범위 이외의 인터럽트 번호가 입력되면 리턴...(예외처리)
    if((interrupt_num < GIC_IRQ_START) || (interrupt_num > GIC_IRQ_END))
    {
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START; 

    if(bit_num < GIC_IRQ_START)
    {
        //interrupt id가 32 ~ 63은
        //Distributor register의 Set-enable1 레지스터를 설정
        SET_BIT(GicDist->Dis_Set_enable1, bit_num);
    }
    else
    {
        //interrupt id가 64 ~ 95는
        //Distributor register의 Set-enable2 레지스터를 설정
        bit_num -= GIC_IRQ_START;
        SET_BIT(GicDist->Dis_Set_enable2, bit_num);
    }
}

/*
    @ func : Hal_interrupt_disable
        - 인터럽트 비활성화
    @ in
        - uint32_t interrupt_num
            > 비활성화할 인터럽트 번호(ID)
*/
void Hal_interrupt_disable(uint32_t interrupt_num)
{
    if((interrupt_num < GIC_IRQ_START) || (interrupt_num > GIC_IRQ_END))
    {
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if(bit_num < GIC_IRQ_START)
    {
        CLR_BIT(GicDist->Dis_Set_enable1, bit_num);
    }
    else
    {
        bit_num -= GIC_IRQ_START;
        CLR_BIT(GicDist->Dis_Set_enable2, bit_num);
    }
}

/*
    @ func : Hal_interrupt_register_handler
        - 인터럽트 핸들러 등록
    @ in
        - InterHdler_fpter handler
            > 등록할 핸들러 함수 포인터
        - uint32_t interrupt_num
            > 등록할 인터럽트 번호(ID)
*/
void Hal_interrupt_register_handler(InterHdlr_fptr handler, uint32_t interrupt_num)
{
    sHandlers[interrupt_num] = handler;
}

/*
    @ func : Hal_interrupt_run_handler
        - 인터럽트 핸들러 실행
*/
void Hal_interrupt_run_handler(void)
{
    //현재 하드웨어에서 대기중인 인터럽트 ID를 불러온다.
    uint32_t interrupt_num = GicCpu->GIC_Interrupt_acknowledge.bits.InterruptID;

    if(sHandlers[interrupt_num] != NULL)    //해당 인터럽트 ID의 함수포인터가 null이 아니면
    {
        sHandlers[interrupt_num]();     //인터럽트 핸들러(함수,기능) 동작수행
    }

    //인터럽트 ID에 해당하는 인터럽트 처리가 끝났음을 알리기 위해 해당 인터럽트 ID를
    //End of Interrupt에 저장한다.
    GicCpu->GIC_End_of_interrupt.bits.InterruptID = interrupt_num;
}