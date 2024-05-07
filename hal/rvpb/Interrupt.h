#ifndef HAL_INTERRUPT_H
#define HAL_INTERRUPT_H

#include "stdint.h"


#define GIC_CPU_InterFaceReg_BASE               0x1E000000      //CPU INterface Base Address
#define GIC_DistriButorReg_BASE                 0x1E001000      //distributor Base Address

#define GIC_PRIORITY_MASK_NONE                  0xF

#define GIC_IRQ_START                           32
#define GIC_IRQ_END                             95



/*
    @ CPU control register
    31                                  1   0
    ------------------------------------|---|
    |      Reserved                     |   |
    |                                   |   |
                                          ^
    --------------------------------------|
                            Enable--------|
*/
typedef union CPU_control_t
{
    uint32_t all;
    struct
    {
        uint32_t Enable     :1;     // 0
        uint32_t Reserved   :31;    // 1:31
    }bits;
    
}CPU_control_t;

/*
    @ Priority mask register
    31                                  8 7         4 3       0
    ------------------------------------| |---------| |-------|
    |        Reserved                   | |         | |  SBZ  |  
    |                                   | |         | |       |
                                               ^
    -------------------------------------------|
                            Priority mask -----|
*/
typedef union Priority_mask_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved1          :4;     // 0:3
        uint32_t Priority_mask      :4;     // 4:7
        uint32_t Reserved2          :24;    // 8:31
    }bits;
}Priority_mask_t;

/*
    @ Binary point register
    31                                             3 2      0
    -----------------------------------------------| |------|
    |       Reserved                               | |      |
    |                                              | |      |
                                                        ^
    ----------------------------------------------------|
                                 Binary point-----------|

*/
typedef union Binary_point_t
{
    uint32_t all;
    struct
    {
        uint32_t Binary_point       :3;     // 0:2
        uint32_t Reserved           :29;    // 3:31    
    }bits;
    
}Binary_point_t;

/*
    @ Interrupt acknowledge
    31                          13 12       10 9                    0
    -----------------------------| |---------| |--------------------|
    |       Reserved             | |         | | Interrupted ID     |
    |                            | |         | |                    |
                                       ^
    -----------------------------------|
                CPU source ID ---------|
*/
typedef union Interrupt_acknowledge_t
{
    uint32_t all;
    struct
    {
        uint32_t InterruptID            :10;    // 0:9
        uint32_t CPUsourceID            :3;     // 10:12
        uint32_t Reserved               :19;    // 13:31
    }bits;
}Interrupt_acknowledge_t;

/*
    @ End of interrupt
    31                          13 12       10 9                    0
    -----------------------------| |---------| |--------------------|
    |       Reserved             | |         | | Interrupted ID     |
    |                            | |         | |                    |
                                       ^
    -----------------------------------|
                CPU source ID ---------|
*/
typedef union End_of_interrupt_t
{
    uint32_t all;
    struct
    {
        uint32_t InterruptID            :10;    // 0:9
        uint32_t CPUsourceID            :3;     // 10:12
        uint32_t Reserved               :19;    // 13:31
    }bits;
}End_of_interrupt_t;


/*
    @ Running interrupt
    31                          8 7           4 3                 0
    ----------------------------| |-----------| |-----------------|
    |      Reserved             | | Priority  | |  SBZ            |
    --------------------------------------------------------------
*/
typedef union Running_interrupt_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved1          :4;     // 0:3
        uint32_t Priority           :4;     // 4:7
        uint32_t Reserved2          :24;    // 8:31
    }bits;
}Running_interrupt_t;

/*
    @ Highest pendiing interrupt
    31                          13 12       10 9                    0
    -----------------------------| |---------| |--------------------|
    |       Reserved             | |         | | Interrupted ID     |
    |                            | |         | |                    |
                                       ^
    -----------------------------------|
                CPU source ID ---------|    
*/
typedef union Highest_pending_interrupt_t
{
    uint32_t all;
    struct
    {
        uint32_t InterruptID            :10;    // 0:9
        uint32_t CPUsourceID            :3;     // 10:12
        uint32_t Reserved               :19;    // 13:31
    }bits;
}Highest_pending_interrupt_t;

