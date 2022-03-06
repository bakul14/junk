/*
* pcf8574.c
*
* Created: 11.12.2020 20:13:59
*  Author: user_01
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t i = 0;
int main(void)
{
    TCCR2 = 0b00001111;
	GICR = 1<<7;

	
	TWBR = 18;
	TWSR = 0b00000001;
	
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	
	
	TWDR = 0b01001110;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	
	//    for (i = 255; i >= 0; i--) {
	//    TWDR = i;
	//    TWCR = (1<<TWINT) | (1<<TWEN);
	//    while (!(TWCR & (1<<TWINT)));
	//    _delay_ms(500);
	//    }
	
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}
ISR(TIMER1_COMPA_vect) {

	TWDR = i;
	TWCR = (1<<TWINT) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
	i--;

}