#include <REGX52.H>
#include "Delay.h"
void Uart1_Init(void)	//9600bps@11.0592MHz
{
	PCON &= 0x7F;
	SCON = 0x50;
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xFD;
	TH1 = 0xFD;
	ET1 = 0;
	TR1 = 1;
	EA = 1;
	ES = 1;
}

void Uart1_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while (!TI);
	TI = 0;
}

unsigned char Uart1_RecByte(void)
{
	unsigned char RecByte;
	while (!RI);
	RI = 0;
	RecByte = SBUF;
	return RecByte;
}

void Uart1_SendAD(void)
{
	Uart1_SendByte('V');
	Uart1_SendByte('=');
}



