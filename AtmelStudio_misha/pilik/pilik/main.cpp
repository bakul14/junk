#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	unsigned char a;
	DDRD = 0b00000011;
	while(1) {
		for(a=0; a<=1; a++){
			PORTD = 0b00000001<<a;
			_delay_ms(100);
		}
	 a = 0;
	}
}