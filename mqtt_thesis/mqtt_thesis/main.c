/*

 * mqtt_thesis.c
 *
 * Created: 2017. 11. 03. 19:49:27
 * Author : Kaulics Daniel
 */ 
#include "lcd.h"
#include "lightsensing.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
	uint16_t tmp = 0, i = 0;
	DDRC = 0xFF; // ledek debugra
	LCD_init();
	USART_Init();
	ADC_init();


	while (1)
	{
		tmp = ReadADC(0);
		LCD_goto(0,0);
		LCD_Put_int(ADC);
		_delay_ms(1000);
		LCD_command(0x01);
	}
}
	
