/*
 * _60sec.cpp
 *
 * Created: 28.04.2021 18:16:03
 *  Author: user_01
 */ 


#include <avr/io.h> 
#include <avr/interrupt.h>

int main(void)
{
	SREG |= 1<<7;
	DDRD = 0xff;
    PORTD |= 1<<0;
	
	OCR1A = 15625;
	TIMSK1 |= 1<<1;
	TCCR1A = 0;
	TCCR1B = 0b00001100;
	TCCR1C = 0;
	
    while(1)
    {
        
    }
}

ISR (TIMER1_COMPA_vect) {
	PORTD ^= 1<<0;
}