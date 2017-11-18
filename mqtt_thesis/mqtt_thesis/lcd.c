/*
 * lcd.c
 *
 * Created: 2017. 11. 15. 20:02:25
 *  Author: Kaulics Dániel
 */ 
 #include <stdio.h>
 #include "lcd.h"
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>

 void LCD_init()
 {
	 //portok beallitasa
	 DDRA |= 0xf0;
	 DDRF |= (1<<CMD_RS) | (1<<CMD_RW) | (1<<CMD_EN);
	 //iras
	 PORTF &= ~(CMD_RW);
	 //reset
	 PORTF &= ~(1<<CMD_RS);
	 PORTA = 0x20;
	 LCD_clock();
	 LCD_clock();
	 LCD_clock();

	 //4 bites uzemmod, 7x5pixel, 2soros
	 LCD_command(0x28);
	 LCD_command(0x28);
	 LCD_command(0x28);
	 //lcd alaphelyzetbe
	 LCD_command(0x02);
	 //lcd torlese
	 LCD_command(0x01);
	 //kurzor villog, alahuzas be, LCD be
	 //LCD_command(0x08 | (1<<LCD_EN) | (1<<LCD_CUR) | (1<<LCD_BL));
	 //kurzor villog ki, alahuzas be, LCD be
	 //LCD_command(0x08 | (1<<LCD_EN) | (1<<LCD_CUR) | (0<<LCD_BL));
	 //kurzor villog ki, alahuzas ki, LCD be
	 LCD_command(0x08 | (1<<LCD_EN) | (0<<LCD_CUR) | (0<<LCD_BL));
	 
	 
 }
 void LCD_clock()		//LCD engedélyezés várakoztatás
 {
	 _delay_ms(6);
	 
	 PORTF |= (1<<CMD_EN);
	 _delay_ms(5);
	 PORTF  &= ~(1<<CMD_EN);
	 _delay_ms(1);
 }
 void LCD_command(unsigned char val)		//PARANCSOK
 {
	 PORTF &= ~(1<<CMD_RS);
	 PORTA = val & 0xf0;
	 LCD_clock();
	 PORTA = val << 4;
	 LCD_clock();
 }
 void LCD_data(unsigned char val)
 {
	 PORTF |= (1<<CMD_RS);
	 PORTA = val & 0xf0;
	 LCD_clock();				//feldolgozás
	 PORTA = val << 4;			//kiírás
	 LCD_clock();
 }
//  void LCD_goto(unsigned char row, unsigned char col)		//sor,oszlop
//  {
// 	 if((col>=16) || (row>=4))return;
// 	 if(row>=2)
// 	 {
// 		 row = row - 2;
// 		 col = col + 16;
// 	 }
// 	 LCD_command((1<<7)|(row<<6)|col);
//  }
 void LCD_goto(unsigned char row, unsigned char col)
 {
	 LCD_command((1<<7)|(row<<6)|col);
 }

 void LCD_Put_int (int val)
 {
	char arr[17] = {0};
	snprintf(arr, 16, "%d",val);
	LCD_Puts(arr);
 }

 void LCD_Puts (char*s)
 {
	 while (*s)
	 {
		 LCD_data(*s);
		 s++;
	 }
 }