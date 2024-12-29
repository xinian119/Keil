#ifndef __LCD1602_H__
#define __LCD1602_H__

sbit D0 = P0 ^ 0;
sbit D1 = P0 ^ 1;
sbit D2 = P0 ^ 2;
sbit D3 = P0 ^ 3;
sbit D4 = P0 ^ 4;
sbit D5 = P0 ^ 5;
sbit D6 = P0 ^ 6;
sbit D7 = P0 ^ 7;
sbit RS = P2 ^ 0;
sbit RW = P2 ^ 1;
sbit E = P2 ^ 2;

void Check_Busy(void);
void Write_Cmd(unsigned char cmd);
void Write_Data(unsigned char Data);
void LCD_Init(void);
void LCD_ShowString(unsigned char AddRess, unsigned char* str);
void LCD_ShowNum(unsigned char AddRess, unsigned int Num, unsigned char Length);
unsigned int Fast_Exponentiation(unsigned char x);
void LCD_SetCustomChar(unsigned char Position, char* Table);
void LCD_Set_Position(unsigned char pos);
void LCD_Display_A_Line(unsigned char Line_Addr, unsigned char s[]);

#endif // !LCD1602__H_
