/*
* time.cpp
*
* Created: 19.07.2021 21:03:58
*  Author: user_01
*/
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



int main(void)
{
	DDRB |= 1<<3;  //часы
	DDRB &= ~1<<1; //кнопка
	DDRD |= 1<<0 | 1<<1 | 1<<4 | 1<<7; //фонари
	DDRC |= 1<<6; //фонари
	DDRE |= 1<<6; //фонари
	DDRD &= ~1<<3; //датчик
	SREG |= 1<<7;
	EICRA = 0b11000000;
	EIMSK |= 1<<3;
	
	PORTC &= ~1<<6;
	PORTD &= ~1<<7;
	PORTD &= ~1<<1;
	PORTE &= ~1<<6;
	PORTD &= ~1<<0;
	PORTB &= ~1<<3;
	
	PORTD &= ~1<<3;
	
	
	while(1)
	{
		if (PINB & 1<<1) PORTB |= 1<<3;
	}
}

	ISR (INT3_vect) {
		
		_delay_ms(200);
		
		PORTC |= 1<<6;
		PORTD |= 1<<7;
		PORTD |= 1<<1;
		PORTE |= 1<<6;
		PORTD |= 1<<0;


		_delay_ms(1000);
		PORTC &= ~1<<6;
		PORTD |= 1<<7;
		PORTD |= 1<<1;
		PORTE |= 1<<6;
		PORTD |= 1<<0;
				
		_delay_ms(1000);
		PORTD &= ~1<<7;
		PORTD |= 1<<1;
		PORTE |= 1<<6;
		PORTD |= 1<<0;

		
		_delay_ms(1000);
		PORTD &= ~1<<1;
		PORTE |= 1<<6;
		PORTD |= 1<<0;

		
		_delay_ms(1000);
		PORTE &= ~1<<6;
		PORTD |= 1<<0;

		
		_delay_ms(1000);
		PORTD &= ~1<<0;
		PORTB &= ~1<<3;
		PORTD |= 1<<4;
		
		_delay_ms(2000);
		PORTD &= ~1<<4;
		
		EIFR |= 1<<3;

	}