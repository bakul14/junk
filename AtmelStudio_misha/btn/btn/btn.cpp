/*
* btn.cpp
*
* Created: 27.10.2020 18:21:06
*  Author: user_01
*/

#define F_CPU 2000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	uint16_t q = 0;
	DDRD |= 1<<0;
	DDRD &= ~(1<<7);
	PORTD |= 1<<7;
	bool flag = 0;
	while(1)
	{
		if (!(PIND & 1<<7) && flag == 0) {
			PORTD ^= 1<<0;
			flag = 1;
			q = 0;
		}
		else {
			if(PIND & 1<<7 && flag == 1 && q>2000) flag = 0;
			else if (PIND & 1<<7) q++;
			     else q = 0;
			
			
			
		}

		//			 flag = 1;
		//			 _delay_ms(50);
		// 		}
		// 		else if (flag == 1) {
		// 			PORTD &= ~(1<<0);
		// 		    flag = 0;
		// 		}
		//TODO:: Please write your application code
	}
}