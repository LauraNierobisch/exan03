#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>
#include<limits.h>

void put_s(char *s, int *count)
{
    if(!s)
        s = "(null)";
    while(*s)
    {
        write(1, s++, 1);
        (*count)++;
    }
}

void putx(unsigned int n, int *count)
{
    char *hex = "0123456789abcdef";
    if(n >= 16)
        putx((n/16), count);
    write(1, &hex[n % 16], 1);
    (*count)++;
}
void putd(int n, int *count)
{
    if(n == -2147483648)
    {
        put_s("-2147483648",count);
        return;
    }
    if(n < 0)
    {
        write(1, "-", 1);
        (*count)++;
        n = -n;
    }
    if(n > 9)
        putd(n / 10, count);
       n =  n % 10 + '0';
    write(1, &n, 1);
    (*count)++;
}
int ft_printf(const char *format, ...)
{
    va_list args;
    int num = 0;
    va_start(args, format);
    while(*format)
    {
        if(*format == '%' && *(format + 1))
        {
            format++;
            if(*format == 's')
                put_s(va_arg(args,char *), &num);
            else if (*format == 'd')
                putd(va_arg(args, int), &num);
            else if(*format == 'x')
                putx(va_arg(args, unsigned), &num);
            else 
            {
                write(1, format, 1);
                num++;
            }
        }
        else
        {
            write(1, format, 1);
            num++;
        }
        format++;
    }
    va_end(args);
    return(num);
}

int main()
{
    int d = -44;
    ft_printf("hallo %d", d );
    return(0);
}