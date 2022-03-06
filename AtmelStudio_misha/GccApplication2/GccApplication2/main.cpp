#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0b00000001;
	PORTD = 0b00000001;
	_delay_ms(1500);
	PORTD = 0;
}