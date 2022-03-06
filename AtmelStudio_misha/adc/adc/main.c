#include <avr/io.h>
int main(void)
{
	DDRD = 0xff;
	DDRC |= (1<<0);
    ADMUX = 0b01000000;
	ADCSRA = 0b10100111;	
    while (1) 
    {
		if (ADC > 511) PORTD = 0xff;
		else PORTD = 0;
    }
}

