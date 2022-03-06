
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int a = 0;
int main(void)
{
	DDRD = 0xff;
    SREG |= (1<<7);
	TIMSK |= (1<<2);
	TIFR |= (1<<2);
	TCCR1B = 0b00000101;
	TCNT1 = 0;
    while (1) 
    {
	PORTD = 0xff;
	_delay_ms(1000);
	PORTD = 0x00;
	_delay_ms(1000);		
    }
}
ISR (TIMER1_OVF_vect) {
	TCCR1B = 0;
	while(a<10) {
	PORTD = 0xff;
	_delay_ms(50);
	PORTD = 0;
	_delay_ms(50);
	a++;
	}
	a = 0;
	TCCR1B = 0b00000101;
}

