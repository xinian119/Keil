#ifndef __UART_H__
#define __UART_H__

void Uart1_Init(void);
void Uart1_SendByte(unsigned char Byte);
unsigned char Uart1_RecByte(void);
void Uart1_SendAD(void);

#endif

