
#include <avr/io.h>

int main(void)
{
	DDRB = 0xff;
	TCCR1A = 0b01000011;
	TCCR1B = 0b00011001;
	OCR1A = 99;
}