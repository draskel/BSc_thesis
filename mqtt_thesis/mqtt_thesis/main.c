/*

 * mqtt_thesis.c
 *
 * Created: 2017. 11. 03. 19:49:27
 * Author : Kaulics Daniel
 */ 
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL  // 1 MHz
#define egy 0b00000001;
#define ketto 0b00000010;
#define harom 0b00000100;
#define negy 0b00001000;
#define ot 0b00010000;
#define hat 0b00100000;
#define het 0b01000000;
#define nyolc 0b10000000;
#define nulla 0;

/*
0b00000001;
0b00000010;
0b00000100;
0b00001000;
0b00010000;
0b00100000;
0b01000000;
0b10000000;
*/
int main()
{
	char AT_command;
	unsigned int tmp = 0, i = 0;
	DDRC = 0xFF; // ledek debugra
	LCD_init();
	USART_Init();

	while (1)
	{
	_delay_ms(5000);
	LCD_goto(0b00000000,0);
	LCD_Puts("* * * * * * * * ");
	LCD_goto(0b00000011,0);
	LCD_Puts(" * * * * * * * *");
	_delay_ms(5000);
	LCD_command(0);
	LCD_goto(0b00000000,0);
	LCD_Puts(" * * * * * * * *");
	LCD_goto(0b00000011,0);
	LCD_Puts("* * * * * * * * ");
	}
}
	
