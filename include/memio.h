#ifndef _MEMIO_H
#define _MEMIO_H

//한비트 설정
#define SET_BIT(data,loc)                   ((data) |=  (0x1 << (loc)))
//한비트 클리어
#define CLR_BIT(data,loc)                   ((data) &= ~(0x1 << (loc)))

#endif /*_MEMIO_H*/