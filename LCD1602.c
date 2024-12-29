#include <reg51.h>
#include <stdio.h>
#include <INTRINS.H>
#include "Delay.h"
#include "LCD1602.h"


void Check_Busy(void)
{
	unsigned char dt;

	do
	{
		dt = 0xff;

		E = 0;
		RS = 0;
		RW = 1;

		E = 1;

		dt = P0;
	} while (dt & 0x80);

	E = 0;
}

void Write_Cmd(unsigned char cmd)//LCD写命令
{
	Check_Busy();
	E = 0;
	RS = 0;
	RW = 0;
	P0 = cmd;
	E = 1;
	_nop_();
	E = 0;
	Delayms(1);
}

void Write_Data(unsigned char Data)//LCD写数据
{
	Check_Busy();
	E = 0;
	RS = 1;
	RW = 0;
	P0 = Data;
	E = 1;
	_nop_();
	E = 0;
	Delayms(1);
}

void LCD_Init(void)//LCD初始化
{
	Write_Cmd(0x38);
	Write_Cmd(0x0C);
	Write_Cmd(0x06);
	Write_Cmd(0x01);
	Delayms(1);
}


void LCD_ShowString(unsigned char AddRess, unsigned char* String)
{
	unsigned char i;

	Write_Cmd(AddRess);

	for (i = 0; String[i] != '\0'; i++)
	{
		Write_Data(String[i]);
	}
}

unsigned int Fast_Exponentiation(unsigned char x)
{
	unsigned char i, result = 1;

	for (i = 0; i < x; i++)
	{
		result *= 10;
	}
	return result;
}

void LCD_ShowNum(unsigned char AddRess, unsigned int Num, unsigned char Length)
{
	unsigned char i;

	Write_Cmd(AddRess);

	for (i = 0; i < Length; i++)
	{
		Write_Data(Num / Fast_Exponentiation(Length - 1 - i) % 10 + '0');
	}
}

void LCD_SetCustomChar(unsigned char Position, char* Table)
{
	unsigned char i;

	switch (Position)
	{
	case 1:
		Write_Cmd(0x40);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 2:
		Write_Cmd(0x48);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 3:
		Write_Cmd(0x50);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 4:
		Write_Cmd(0x58);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 5:
		Write_Cmd(0x60);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 6:
		Write_Cmd(0x68);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 7:
		Write_Cmd(0x70);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	case 8:
		Write_Cmd(0x78);
		for (i = 0; i < 8; i++)
		{
			Write_Data(Table[i]);
		}
		break;
	}
}

void LCD_Set_Position(unsigned char pos)
{
	Write_Cmd(pos | 0x80);
}

void LCD_Display_A_Line(unsigned char Line_Addr,unsigned char s[])
{
 	unsigned char i;
	LCD_Set_Position(Line_Addr);
	for(i=0;i<16;i++)	Write_Data(s[i]);
}