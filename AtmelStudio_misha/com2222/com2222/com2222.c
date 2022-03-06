/*
 * com2222.c
 *
 * Created: 16.01.2021 13:43:42
 *  Author: user_01
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t n = 0; //передача
int rpm = 30; //об_мин
float d = 0.08; //диаметр_провода

int main(void)
{

	DDRB |= 1<<1 | 1<<2 | 1<<3;
	SREG |= 1<<7;
	
	maths();
	
	TCCR1A = 0;
	TCCR1B = 0b00001010; //clk/8
	
	OCR1A = 149820/d/rpm; //2497/d/(rpm/60)
	OCR2 = (4687.5/rpm)*n-1; //78/rpm/60-1 4680
	
	TIMSK = 0b10010000;

	while(1) {
		//TODO:: Please write your application code
	}
}
ISR (TIMER1_COMPA_vect) {
	PORTB ^= 1<<1;
}
ISR (TIMER2_COMP_vect) {
	PORTB ^= 1<<2;
}

void maths() {
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

}