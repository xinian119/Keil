#include "Delay.h"
#include <REGX52.H>
#include <intrins.h>
#include "I2C.h"

bit bdata IIC_ERROR;

sbit SCL = P1 ^ 0;
sbit SDA = P1 ^ 1;

void IIC_Start()
{
  SDA = 1;
  SCL = 1;
  Delay4us();
  SDA = 0;
  Delay4us();
  SCL = 0;
}

void IIC_Stop()
{
  SDA = 0;
  SCL = 1;
  Delay4us();
  SDA = 1;
  Delay4us();
  SCL = 0;
}

void Slave_ACK()
{
  SDA = 0;
  SCL = 1;
  Delay4us();
  SCL = 0;
  SDA = 1;
}

void Slave_NOACK()
{
  SDA = 1;
  SCL = 1;
  Delay4us();
  SCL = 0;
  SDA = 0;
}

void IIC_SendByte(unsigned char wd)
{
  unsigned char i;
  for (i = 0;i < 8;i++)
  {
    SDA = (bit) (wd & 0x80);
    _nop_();
    _nop_();
    SCL = 1;
    Delay4us();
    SCL = 0;
    wd <<= 1;
  }
  Delay4us();
  SDA = 1;
  SCL = 1;
  Delay4us();

  IIC_ERROR = SDA;
  SCL = 0;
  Delay4us();
}

unsigned char IIC_ReceiveByte()
{
  unsigned char i, rd = 0x00;
  for (i = 0;i < 8;i++)
  {
    SCL = 1;
    rd <<= 1;
    rd |= SDA;
    Delay4us();
    SCL = 0;
    Delay4us();
  }
  SCL = 0;
  Delay4us();
  return rd;
}

bit Get_IIC_ERROR(void)
{
  return IIC_ERROR;
}