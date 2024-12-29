#ifndef _AD_H
#define _AD_H

unsigned char Recv_Buffer[4];

void ADC_PCF8591(unsigned char CtrlByte);
void DAC_PCF8591(unsigned char CtrlByte, unsigned char dat);

#endif 

