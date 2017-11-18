/*
 * uart.c
 *
 * 
 * Created: 2017. 11. 15. 20:06:23
 *  Author: Kaulics Dániel
 */
#include "lcd.h" //for debug
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define USART_BAUDRATE 9600   
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
volatile unsigned char value;

uint8_t USART_ReceiveByte();


void USART_Init(void)
{
	UBRR1L = BAUD_PRESCALE;
	UBRR1H = (BAUD_PRESCALE >> 8); 
	UCSR1B = ((1<<TXEN1)|(1<<RXEN1) | (1<<RXCIE1));
}


void USART_SendByte(uint8_t u8Data)
{
	while((UCSR1A &(1<<UDRE1)) == 0);
	UDR1 = u8Data;
}

uint8_t USART_ReceiveByte()
{
	while((UCSR1A &(1<<RXC1)) == 0);
	return UDR1;
}

ISR(USART1_RX_vect)
{
	value = UDR1;
}
