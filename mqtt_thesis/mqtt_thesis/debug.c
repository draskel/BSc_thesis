/*
* debug.c
*
* Created: 2017. 12. 06. 21:34:32
*  Author: Kaulics Dániel
*/

#include "debug.h"
#include <avr/io.h>

void led_on(uint8_t led)
{
	PORTC |= 1<<led;
}
void led_off(uint8_t led)
{
	PORTC &= ~(1<<led);
}