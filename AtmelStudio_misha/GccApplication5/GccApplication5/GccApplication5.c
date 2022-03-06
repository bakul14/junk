/*
 * GccApplication5.c
 *
 * Created: 19.12.2020 14:38:03
 *  Author: user_01
 */ 


#include <avr/io.h>

int main(void)
{
	DDRB |= 1<<0;
// 	PORTB &= ~1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
// 	PORTB ^= 1<<0;
    PORTB |= 1<<0;
	PORTB &= ~1<<0;
    PORTB |= 1<<0;
    PORTB &= ~1<<0;
    PORTB |= 1<<0;
    PORTB &= ~1<<0;
    PORTB |= 1<<0;
    PORTB &= ~1<<0;
    PORTB |= 1<<0;
    PORTB &= ~1<<0;
    while(1)
    {
        //TODO:: Please write your application code 
    }
}