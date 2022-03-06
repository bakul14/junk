/*
* logic.cpp
*
* Created: 04.12.2020 18:43:42
*  Author: user_01
*/


#include <avr/io.h>

int main(void)
{
	DDRD |= 1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
	
	PORTD |= 1<<0;
	PORTD &= ~1<<0;
}