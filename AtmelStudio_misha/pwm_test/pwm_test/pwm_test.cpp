/*
 * pwm_test.cpp
 *
 * Created: 01.11.2020 15:28:47
 *  Author: user_01
 */ 


#include <avr/io.h>

int main(void)
{
	
	TCCR1A = 0b10000010;
	TCCR1B = 0b00010001;
	ICR1 = 20000;
	OCR1A = 2000;
	DDRB |= 1<<1;
    while(1)
    {
         
    }
}