/*
* tcp.c
*
* Created: 2017. 12. 06. 22:02:34
*  Author: Kaulics Dániel
*/
#include "tcp.h"
#include <stdio.h>
#include "esp_12f.h"
#include <util/delay.h>

void tcp_send_packet(char* payload, uint8_t length, uint8_t dc_flag, uint8_t start_flag)
{
	unsigned char cmd[50] = {0};
	if (start_flag == 1)
	{
		USART_puts0("AT+CIPSTART=\"TCP\",\"192.168.1.99\",1883\r\n");
		_delay_ms(300);
	}

	snprintf(cmd,50,"AT+CIPSEND=%d\r\n",length);
	USART_puts0(cmd);
	//while ((USART_Receive0()) != '>'){};
	_delay_ms(5);
	USART_mqtt_puts0(payload,length);
	//ESP_12_wait_for_ok(6);
	_delay_ms(50);
	if(dc_flag == 1)
	{
		USART_puts0("AT+CIPCLOSE\r\n");
		ESP_12_wait_for_ok(5);		
	}

}