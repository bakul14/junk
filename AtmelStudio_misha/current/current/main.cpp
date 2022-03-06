/* PD3-PD0 && PC5-PC2 шина_данных_на_дисплей
   PC1 вход_АЦП
   PC0 && PB1 транзисторы_
*/   
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
	float q = 0;
int main(void)
{
    DDRC |= (1<<5) | (1<<4) | (1<<3) | (1<<2) | (0<<1) | (1<<0);
	DDRD |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
	DDRB |= (1<<1);
	TCCR0 = 0b00000101;
	TIMSK = 0b00000001;
	TCNT0 = 0;
    SREG = 0b10000000;
	ADCSRA = 0b11100011;
	ADMUX = 0b01000001;
    while (1) 
    {
		PORTB &= (0<<1);
		PORTC |= (1<<0);
		PORTD |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
		PORTC |= (1<<5) | (1<<4) | (1<<3) | (1<<2);

		PORTC &= (0<<0);
		PORTB |= (1<<1);
		PORTD |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
		PORTC |= (1<<5) | (1<<4) | (1<<3) | (1<<2);

    }
}
ISR (TIMER0_OVF_vect) {
	q = (ADC/1023*5 - 0.072)/0.088;
}

