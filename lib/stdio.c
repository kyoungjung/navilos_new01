#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"

#define PRINTF_BUF_LEN  1024

static char printf_buf[PRINTF_BUF_LEN];   // 1KB

//uint32_t vsprintf(char *buf, const char* format, va_list arg);
//uint32_t utoa(char* buf, uint32_t val, utoa_t base);

/*
    @ 문자열 출력 함수
*/
uint32_t Hal_uart_put_string(const char *str)
{
    uint32_t c = 0;
    while(*str != '\0') //널 문자 나오기 전까지 루프실행
    {        
        Hal_uart_put_char(*str++);
        c++;
    }
    return c;
}


/*
    @ printf 사용자 함수
        - %u, %x등의 형식 문자 처리하는 코드는 vsprintf()에서 구현
        - 가변인자를 처리는 주로 va_list라는 자료형과 va_start, va_end, va_arg 매크로 사용
        - 구현범위
            > %3u나 %03u와 같이 출력하는 숫자의 자릿수를 고정하거나 남는 자릿수에 0을 채우는
              옵션은 구현하지 않는다.
            > %u, %x같은 부가 옵션이 없는 형식만 허용.
            > %c, %u, %x, %s만 구현
*/
uint32_t debug_printf(const char* format, ...)
{
    va_list     args;    

    va_start(args, format);
    vsprintf(printf_buf, format, args);
    va_end(args);

    return Hal_uart_put_string(printf_buf);
}

uint32_t vsprintf(char *buf, const char* format, va_list arg)
{
    uint32_t c = 0;

    char        ch;
    char*       str;
    uint32_t    uint;
    uint32_t    hex;

    for(uint32_t i=0;format[i];i++)
    {
        if(format[i] == '%')    //문자 '%'가 입력됬다면
        {
            i++;
            switch(format[i])
            {
                case 'c' :
                //arg위치에서 int32_t 타입 값을 읽어서 ch에 저장
                //char 타입으로 형변환
                ch = (char)va_arg(arg, int32_t);
                buf[c++] = ch;
                break;

                case 's' :
                //arg위치에서 char* 타입 값을 읽어서 str 포인터 변수에 저장
                str = (char*)va_arg(arg, char*);                                
                if(str == NULL)
                {
                    //str이 NULL이면 str에 (null)문자열포인터 저장
                    str = "(null)";
                }
                while(*str)
                {
                    //str이 null이 될때까지 읽어서 버퍼에 저장
                    //str이 null이면 루트를 빠져나온다.
                    buf[c++] = (*str++);
                }
                break;

                case 'u' :
                uint = (uint32_t)va_arg(arg, uint32_t);                
                c += utoa(&buf[c], uint, utoa_dec);
                break;

                case 'x' :
                hex = (uint32_t)va_arg(arg, uint32_t);                
                c += utoa(&buf[c], hex, utoa_hex);
                break;
            }
        }
        else
        {
            buf[c++] = format[i];
        }
    }

    //버퍼 카운터가 버퍼 길이 이상이 되면
    if(c >= PRINTF_BUF_LEN)
    {        
        buf[0] = '\0';
        return 0;
    }

    buf[c] = '\0';

    return c;
}

/*

    @ 부호없는 정수를 문자로 변환
        - buf : 변환 결과가 저장된 버퍼
        - val : 부호없는 정수 입력인자
        - base : 변환형태가 10진형태 혹은 16진수형태인지를 알려주는 인자
    typedef enum utoa_t
    {
        utoa_dec = 10,
        utoa_hex = 16,
    }utoa_t;
*/
uint32_t utoa(char* buf, uint32_t val, utoa_t base)
{
    uint32_t    c = 0;
    int32_t     idx = 0;
    char        tmp[11];

    do
    {
        //uint32_t 타입 val값을 입력인자 base맞는 값으로 나누고 나머지를 t에 저장
        uint32_t t = val % (uint32_t)base;
        if(t >= 10)
        {
            //'A' : 65, '0' : 48
            t += 'A' - '0' - 10;    //7
        }
        //t가 10 미만이면, '0' : 48을 t에 더해준다.
        tmp[idx] = (t + '0');
        val /= base;    //val = val / base;
        idx++;
    }while(val);

    // reverse
    idx--;
    while(idx >= 0)
    {
        buf[c++] = tmp[idx];
        idx--;
    }

    return c;
}