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
#include "mqtt.h"
#include <stdio.h>

//115200
#define USART_BAUDRATE 57600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

int main()
{
	/*-----------------LOCAL VARS------------*/
	float temperature = 0, humidity = 0;
	char i = 0;
	uint16_t lighintensity;
	char arr[17] = {0};
	/*---------------------INITS------------------------*/
	DDRC = 0xFF;
	LCD_init();
	USART_Init0(BAUD_PRESCALE);
	ADC_init();
	i2c_init();
	sei();
	
	_delay_ms(5000);
	ESP_12_init();

	while (1)
	{
		r_both_Si7021(&humidity, &temperature);
		snprintf(arr, 16, "%d",(int)humidity);
		mqtt_publish_sensordata(arr, "humidity");
		memset(arr,0,sizeof(arr));
		_delay_ms(1000);

		snprintf(arr, 16, "%d",(int)temperature-3);
		mqtt_publish_sensordata(arr, "temperature");
		memset(arr,0,sizeof(arr));
		_delay_ms(1000);

		lighintensity = ReadADC(0);
		snprintf(arr, 16, "%d",lighintensity);
		mqtt_publish_sensordata(arr, "light");
		memset(arr,0,sizeof(arr));
		_delay_ms(1000);

		//LCD_command(0x01);
		PORTC ^= (1<<6);
		//tcp_send_packet(buf,len);
		
		//PORTC = 0x0;
		//lighintensity = ReadADC(0);
		//LCD_goto(0,0);
		//LCD_Puts("L:");
		//LCD_Put_int(ADC);
		//_delay_ms(1000);
//
		//LCD_Put_int( UDR1);
		//LCD_command(0x01);
		//
		//r_both_Si7021(&humidity, &temperature);
		//PORTC |= (1 << i);
		//i++;
		//LCD_goto(1,0);
		//LCD_Puts("H:");
		//LCD_Put_int(humidity);
		//LCD_Puts("% T:");
		//LCD_Put_int(temperature);
		//LCD_Puts("C");
		//if (i == 8)
		//{
		//i = 0;
		//}
	}
}

