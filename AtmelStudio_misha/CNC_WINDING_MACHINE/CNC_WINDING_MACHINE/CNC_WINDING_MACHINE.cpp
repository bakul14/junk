/*
* CNC_WINDING_MACHINE.cpp
*
* Created: 18.01.2021 15:57:48
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

/*

PD0   PARAMETR+
PD1   PARAMETR-
PD2   END1
PD2   END2
PD4   ENTER
PD5   BACK
PD6   PLAY/PAUSE
PD7   MOVE

*/



#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int pulse_rpm = 0;

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

volatile uint8_t i = 0;

volatile uint8_t r0 = 0;
volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;
volatile uint8_t r6 = 0;
volatile uint8_t r7 = 0;

bool dp0 = 0;
bool dp1 = 0;
bool dp2 = 0;
bool dp3 = 0;
bool dp4 = 0;
bool dp5 = 0;
bool dp6 = 0;
bool dp7 = 0;

bool timsk228 = 0;

#define step1 1
#define dir1 0
#define en1 2
#define step2 4
#define dir2 5
#define en2 3

int up = 0;
int down = 0;

uint8_t n = 0; //_передача
uint8_t status = 0; | 

uint8_t stk1 = 1; // шаг_задания_оборотов
uint8_t stk2 = 0; // шаг_задания_оборотов

uint8_t data_out = 0;

volatile int N = 0;
volatile int N0 = 0;
volatile int d100;
volatile float d = 0; //диаметр_провода_мм
int rpm = 200; //об_мин
uint8_t dir = 5;

