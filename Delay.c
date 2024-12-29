#include <intrins.h>

void Delayms(unsigned char t) //@11.0592MHz
{
    unsigned char data i, j;
    while (t--)
    {
        i = 15;
        j = 90;
        do
        {
            while (--j);
        } while (--i);
    }
}

void Delay4us(void)
{
    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}

void Delay(unsigned int ms)
{
    unsigned char i;
    while (ms--)	for (i = 0;i < 250;i++) Delay4us();
}
