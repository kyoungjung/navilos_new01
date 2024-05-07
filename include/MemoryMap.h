#define INST_ADDR_START                 0
#define USRSYS_STACK_START              0x00100000
#define SVC_STACK_START                 0x00300000
#define IRQ_STACK_START                 0x00400000
#define FIQ_STACK_START                 0x00500000
#define ABT_STACK_START                 0x00600000
#define UND_STACK_START                 0x00700000
#define TASK_STACK_START                0x00800000
#define GLOBAL_ADDR_START               0x04800000
#define DALLOC_ADDR_START               0x04900000

#define INST_MEM_SIZE                   (USRSYS_STACK_START - INST_ADDR_START)      // 1MB
#define USRSYS_STACK_SIZE               (SVC_STACK_START - USRSYS_STACK_START)      // 2MB
#define SVC_STACK_SIZE                  (IRQ_STACK_START - SVC_STACK_START)         // 1MB
#define IRQ_STACK_SIZE                  (FIQ_STACK_START - IRQ_STACK_START)         // 1MB
#define FIQ_STACK_SIZE                  (ABT_STACK_START - FIQ_STACK_START)         // 1MB
#define ABT_STACK_SIZE                  (UND_STACK_START - ABT_STACK_START)         // 1MB
#define UND_STACK_SIZE                  (TASK_STACK_START - UND_STACK_START)        // 1MB
#define TASK_STACK_SIZE                 (GLOBAL_ADDR_START - TASK_STACK_START)      // 64MB
#define GLOBAL_ADDR_SIZE                (DALLOC_ADDR_START - GLOBAL_ADDR_START)     // 1MB
#define DALLOC_ADDR_SIZE                (55 * 1024 * 1024)                          // 55MB

//
#define USRSYS_STACK_TOP                (USRSYS_STACK_START + USRSYS_STACK_SIZE) - 4
#define SVC_STACK_TOP                   (SVC_STACK_START + SVC_STACK_SIZE) - 4
#define IRQ_STACK_TOP                   (IRQ_STACK_START + IRQ_STACK_SIZE) - 4
#define FIQ_STACK_TOP                   (FIQ_STACK_START + FIQ_STACK_SIZE) - 4
#define ABT_STACK_TOP                   (ABT_STACK_START + ABT_STACK_SIZE) - 4
#define UND_STACK_TOP                   (UND_STACK_START + UND_STACK_SIZE) - 4
#define TASK_STACK_TOP                  (TASK_STACK_START + TASK_STACK_SIZE) - 4