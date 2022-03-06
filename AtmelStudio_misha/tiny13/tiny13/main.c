
#include <avr/io.h>

uint8_t i = 0;
uint8_t a = 0;
uint8_t b = 0;
uint8_t c = 0;
int main(void)
{
	TCCR0B |= (1<<0);
	TCCR0B |= (0<<0) | (0<<0);
	TCNT0 = 0;
	while (1)
	{
		if ((PINB |= (1<<0)) | (PINB |= (1<<1)) | (PINB |= (1<<2)) & (i == 0)) { 
			TCNT0 = 0;
			 i = 1;
		 }
		
		if (PINB |= (0<<0)) a = TCNT0;
		if (PINB |= (0<<1)) b = TCNT0;
		if (PINB |= (0<<2)) c = TCNT0;

        if ((PINB |= (0<<0)) & (PINB |= (0<<1)) & (PINB |= (0<<2))) { 
			TCNT0 = 0; 
			i = 0;
		 }
		
		if (a>45) PORTB |= (1<<3);
		else PORTB |= (0<<3);
		if (b>45) PORTB |= (1<<4);
		else PORTB |= (0<<4);
		if (c>45) PORTB |= (1<<5);
		else PORTB |= (0<<5);
	}
}

