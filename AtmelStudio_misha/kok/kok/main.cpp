/*
 * kok.cpp
 *
 * Created: 24.09.2020 10:28:14
 * Author : user_01
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD |= 1<<0;
	TCCR0 = 0b00000011;
	PORTD |= 1<<0;
	TCNT0 = 0;
	bool flag = 0;
    while (1) 
    {
		if (TCNT0 == 10 && flag == 0) {
			PORTD &= 0<<0;
			TCNT0 = 0;
			flag = !flag;
		}
        if (TCNT0 == 40 && flag == 1) {
			PORTD |= 1<<0;
			TCNT0 = 0;
			flag = !flag;
		}
    }
}

