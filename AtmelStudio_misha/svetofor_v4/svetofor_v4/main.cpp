#include <avr/io.h>
uint8_t a = 0;
uint8_t b = 0;
uint8_t c = 0;

uint8_t a1 = 0;
uint8_t b1 = 0;
uint8_t c1 = 0;

uint8_t d1 = 0;
uint8_t d2 = 0;
uint8_t d3 = 0;

uint8_t timera = 0;
uint8_t timerb = 0;
uint8_t timerc = 0;

#define sec 2
int main(void)
{
    TCCR1B = 0b00000101;
	TCNT1 = 0;
	TCCR0 = 0b00000100;
	TCNT0 = 0;
	DDRB |= (0<<0) | (0<<1) | (0<<2); // ���� �������� � ���������
	DDRD |= (1<<5) | (1<<6) | (1<<7); // ����� ������� �� ��������
	
	while (1) {
		// -------------------------------------
		if (PINB &= (1<<0)) {
			if (a == 0) {
				a1 = TCNT0;
				a = 1;
			}
		}
		else if (a==1) {
			a = 0;
			timera = TCNT0 - a1;
		}
		// -------------------------------------
		if (PINB &= (1<<1)) {
			if (b == 0) {
				b1 = TCNT0;
				b = 1;
			}
		}
		else if (b==1) {
			b = 0;
			timerb = TCNT0 - b1;
		}
		// -------------------------------------
		if (PINB &= (1<<2)) {
			if (c == 0) {
				c1 = TCNT0;
				c = 1;
			}
		}
		else if (c==1) {
			c = 0;
			timerc = TCNT0 - c1;
		}
		// -------------------------------------
		if (timera>20) {			
			PORTD |= (1<<7);
			d1 = TCNT1;
		}
		else if ((TCNT1-d1) > 3906*sec) PORTD &= ~(1<<7);
		//PORTD &= ~(1<<7);
		// -------------------------------------
		if (timerb>20) PORTD |= (1<<6);
		else PORTD &= ~(1<<6);
		// -------------------------------------
		if (timerc>20) PORTD |= (1<<5);
		else PORTD &= ~(1<<5);
		// -------------------------------------
		if (PINB &= (0<<0)) {
			if (PINB &= (0<<1)) {
				if (PINB &= (0<<2)) TCNT0 = 0;
			}
		}
		// -------------------------------------
	}

}