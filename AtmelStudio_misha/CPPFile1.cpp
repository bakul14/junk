#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int a;
	DDRD |= 0b00000011;
	PORTD |= 0b00000001;
    while(1) {
		for(a=0; a<=1; a++){
			PORTD = (1<<a);
			_delay_ms(500);
		}
	}
}