//GIC CPU Interface
typedef struct GIC_CPU_InterFace_t
{   
    CPU_control_t                   GIC_CPU_control;                // 0x000
    Priority_mask_t                 GIC_Priority_mask;              // 0x004
    Binary_point_t                  GIC_Binary_point_t;             // 0x008
    Interrupt_acknowledge_t         GIC_Interrupt_acknowledge;      // 0x00C
    End_of_interrupt_t              GIC_End_of_interrupt;           // 0x010
    Running_interrupt_t             GIC_Running_interrupt;          // 0x014
    Highest_pending_interrupt_t     GIC_Highest_pending_interrupt;  // 0x018
}GIC_CPU_InterFace_t;



/*
    @ Distributor control register
    31                                              1  0
    ------------------------------------------------|  |
    |           Reserved                            |  |
    |                                               |  |      
                                                      ^
                                        Enable -------|
*/
typedef union Distributor_control_t
{
    uint32_t all;
    struct
    {
        uint32_t Enable                 :1;     // 0
        uint32_t Reserved               :31;    // 1:31
    }bits;
}Distributor_control_t;

/*
    @ Controller type register
    31                          8 7           5 4                 0
    ----------------------------| |-----------| |-----------------|
    |      Reserved             | | CPU number| | ID lines number |
    --------------------------------------------------------------    
*/
typedef union Controller_type_t
{
    uint32_t all;
    struct
    {
        uint32_t ID_lines_number                :5;  // 0:4
        uint32_t CPU_number                     :3;  // 4:7
        uint32_t reserved                       :24; // 8:31
    }bits;
}Controller_type_t;


/*
    @ Set enable0 register
        - The Set-enable0 register at address offset 0x100 is reserved for private use in the PB-A8
*/
typedef union Set_enable0_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved            :32; // 0:31
    }bits; 
}Set_enable0_t;

/*
    @ Set enable1 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Enable(ID63 to ID32)              |
    ---------------------------------------------------------------|
*/
typedef union Set_enable1_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Enable            :32; // 0:31
    }bits; 
}Set_enable1_t;

/*
    @ Set enable2 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Enable(ID95 to ID64)              |
    ---------------------------------------------------------------|
*/
typedef union Set_enable2_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Enable            :32; // 0:31
    }bits; 
}Set_enable2_t;

/*
    @ Clear enable0 register
        - The Clear-enable0 register at address offset 0x180 is reserved for private use in the PB-A8
*/
typedef union Clear_enable0_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved            :32; // 0:31
    }bits; 
}Clear_enable0_t;


/*
    @ Clear enable1 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Enable(ID63 to ID32)              |
    ---------------------------------------------------------------|
*/
typedef union Clear_enable1_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Enable            :32; // 0:31
    }bits; 
}Clear_enable1_t;

/*
    @ Clear enable2 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Enable(ID95 to ID64)              |
    ---------------------------------------------------------------|
*/
typedef union Clear_enable2_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Enable            :32; // 0:31
    }bits; 
}Clear_enable2_t;

/*
    @ Set-pending0 register
        - The Set-pending0 register at address offset 0x200 is reserved for private use in the PB-A8
*/
typedef union Set_pending0_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved            :32; // 0:31
    }bits; 
}Set_pending0_t;

/*
    @ Set-pending1 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Pending(ID63 to ID32)             |
    ---------------------------------------------------------------|
*/
typedef union Set_pending1_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Pending            :32; // 0:31
    }bits; 
}Set_pending1_t;

/*
    @ The Set-pending2 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Pending(ID95 to ID64)             |
    ---------------------------------------------------------------|
*/
typedef union Set_pending2_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Pending            :32; // 0:31
    }bits; 
}Set_pending2_t;

/*
    @ Clear-pending0 register
        - The Clear-pending0 register at address offset 0x280 is reserved for private use in the PB-A8
*/
typedef union Clear_pending0_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved            :32; // 0:31
    }bits; 
}Clear_pending0_t;

