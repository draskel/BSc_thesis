/*
 * uart.c
 *
 * Created: 2017. 11. 15. 20:06:23
 *  Author: Kaulics Dániel
 */
 #include "lcd.h"
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #define USART_BAUDRATE 9600   
 #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
 volatile unsigned char*value;
 void USART_Init(void);
 void USART_SendByte(uint8_t u8Data);
 void USART_SendString(char*AT);
 uint8_t USART_ReceiveByte();


  void USART_Init(void)
  {
	 // Set baud rate
	 UBRR1L = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
	 UBRR1H = (BAUD_PRESCALE >> 8); 
	 /* Load upper 8-bits into the high byte of the UBRR register
     Default frame format is 8 data bits, no parity, 1 stop bit
	 to change use UCSRC, see AVR datasheet*/ 
	 
	 // Enable receiver and transmitter and receive complete interrupt 
	 UCSR1B = ((1<<TXEN1)|(1<<RXEN1) | (1<<RXCIE1));
 }
 
 void USART_SendString(char*AT)
 {
	while (UCSR1A & (1 << UDRE1) == 0) {};
	UDR1 = *AT;
 }

 void USART_SendByte(uint8_t u8Data)
 {
	 // Wait until last byte has been transmitted
	 while((UCSR1A &(1<<UDRE1)) == 0);
	 // Transmit data
	 UDR1 = u8Data;
 }

uint8_t USART_ReceiveByte()
{
	while((UCSR1A &(1<<RXC1)) == 0);
	return UDR1;
}

 ISR(USART1_RX_vect)
 {
	 value = UDR1;             //read UART register into value 
	LCD_Puts("lofasz");				
 }