/*
 * _2phase_pwm.cpp
 *
 * Created: 23.02.2021 11:58:08
 *  Author: user_01
 */ 


#include <avr/io.h>

int main(void)
{
	
	DDRD = 0xff;
	DDRB = 0xff;
	TCNT2 = 255; //сдвиг_180
	TCCR0A = TCCR2A = 0b10000001;
	TCCR0B = TCCR2B = 0b00000001;
	OCR0A = OCR2A = 100;
}