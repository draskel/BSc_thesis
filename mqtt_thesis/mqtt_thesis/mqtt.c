/*
* mqtt.c
*
* Created: 2017. 12. 09. 19:06:39
*  Author: Kaulics Dániel
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

void mqtt_publish_sensordata(char* payload, char* topic)
{
		MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

		char buf[200];
		int buflen = sizeof(buf);

		MQTTString topicString = MQTTString_initializer;

		int payloadlen = strlen(payload);
		int len = 0;

		data.clientID.cstring = "ERO4XE_client";
		data.keepAliveInterval = 20;
		data.cleansession = 1;
		data.MQTTVersion = 4;

		len = MQTTSerialize_connect((unsigned char *)buf, buflen, &data);

		_delay_ms(1000);
		tcp_send_packet(buf,len,0,1);
		memset(buf,0,sizeof(buf));
		len = 0;
		_delay_ms(500);

		topicString.cstring = topic;
		len += MQTTSerialize_publish((unsigned char *)(buf + len), buflen - len, 0, 0, 0, 0, topicString, (unsigned char *)payload, payloadlen);
		tcp_send_packet(buf,len,0,0);
		memset(buf,0,sizeof(buf));
		len = 0;
		_delay_ms(500);

		len += MQTTSerialize_disconnect((unsigned char *)(buf + len), buflen - len);
		tcp_send_packet(buf,len,0,0);
		memset(buf,0,sizeof(buf));
		len = 0;
		_delay_ms(500);
}