/*
    @ Clear-pending1 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Pending(ID63 to ID32)             |
    ---------------------------------------------------------------|
*/
typedef union Clear_pending1_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Pending            :32; // 0:31
    }bits; 
}Clear_pending1_t;

/*
    @ The Clear-pending2 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Pending(ID95 to ID64)             |
    ---------------------------------------------------------------|
*/
typedef union Clear_pending2_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Pending            :32; // 0:31
    }bits; 
}Clear_pending2_t;

/*
    @ Active0 register
        - The Active0 register at address offset 0x300 is reserved for private use in the PB-A8
*/
typedef union Active0_t
{
    uint32_t all;
    struct
    {
        uint32_t Reserved            :32; // 0:31
    }bits; 
}Active0_t;

/*
    @ Active1 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Active(ID63 to ID32)              |
    ---------------------------------------------------------------|
*/
typedef union Active1_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Active            :32; // 0:31
    }bits; 
}Active1_t;

/*
    @ Active2 register
    31                                                             0
    ---------------------------------------------------------------|
    |                  Interrupt Active(ID95 to ID64)              |
    ---------------------------------------------------------------|
*/
typedef union Active2_t
{
    uint32_t all;
    struct
    {
        uint32_t Interrupt_Active            :32; // 0:31
    }bits; 
}Active2_t;




//GIC Distribution registers
typedef struct GIC_Ditribution_t
{
    Distributor_control_t           Dis_Distributor_control;        // 0x000
    Controller_type_t               Dis_Controller_type;            // 0x004
    uint32_t                        Reserved0[62];                  // 0x008 - 0x0FC
    uint32_t                        Reserved1;                      // 0x100
//  Set_enable0_t                   Dis_Set_enable0;                // 0x100
    uint32_t                        Dis_Set_enable1;                // 0x104
    uint32_t                        Dis_Set_enable2;                // 0x108    
    uint32_t                        Reserved2[29];                  // 0x10C - 0x17C
    uint32_t                        Reserved3;                      // 0x180
//  Clear_enable0_t                 Dis_Clear_enable0;              // 0x180
    uint32_t                        Dis_Clear_enable1;              // 0x184
    uint32_t                        Dis_Clear_enable2;              // 0x188
//  uint32_t                        Reserved2[29];                  // 0x18C - 0x1FC
//    Set_pending0_t                  Dis_Set_pending0;               // 0x200
//    Set_pending1_t                  Dis_Set_pending1;               // 0x204
//    Set_pending2_t                  Dis_Set_pending2;               // 0x208
//    uint32_t                        Reserved3[29];                  // 0x20C - 0x27C
//    Clear_pending0_t                Dis_Clear_pending0;             // 0x280
//    Clear_pending1_t                Dis_Clear_pending1;             // 0x284
//    Clear_pending2_t                Dis_Clear_pending2;             // 0x288
//    uint32_t                        Reserved4[29];                  // 0x28C - 0x2FC
//    Active0_t                       Dis_Active0;                    // 0x300
//    Active1_t                       Dis_Active1;                    // 0x304
//    Active2_t                       Dis_Active2;                    // 0x308
//    uint32_t                        Reserved5[61];                  // 0x30C - 0x3FC
//    Priority_t                      Dis_Priority[24];               // 0x400 - 0x45C
//    uint32_t                        Reserved6[232];                 // 0x460 - 0x7FC
//    CPU_targets_t                   Dis_CPU_targets[24];            // 0x800 - 0x85C
//    uint32_t                        Reserved7[232];                 // 0x860 - 0xBFC
//    Configuration_t                 Dis_Configuration[6];           // 0xC00 - 0xC14
//    uint32_t                        Reserved8[186];                 // 0xC18 - 0xEFC
//    Software_interrupt_t            Dis_Software_interrupt;         // 0xF00
//    uint32_t                        Reserved9[63];                 // 0xF04 - 0xFFC

}GIC_Ditribution_t;

#endif /* HAL_INTERRUPT_H */