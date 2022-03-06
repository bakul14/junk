#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char a;
    DDRD = 0b01111111;
    while (1) 
    {
		for(a = 0; a<=9; a++){
			segment(a);
		}
// 		PORTD = 0b00000110;
// 		_delay_ms(1000);
// 		PORTD = 0b01011011;
// 	    _delay_ms(1000);
// 		PORTD = 0b01001111;
// 		_delay_ms(1000);
// 		PORTD = 0b01100110;
// 		_delay_ms(1000);
// 		PORTD = 0b01101101;
// 		_delay_ms(1000);
// 		PORTD = 0b01111101;
// 		_delay_ms(1000);
// 		PORTD = 0b00000111;
// 		_delay_ms(1000);
// 		PORTD = 0b01111111;
// 		_delay_ms(1000);
// 		PORTD = 0b01101111;
// 		_delay_ms(1000);
// 		PORTD = 0b00111111;
// 		_delay_ms(1000);

		
    }
}

void segment(unsigned long b) {
	switch(b) {
		case 0: PORTD = 0b00111111; break;
		case 1: PORTD = 0b00000110; break;
		case 2: PORTD = 0b01011011; break;
		case 3: PORTD = 0b01001111; break;
		case 4: PORTD = 0b01100110; break;
		case 5: PORTD = 0b01101101; break;
		case 6: PORTD = 0b01111101; break;
		case 7: PORTD = 0b00000111; break;
		case 8: PORTD = 0b01111111; break;
		case 9: PORTD = 0b01101111; break;
	}
}

