#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include <intrins.h>
#include "UART.h"

#define uint unsigned int
#define uchar unsigned char

uchar StartFlag = 1;

sbit CH0 = P1 ^ 2;
sbit CH1 = P1 ^ 3;
sbit CH2 = P1 ^ 4;
sbit CH3 = P1 ^ 5;
sbit SCL = P1 ^ 0;
sbit SDA = P1 ^ 1;

unsigned char An[8] = { 0x04,0x1f,0x11,0x0a,0x1f,0x04,0x1B,0x00 };
unsigned char Gon[8] = { 0x00,0x1f,0x04,0x04,0x04,0x04,0x1f,0x00 };
unsigned char Da[8] = { 0x04,0x04,0x1f,0x04,0x04,0x0a,0x11,0x00 };

uchar Recv_Buffer[4];
uint Voltage[] = { '0','0','0' };
bit bdata IIC_ERROR;
uchar LCD_Line_1[] = { "  CHX-?.??V     " };
//uchar LCD_Line_2[] = { " PCF8597 AD-DA  " };
uchar Rec = 0;

void Convert_To_Voltage(uchar val)
{
	uchar Tmp;
	Voltage[2] = val / 51 + '0';
	Tmp = val % 51 * 10;
	Voltage[1] = Tmp / 51 + '0';
	Tmp = Tmp % 51 * 10;
	Voltage[0] = Tmp / 51 + '0';
}

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

void IIC_SendByte(uchar wd)
{
	uchar i;
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

uchar IIC_ReceiveByte()
{
	uchar i, rd = 0x00;
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

void ADC_PCF8591(uchar CtrlByte)
{
	//	uchar i;
	IIC_Start();
	IIC_SendByte(0x90);
	if (IIC_ERROR == 1) return;

	IIC_SendByte(CtrlByte);
	if (IIC_ERROR == 1) return;


	IIC_Start();
	IIC_SendByte(0x91);
	if (IIC_ERROR == 1) return;
	Recv_Buffer[0] = IIC_ReceiveByte();
	Slave_ACK();
	Slave_NOACK();
	IIC_Stop();
}

void DAC_PCF8591(uchar CtrlByte, uchar dat)
{
	IIC_Start();
	Delay4us();
	IIC_SendByte(0x90);
	if (IIC_ERROR == 1) return;
	IIC_SendByte(CtrlByte);
	if (IIC_ERROR == 1) return;
	IIC_SendByte(dat);
	if (IIC_ERROR == 1) return;
	IIC_Stop();
	Delay4us();
	Delay4us();
}

void main()
{
	LCD_Init();
	Uart1_Init();
	LCD_SetCustomChar(1, An);
	LCD_SetCustomChar(2, Gon);
	LCD_SetCustomChar(3, Da);
	LCD_Display_A_Line(0x00, LCD_Line_1);
	//LCD_Display_A_Line(0x40, LCD_Line_2);

	Write_Cmd(0xC0);
	Write_Data(0);
	Write_Cmd(0xC1);
	Write_Data(1);
	Write_Cmd(0xC2);
	Write_Data(2);
	while (1)

	{

		if (CH0 == 0)
		{
			ADC_PCF8591(0x40);
			Convert_To_Voltage(Recv_Buffer[0]);
			LCD_Line_1[4] = '0';
			LCD_Line_1[6] = Voltage[2];
			LCD_Line_1[8] = Voltage[1];
			LCD_Line_1[9] = Voltage[0];
			LCD_Display_A_Line(0x00, LCD_Line_1);
			if (StartFlag == 1)
			{
				Uart1_SendAD();
				Uart1_SendByte(Voltage[2]);
				Uart1_SendByte('.');
				Uart1_SendByte(Voltage[1]);
				Uart1_SendByte(Voltage[0]);
				Uart1_SendByte(';');
			}
			if (Voltage[2] >= 3 && Voltage[1] >= 5 && Voltage[0] >= 0)
			{
				LCD_Display_A_Line(0x00, LCD_Line_1);
				Delayms(5000);
				LCD_Display_A_Line(0x00, "                ");
			}
		}
		else if (CH1 == 0)
		{
			ADC_PCF8591(0x41);
			Convert_To_Voltage(Recv_Buffer[0]);
			LCD_Line_1[4] = '1';
			LCD_Line_1[6] = Voltage[2];
			LCD_Line_1[8] = Voltage[1];
			LCD_Line_1[9] = Voltage[0];
			LCD_Display_A_Line(0x00, LCD_Line_1);
			if (StartFlag == 1)
			{
				Uart1_SendAD();
				Uart1_SendByte(Voltage[2]);
				Uart1_SendByte('.');
				Uart1_SendByte(Voltage[1]);
				Uart1_SendByte(Voltage[0]);
				Uart1_SendByte(';');
			}
		}
		else	if (CH2 == 0)
		{
			ADC_PCF8591(0x42);
			Convert_To_Voltage(Recv_Buffer[0]);
			LCD_Line_1[4] = '2';
			LCD_Line_1[6] = Voltage[2];
			LCD_Line_1[8] = Voltage[1];
			LCD_Line_1[9] = Voltage[0];
			LCD_Display_A_Line(0x00, LCD_Line_1);
			if (StartFlag == 1)
			{
				Uart1_SendAD();
				Uart1_SendByte(Voltage[2]);
				Uart1_SendByte('.');
				Uart1_SendByte(Voltage[1]);
				Uart1_SendByte(Voltage[0]);
				Uart1_SendByte(';');
			}
		}
		else if (CH3 == 0)
		{
			ADC_PCF8591(0x43);
			Convert_To_Voltage(Recv_Buffer[0]);
			LCD_Line_1[4] = '3';
			LCD_Line_1[6] = Voltage[2];
			LCD_Line_1[8] = Voltage[1];
			LCD_Line_1[9] = Voltage[0];
			LCD_Display_A_Line(0x00, LCD_Line_1);
			if (StartFlag == 1)
			{
				Uart1_SendAD();
				Uart1_SendByte(Voltage[2]);
				Uart1_SendByte('.');
				Uart1_SendByte(Voltage[1]);
				Uart1_SendByte(Voltage[0]);
				Uart1_SendByte(';');
			}
		}
		else
		{
			LCD_Line_1[4] = 'X';
			LCD_Line_1[6] = '?';
			LCD_Line_1[8] = '?';
			LCD_Line_1[9] = '?';
			LCD_Display_A_Line(0x00, LCD_Line_1);
		}

		DAC_PCF8591(0x40, Recv_Buffer[0]);
	}

}

void Uart1_Isr(void) interrupt 4
{
	Rec = Uart1_RecByte();
	if (Rec == 0x35 || Rec == 5)
	{
		StartFlag = 0;
	}
	else if (Rec == 0x36 || Rec == 6)
	{
		StartFlag = 1;
	}
}
