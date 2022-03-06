/*
 * new.c
 *
 * Created: 01.07.2020 12:09:40
 * Author : user_01
 */ 

#include <avr/io.h>
#define ms 50
int main(void)
{
    DDRD = 0xFF;
	TCCR1B = 0b00000100;
	TCNT1 = 0;
	PORTD = 0xFF;
    while (1) 
    {
		if (TCNT1 > 31250/1000*ms) {
			PORTD = 0;			
		}
		if (TCNT1 > 62500/1000*ms) {
			PORTD = 0xFF;
			TCNT1 = 0;
		}
    }
}

