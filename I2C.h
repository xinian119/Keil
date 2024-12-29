#ifndef _I2C_H
#define _I2C_H

void IIC_Start();
void IIC_Stop();
void Slave_ACK();
void Slave_NOACK();
bit Get_IIC_ERROR(void);
void IIC_SendByte(unsigned char wd);
unsigned char IIC_ReceiveByte();

#endif // !1


