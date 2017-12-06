/*

* mqtt_thesis.c
*
* Created: 2017. 11. 03. 19:49:27
* Author : Kaulics Daniel
*/
#include <stdint.h>
#include "lcd.h"
#include "lightsensing.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Si7021_driver.h"
#include "esp_12f.h"
#include "paho_mqtt/MQTTPacket.h"

//115200
#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char response_buffer[200] = {0};
volatile unsigned char respones_index = 0;
volatile unsigned char response_flag = 0;

ISR (USART1_RX_vect)
{
	if (response_flag == 1)
	{
		if (UDR1 == '\r')
		{
			response_flag = 0;
			response_buffer[respones_index] = '\0';
			respones_index = 0;
		}
		else
		{
			response_buffer[respones_index] = UDR1;
			respones_index++;
		}
	}

	if (UDR1 == '\n')
	{
		response_flag = 1;
	}
}

int main()
{
	/*-----------------LOCAL VARS------------*/
	float temperature = 0, humidity = 0;
	char i = 0;
	uint8_t tmp;
	char *payload = "test";
	/*---------------------INITS------------------------*/
	DDRC = 0xFF; // ledek debugra
	LCD_init();
	USART_Init0(BAUD_PRESCALE);
	ADC_init();
	i2c_init();
	sei();
	
	_delay_ms(5000);
	ESP_12_init();


	MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

	char buf[200];
	int buflen = sizeof(buf);

	MQTTString topicString = MQTTString_initializer;

	int payloadlen = strlen(payload);
	int len = 0;

	data.clientID.cstring = "mymqttclient";
	data.keepAliveInterval = 20;
	data.cleansession = 1;
	//data.username.cstring = "testuser";
	//data.password.cstring = "testpassword";
	data.MQTTVersion = 4;

	len = MQTTSerialize_connect((unsigned char *)buf, buflen, &data);

	topicString.cstring = "TEST_TOPIC";
	len += MQTTSerialize_publish((unsigned char *)(buf + len), buflen - len, 0, 0, 0, 0, topicString, (unsigned char *)payload, payloadlen);

	len += MQTTSerialize_disconnect((unsigned char *)(buf + len), buflen - len);

	while (1)
	{
		
		_delay_ms(1000);
		//LCD_command(0x01);
		PORTC ^= (1<<1);
		tcp_send_packet(buf,len);
		/*
		PORTC = 0x0;
		tmp = ReadADC(0);
		LCD_goto(0,0);
		LCD_Puts("L:");
		LCD_Put_int(ADC);
		_delay_ms(1000);

		LCD_Put_int( UDR1);
		LCD_command(0x01);
		
		r_both_Si7021(&humidity, &temperature);
		PORTC |= (1 << i);
		i++;
		LCD_goto(1,0);
		LCD_Puts("H:");
		LCD_Put_int(humidity);
		LCD_Puts("% T:");
		LCD_Put_int(temperature);
		LCD_Puts("C");
		if (i == 8)
		{
		i = 0;
		}*/
	}
}

