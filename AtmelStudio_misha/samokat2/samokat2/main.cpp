/*
 * Samokat.cpp
 *
 * Created: 20.09.2020 19:24:21
 * Author : mikhail_bakulevskiy
 * Frequency 1MHz 
 * PC0 voltage1
 * PC1 voltage2
 * PC2 voltage3
 * PC3 voltage4
 * PC4 current
 * PC5 signal throttle INPUT
 * PB0 button mode
 * PB1-PB5 transistors of segments
 * PB6 signal throttle OUTPUT
 * PB7 hall sensor
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
	TCNT0 = 1;
	uint8_t t1 = 0;
	uint8_t t = 0;
	uint8_t r1 = 0;
	uint8_t r2 = 0;
	uint8_t v = 0;
	uint8_t q = 0;
	uint8_t i = 1;
	bool flag = 0;
	uint8_t mass [10] = {
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
		0b11111111,
	};
    while (1) 
    {
		
		
		v = s/(t*1024/F_CPU*6)*3.6;
        r1 = v/10;
		r2 = v%10;
		
		if (TCNT0 - q >=1) {
			PORTB |= 1<<i;
			q++;
			i++;			
		}
		switch (i) {
			case 1: PORTD = mass [r1];
			case 2: PORTD = mass [r2];
//			case 3: PORTD = mass [r3];
//			case 4: PORTD = mass [r4];
//			case 5: PORTD = mass [r5];
		}
		if (i == 5) i = 1;
		if (q == 255) q = 0;
		if (TCNT0 == 255) TCNT0 = 1;
    }
}


