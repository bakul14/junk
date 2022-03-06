
#include <avr/io.h>
uint8_t a = 0;
uint8_t i = 0;
int main(void)
{
	TCCR0 = 0b00000100;
	TCNT0 = 0;
	DDRD = 0xff;
	DDRB |= (0<<0);
	while (1)
	{
		
		if (PINB &= (1<<0)) {
			if (i == 0) {
				TCNT0 = 0;
				i = 1;
			}
		}
		
		else if (i==1) {
			i = 0;
			a = TCNT0;
		}
		
		if (a>94) PORTD |= (1<<0);
		else PORTD &= (0<<0);

	}
}

