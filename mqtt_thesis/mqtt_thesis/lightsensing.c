/*
 * lightsensing.c
 *
 * Created: 2017. 11. 18. 17:44:23
 *  Author: Kaulics Dániel
 */ 
 
 #include "lightsensing.h"
 #include <util/delay.h>
 #include <avr/interrupt.h>

  void ADC_init()
 {
	ADCSRA |= (1<<ADEN);
	ADMUX |= (1<<REFS0); //(1<<REFS1) | 
	ADCSRA |= (1<<ADPS0) | ((1<<ADPS1)) | (1<<ADPS2);
}

 uint16_t ReadADC(uint8_t ch)
 {
	//Select ADC Channel ch must be 0-7
	ADMUX |= ch;
	//Start Single conversion
	ADCSRA|=(1<<ADSC);
	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));
	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF); 
	return (ADC);
 }

