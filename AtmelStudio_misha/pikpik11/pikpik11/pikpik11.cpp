/*
* pikpik11.cpp
*
* Created: 07.05.2021 20:55:40
*  Author: user_01
*/


#include <avr/io.h>

int main(void)
{
	DDRB &= ~1<<1;
	DDRB |= 1<<3;
	
	TCCR0A = 0;
	TCCR0B = 0b00000100;
	
	uint8_t a = 0;
	bool flag = 1;
	
	while(1)
	{
		if (PINB&(1 << 1)) {			
			if (flag) {
				TCNT0 = 0;
				flag = 0;			
			}
		}
		
	   else if (!flag) {		   		  
			a = TCNT0;
			flag = 1;					   		   
	   }
		
		if (a > 56) PORTB |= 1<<3;
		else PORTB &= ~1<<3;

	}
}
