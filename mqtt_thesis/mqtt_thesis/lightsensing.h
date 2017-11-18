/*
 * adc.h
 *
 * Created: 2017. 11. 18. 20:25:03
 *  Author: Kaulics Dániel
 */ 

#include <avr/io.h>
#ifndef ADC_H_
#define ADC_H_

void ADC_init();
uint16_t ReadADC(uint8_t ch);

#endif /* ADC_H_ */