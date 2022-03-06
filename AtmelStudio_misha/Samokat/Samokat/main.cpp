/*
 * Samokat.cpp
 *
 * Created: 20.09.2020 19:24:21
 * Author : mikhail_bakulevskiy
 * Frequency 1MHz 
 * PC0 signal throttle OUTPUT
 * PC1 hall sensor
 * PC2 voltage
 * PC3 current
 * PC4 button mode
 * PC5 signal throttle INPUT
 * PB1-PB5 transistors of segments
 */ 

#include <avr/io.h>

#define n 6 
#define s 0.254
#define F_CPU 1000000
int main(void)
{
    DDRD = 0xff; 
	DDRB |= (0<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5);
	PORTC = 0b00000011;
	TCCR0 = 0b00000101; //1024
	TCNT0 = 0;
	uint8_t t = 0;
	int v = 0;
/*	uint8_t [10] = {
		0b;
		0b;
		0b;
		0b;
		0b;
		0b;
		0b;
		0b;
		0b;
		0b;
	} */
    while (1) 
    {
		if (PINC &= (0<<1)) {
			t = TCNT0;
			TCNT0 = 0;
		}
		v = s/(t*1024/F_CPU*6)*3.6;
    }
}

