/*
* esp_12f.c
*
* Created: 2017. 12. 03. 16:44:08
*  Author: Kaulics Dániel
*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "uart.h"
#include "lcd.h"
#include "esp_12f.h"
#include "debug.h"

extern volatile unsigned char response_buffer[200];
extern volatile unsigned char respones_index;

void ESP_12_init()
{
	USART_puts0("ATE0\r\n");
	ESP_12_wait_for_ok(0);

	USART_puts0("AT+CWMODE=3\r\n");
	ESP_12_wait_for_ok(1);

	USART_puts0("AT+CWJAP=\"Csopog a csap!\",\"AKapucsengoKodja34KulcsNemTudjuk!!!!4444\"\r\n");
	ESP_12_wait_for_ok(2); //ready to configure TCP
}

void ESP_12_wait_for_ok(uint8_t led)
{
		while ((USART_Receive0()) != 'K')
		{
		}
		led_on(led);
}