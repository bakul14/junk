/*
 * led_on.c
 *
 * Created: 07.05.2020 16:21:30
 * Author : user_01
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD = 0b00000001;
	PORTD = 0b00000001;
    while (1) 
    {
    }
}

