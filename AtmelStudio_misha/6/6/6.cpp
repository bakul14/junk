/*
 * _6.cpp
 *
 * Created: 11.10.2020 20:51:22
 *  Author: user_01
 */ 


#include <avr/io.h>

int main(void)
{
    while(1)
    {
        DDRD = 0b00000111;
		PORTD |= 1<<4;
		
    }
}