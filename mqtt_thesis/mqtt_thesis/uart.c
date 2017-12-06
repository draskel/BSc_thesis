/*
 * uart.c
 *
 * Created: 2017. 12. 03. 0:09:26
 *  Author: Kaulics Daniel
 */ 

#include <avr/io.h>

void USART_Init0( unsigned int ubrr )
{
	//UCSR1A=(1<<U2X1);			//sebesség duplázása
	/* Set baud rate */
	UBRR1H = (unsigned char)(ubrr>>8);
	UBRR1L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = (0<<USBS1)|(1<<UCSZ10)|(1<<UCSZ11);
	//UCSR1B |= (1 << RXCIE1);

}

void USART_Transmit0( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

unsigned char USART_Receive0( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* Get and return received data from buffer */
	return UDR1;
}

void USART_mqtt_puts0(const char* data, uint8_t size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		USART_Transmit0(data[i]);
	}
}

void USART_puts0(const char* str)
{
	while(*str)
	{
		USART_Transmit0(*str++);
	}
}
