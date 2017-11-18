/*
 * uart.h
 *
 * Created: 2017. 11. 18. 20:27:08
 *  Author: Kaulics Dániel
 */ 
#include <avr/io.h>
#ifndef UART_H_
#define UART_H_


void USART_Init(void);
void USART_SendByte(uint8_t u8Data);
void USART_SendString(char*AT);


#endif /* UART_H_ */