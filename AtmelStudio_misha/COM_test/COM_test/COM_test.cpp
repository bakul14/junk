/*
* COM_test.cpp
*
* Created: 13.01.2021 21:56:14
*  Author: user_01
*/


#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t qty_now = 0;
volatile uint32_t qty = 100;

uint8_t= 0 i ;

volatile uint8_t r0 = 0;
volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;
volatile uint8_t r6 = 0;
volatile uint8_t r7 = 0;

volatile int up = 0;
volatile int down = 0;

volatile uint8_t mass [10] = {
	0b11010111,
	0b00010100,
	0b11001101,
	0b01011101,
	0b00011110,
	0b01011011,
	0b11011011,
	0b00010101,
	0b11011111,
	0b01011111
};

volatile int kv = 0;

int main(void)
{
	uint8_t n = 0; //передача
	int rpm = 600; //об_мин
	float d = 2; //диаметр_провода

	DDRB |= 1<<2 | 1<<3 | 1<<5;
	DDRD |= 1<<6 | 1<<7;
	SREG |= 1<<7;
	SPCR = 0b01010000;
	
	
	if (rpm < 38) {
		TCCR2 = 0b00001101; //clk/128
		n = 1;
	}
	if (rpm >= 38) {
		TCCR2 = 0b00001100; //clk/64
		n = 2;
	}
	if (rpm >= 75) {
		TCCR2 = 0b00001011; //clk/32
		n = 4;
	}
	if (rpm >= 300) {
		TCCR2 = 0b00001010; //clk/8
		n = 16;
	}
	
	
	TCCR1A = 0;
	TCCR1B = 0b00001010; //clk/8
	
	TCCR0 = 0b00000010;
	
	OCR1A = 149820/d/rpm; //2497/d/(rpm/60)
	OCR2 = (4687.5/rpm)*n-1; //78/rpm/60-1 4680
	
	TIMSK = 0b10010001;

	while(1) {
		up = down = kv/1600;
		
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


ISR (TIMER1_COMPA_vect) {
	PORTD ^= 1<<6;
	qty_now++;
	if (qty_now >= qty*1600) TIMSK &= ~(1<<7 | 1<<4); //qty*1600
}


ISR (TIMER2_COMP_vect) {
	PORTD ^= 1<<7;
	kv++;
}





