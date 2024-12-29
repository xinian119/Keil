#include "I2C.h"
#include "Delay.h"
#include "AD.h"
void ADC_PCF8591(unsigned char CtrlByte)
{
  //	uchar i;
  IIC_Start();
  IIC_SendByte(0x90);
  if (Get_IIC_ERROR() == 1) return;

  IIC_SendByte(CtrlByte);
  if (Get_IIC_ERROR() == 1) return;


  IIC_Start();
  IIC_SendByte(0x91);
  if (Get_IIC_ERROR() == 1) return;
  Recv_Buffer[0] = IIC_ReceiveByte();
  Slave_ACK();
  Slave_NOACK();
  IIC_Stop();
}

void DAC_PCF8591(unsigned char CtrlByte, unsigned char dat)
{
  IIC_Start();
  Delay4us();
  IIC_SendByte(0x90);
  if (Get_IIC_ERROR() == 1) return;
  IIC_SendByte(CtrlByte);
  if (Get_IIC_ERROR() == 1) return;
  IIC_SendByte(dat);
  if (Get_IIC_ERROR() == 1) return;
  IIC_Stop();
  Delay4us();
  Delay4us();
}
