/*
 * tiktak.cpp
 *
 * Created: 24.09.2020 10:28:14
 * Author : user_01
 */ 

#include <avr/io.h>


int main(void)
{
    DDRD |= 1<<0;
	TCCR1B = 0b00000011;
	PORTD |= 1<<0;
	TCNT1 = 0;
	bool flag = 0;
    while (1) 
    {
		if (TCNT1 == 15625 && flag == 0) {
			PORTD &= 0<<0;
			TCNT1 = 0;
			flag = !flag;
		}
        if (TCNT1 == 15625 && flag == 1) {
			PORTD |= 1<<0;
			TCNT1 = 0;
			flag = !flag;
		}
    }
}

