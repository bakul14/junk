/*
* WINDING.cpp
*
* Created: 07.02.2021 17:05:13
*  Author: user_01
*/

/*

PC0 dir1
PC1 step1
PC2 en1
PC3 en2
PC4 step2
PC5 dir2

*/

#define step1 1
#define dir1 0
#define en1 2
#define step2 4
#define dir2 5
#define en2 3

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t tik1;
volatile uint32_t tik2;
volatile uint32_t last_tik1;
volatile uint32_t last_tik2;
volatile uint32_t systick = 0;
volatile uint32_t n = 0;
volatile uint32_t i = 5000;
volatile uint8_t lq = 0;
volatile uint8_t r = 0;

uint8_t mass [11] = {
	0b11010111,
	0b00010100,
	0b11001101,
	0b01011101,
	0b00011110,
	0b01011011,
	0b11011011,
	0b00010101,
	0b11011111,
	0b01011111,
	0b00001000
};

volatile uint8_t r0 = 0;
volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;
volatile uint8_t r6 = 0;
volatile uint8_t r7 = 0;

volatile uint16_t up = 0;
volatile uint16_t down = 0;

bool dp0 = 0;
bool dp1 = 0;
bool dp2 = 0;
bool dp3 = 0;
bool dp4 = 0;
bool dp5 = 0;
bool dp6 = 0;
bool dp7 = 0;

uint8_t data_out = 0;

volatile int N = 0;
volatile int N0 = 0;
volatile int d100;

volatile uint32_t kolvo_now = 0;

volatile uint16_t rpm =  300;



void work() {
	PORTC &= ~(1<<en1 | 1<<en2);
	PORTC |= 1<<dir2;
	down = rpm;
	while (1) {
		systick = 256*n + TCNT0;
		
		if ((systick - last_tik1) >= (tik1 + i)) {
			PORTC ^= 1<<step1;
			last_tik1 = systick;
			kolvo_now++;
		}
		
		if ((systick - last_tik2) >= (tik2 + i)) {
			PORTC ^= 1<<step2;
			last_tik2 = systick;
		}
		
		N = kolvo_now/1600;
		
		up = N;

		



	}
}


int main(void)
{

	float d = 0.25;
	
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0;
	
	PORTC |= 1<<en1 | 1<<en2;
	
	
	tik1 = 64285/rpm;
	tik2 = 2*tik1/d;
	
	SREG |= 1<<7;
	TCCR0 = 0b00000101;
	TCCR2 = 0b00000010;
	TIMSK = 0b01000001;
	
	SPCR = 0b01010000; //SPI_enable_MSB_clk/4
	

	work();
	
	while(1)
	{
		//TODO:: Please write your application code
	}
}

ISR (TIMER0_OVF_vect) {
	if (i == 0) i = 10;
	i--;

	r0 = up/1000;
	r1 = up%1000/100;
	r2 = up%1000%100/10;
	r3 = up%1000%100%10;
	r4 = down/1000;
	r5 = down%1000/100;
	r6 = down%1000%100/10;
	r7 = down%1000%100%10;
	
	
	switch (r) {
		case 0: SPDR = mass[r0] | dp0<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
		case 1: SPDR = mass[r1] | dp1<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
		case 2: SPDR = mass[r2] | dp2<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
		case 3: SPDR = mass[r3] | dp3<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
		case 4: SPDR = mass[r4] | dp4<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
		case 5: SPDR = mass[r5] | dp5<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
		case 6: SPDR = mass[r6] | dp6<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
		case 7: SPDR = mass[r7] | dp7<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
	}
	PORTB |= 1<<2;
	PORTB &= ~1<<2;
	
	SPDR = data_out;
	while(!(SPSR & (1<<SPIF)));
	PORTB |= 1<<1;
	PORTB &= ~1<<1;
	
	r++;
	if (r > 7) r = 0;
}



ISR (TIMER2_OVF_vect) {
	
	n++;
	
}