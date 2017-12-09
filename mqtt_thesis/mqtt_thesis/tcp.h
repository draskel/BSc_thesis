/*
 * tcp.h
 *
 * Created: 2017. 12. 06. 22:02:49
 *  Author: Kaulics Dániel
 */ 


#ifndef TCP_H_
#define TCP_H_
#include <stdint.h>

void tcp_send_packet(char* payload, uint8_t length, uint8_t dc_flag, uint8_t start_flag);


#endif /* TCP_H_ */