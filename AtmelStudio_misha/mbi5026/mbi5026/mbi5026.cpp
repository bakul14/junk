/*
* mbi5026.cpp
*
* Created: 16.01.2021 19:54:08
*  Author: user_01
*/
#define S 0b01011011
#define O 0b11010111
#define I 0b00010100
#define P 0b10001111
#define U 0b11010110
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t i = 0;

volatile uint8_t r0 = 0;
volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;
volatile uint8_t r6 = 0;
volatile uint8_t r7 = 0;

int up = 3469;
int down = 2567;

uint8_t mass [10] = {0b11010111, 0b00010100, 0b11001101, 0b01011101, 0b00011110, 0b01011011, 0b11011011, 0b00010101, 0b11011111, 0b01011111};
int main(void)
{
	DDRB = 0xff;
	SPCR = 0b01010000;
	
	SREG |= 1<<7;
	TCCR0 = 0b00000010;
	TIMSK = 0b00000001;
	

	while(1)
	{
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
	}
}

ISR (TIMER0_OVF_vect) {
	switch (i) {
		case 0: SPDR = mass[r0]; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
		case 1: SPDR = mass[r1]; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
		case 2: SPDR = mass[r2]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
		case 3: SPDR = mass[r3]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
		case 4: SPDR = mass[r4]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
		case 5: SPDR = mass[r5]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
		case 6: SPDR = mass[r6]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
		case 7: SPDR = mass[r7]; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
	}
	PORTB |= 1<<2;
	PORTB &= ~1<<2;
	i++;
	if (i > 7) i = 0;
}