uint8_t layer = 1;
volatile int NN = 0;
void work () {

	TIMSK = 0b10000000; //INTERRUPT: TIMER0_overflow, TIMER1_CTC, TIMER2_CTC
	TCCR1A = 0;
	TCCR1B = 0b00001010; //TIMER1_clk/8_CTC_mode_(interrupt)
	PORTC &= ~(1<<en1);
	PORTC &= ~(1<<en2);
	dp1 = 0;
	dir = dir-4;
	OCR1A = 149820*d/rpm; //2497/d/(rpm/60)
	OCR2 = (4687.5/rpm)*n-1; //78/rpm/60-1 4680
	while (1) {
		
		if (rpm < 38) {TCCR2 = 0b00001101; n = 1;} //TIMER2_clk/128_CTC_mode_(interrupt)
		if (rpm >= 38) {TCCR2 = 0b00001100; n = 2;} //TIMER2_clk/64_CTC_mode_(interrupt)
		if (rpm >= 75) {TCCR2 = 0b00001011; n = 4;} //TIMER2_clk/32_CTC_mode_(interrupt)
		if (rpm >= 300) {TCCR2 = 0b00001010; n = 16;} //TIMER2_clk/8_CTC_mode_(interrupt)
		

		
		up = pulse_rpm/1600;
		down = rpm;
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		
		if(up >= N0*layer) { //смена_направления
			dir = !dir;
			layer++;
		}
		
		switch (PIND) {
			case 0b00000001: rpm = rpm + 10; if (rpm >= 450) rpm = 450; _delay_ms(200); break;
			case 0b00000010: rpm = rpm - 10; if (rpm <= 30) rpm = 30; _delay_ms(200); break;
		}
		
		switch (i) {
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
		
		i++;
		if (i > 7) i = 0;
		
		
	}
}

void ready() {
	data_out = 0b11000000 | 1<<dir;
	while (1) {
		switch (PIND) {
			case 0b01000000: work(); data_out = 0b01000000 | 1<<dir;
		}
	}
}

void point56_DIR () {
	while (1) {
		switch (PIND) {
			case 0b00000001: data_out = 0b10100000; dir = 5; break;
			case 0b00000010: data_out = 0b10010000; dir = 4; break;
			case 0b00010000: _delay_ms(200); ready();
		}

	}
}

void point4_RPM () {
	data_out = 0b10001000;
	while (1) {
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		switch (PIND) {
			case 0b00000001: rpm = rpm + 10; _delay_ms(200); break;
			case 0b00000010: rpm = rpm - 10; _delay_ms(200); break;
			case 0b00010000: _delay_ms(200); data_out = 0b10100000; point56_DIR(); break;
		}
		if (rpm > 450) rpm = 450;
		if (rpm < 30) rpm = 30;
		down = rpm;
	}
}

void point3_D () {
	data_out = 0b10000100;
	dp1 = 1;
	down = 0;
	
	while (1) {
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		
		if (PIND & 1<<4) {
			_delay_ms(200);
			stk1++;
		}
		switch (stk1) {
			case 1: stk2 = 10; break;
			case 2: stk2 = 1; break;
			case 3: _delay_ms(200); stk1 = 1; stk2 = 0; point4_RPM(); break;
		}
		
		switch (PIND) {
			case 0b00000001: d100 = d100 + stk2; _delay_ms(200); break;
			case 0b00000010: d100 = d100 - stk2; _delay_ms(200); break;
		}
		
		if (d100 > 300) d100 = 300;
		if (d100 < 0) d100 = 0;
		up = d100;
		d = 100/d100;
	}
}


void point2_N0 () {
	data_out = 0b10000010;
	
	while (1) {
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		
		if (PIND & 1<<4) {
			_delay_ms(200);
			stk1++;
		}

		switch (stk1) {
			case 1: stk2 = 100; break;
			case 2: stk2 = 10; break;
			case 3: stk2 = 1; break;
			case 4: _delay_ms(200); stk1 = 1; stk2 = 0; point3_D();
		}

		
		switch (PIND) {
			case 0b00000001: N0 = N0 + stk2; _delay_ms(200); break;
			case 0b00000010: N0 = N0 - stk2; _delay_ms(200); break;
		}
		if (N0 < 0) N0 = 0;
		if (N0 > 9999) N0 = 9999;
		down = N0;
	}
	
}

void point1_N ()  {
	data_out = 0b10000001;
	while (1) {
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		if (PIND & 1<<4) {
			_delay_ms(200);
			stk1++;
		}

		switch (stk1) {
			case 1: stk2 = 100; break;
			case 2: stk2 = 10; break;
			case 3: stk2 = 1; break;
			case 4: _delay_ms(200); stk1 = 1; stk2 = 0; point2_N0(); break;
		}

		
		switch (PIND) {
			case 0b00000001: N = N + stk2; _delay_ms(200); break;
			case 0b00000010: N = N - stk2; _delay_ms(200); break;
		}
		if (N < 0) N = 0;
		if (N > 9999) N = 9999;
		up = N;
		NN = N*1600;
	}
}
void wait () {
	r0 = r1 = r2 = r3 = r4 = r5 = r6 = r7 = 10;
	while (1) {
		if (PIND & 1<<4) {_delay_ms(200);
		point1_N();}
		

	}
	
}



int main(void)
{
	
	DDRB = 0xff;; //SPI_out
	DDRC = 0xff; //(step_dir_enable)x2
	DDRD = 0; //buttons
	
	PORTC |= 1<<en1 | 1<<en2;
	
	SREG |= 1<<7; //разрешить_глобальные_прерывания
	SPCR = 0b01010000; //SPI_enable_MSB_clk/4
	
	TCCR0 = 0b00000010; //TIMER0_clk/64
	

	
	TIMSK = 0b00000001;
	
	wait();
	
}

ISR (TIMER0_OVF_vect) {
	switch (i) {
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
	
	i++;
	if (i > 7) i = 0;
}

ISR (TIMER1_COMPA_vect) {
	PORTC ^= 1<<step2;

}

ISR (TIMER2_COMP_vect) {
	PORTC ^= 1<<step1;
	pulse_rpm++;
	if (pulse_rpm >= NN) {
		TIMSK &= ~(1<<7 | 1<<4);
		PORTC |= 1<<en1 | 1<<en2;
	}
}


