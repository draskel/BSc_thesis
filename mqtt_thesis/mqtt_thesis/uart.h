/*
* uart.h
*
* Created: 2017. 12. 03. 0:09:44
*  Author: Kaulics Daniel
*/


#ifndef UART_H_
#define UART_H_


void USART_Init0( unsigned int ubrr );
void USART_Transmit0( unsigned char data );
unsigned char USART_Receive0( void );
void USART_puts0(const char* str);
void USART_mqtt_puts0(const char* data, uint8_t size);

#endif /* UART_H_ */