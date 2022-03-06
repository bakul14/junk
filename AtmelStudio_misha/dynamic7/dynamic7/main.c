#include <avr/io.h>
uint8_t a = 0;
uint8_t i = 0;
uint8_t r1 = 0;
uint8_t r2 = 0;
uint8_t mass [10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0xff, 0b01101111};
int main(void)
{
	TCCR0 = 0b00000100;
	DDRD = 0xff;
	DDRB |= (1<<6) | (1<<7); // 1 and 2 modul
	TCNT0 = 0;
	while (1)
	{
		if (i == 245) {
			a++;
			i = 0;
		}
		if (a > 59) a = 0;
		r1 = a/10;
		r2 = a%10;
		
		if (TCNT0 == 127) {
			PORTB = 0b00000010;
			PORTD = mass[r1];
		}
		
		if (TCNT0 == 255) {
			PORTB = 0b00000100;
			PORTD = mass[r2];
			i++;
			TCNT0 = 0;
		}		
	}
}
