
#include <avr/io.h>

uint8_t flag1_1 = 0;
uint8_t flag1_2 = 0;
uint8_t flag1_3 = 0;

uint8_t flag2_1 = 0;
uint8_t flag2_2 = 0;
uint8_t flag2_3 = 0;

uint8_t flag3_1 = 0;
uint8_t flag3_2 = 0;
uint8_t flag3_3 = 0;

uint8_t pylon1_1 = 0;
uint8_t pylon1_2 = 0;
uint8_t pylon1_3 = 0;

uint8_t pylon2_1 = 0;
uint8_t pylon2_2 = 0;
uint8_t pylon2_3 = 0;

uint8_t pylon3_1 = 0;
uint8_t pylon3_2 = 0;
uint8_t pylon3_3 = 0;

uint8_t pylon1_1_zero = 0;
uint8_t pylon1_2_zero = 0;
uint8_t pylon1_3_zero = 0;

uint8_t pylon2_1_zero = 0;
uint8_t pylon2_2_zero = 0;
uint8_t pylon2_3_zero = 0;

uint8_t pylon3_1_zero = 0;
uint8_t pylon3_2_zero = 0;
uint8_t pylon3_3_zero = 0;

int main(void)
{
	DDRD = 0xff;
	DDRB |= (1<<0) | (0<<1) | (0<<2) | (0<<3) | (0<<4) | (0<<5);
	DDRC = 0x00;
	TCCR0 = 0b00000100;
	TCNT0 = 0;
	while (1)
	{
		//-------------------------------------
		if (PINC &= 1<<3) {
			if (flag1_1 == 0) {
				pylon1_1_zero = TCNT0;
				flag1_1 = 1;
			}
			
		}
		else if (flag1_1 == 1) {
			pylon1_1 = TCNT0 - pylon1_1_zero;
			flag1_1 = 0;
		}
		//-------------------------------------
		if (PINC &= 1<<2) {
			if (flag1_2 == 0) {
				pylon1_2_zero = TCNT0;
				flag1_2 = 1;
			}
			
		}
		else if (flag1_2 == 1) {
			pylon1_2 = TCNT0 - pylon1_2_zero;
			flag1_2 = 0;
		}
		//-------------------------------------
		if (PINC &= 1<<1) {
			if (flag1_3 == 0) {
				pylon1_3_zero = TCNT0;
				flag1_3 = 1;
			}
			
		}
		else if (flag1_3 == 1) {
			pylon1_3 = TCNT0 - pylon1_3_zero;
			flag1_3 = 0;
		}
		//-------------------------------------
		if (PINC &= 1<<0) {
			if (flag2_1 == 0) {
				pylon2_1_zero = TCNT0;
				flag2_1 = 1;
			}
			
		}
		else if (flag2_1 == 1) {
			pylon2_1 = TCNT0 - pylon2_1_zero;
			flag2_1 = 0;
		}
		//-------------------------------------
		if (PINB &= 1<<5) {
			if (flag2_2 == 0) {
				pylon2_2_zero = TCNT0;
				flag2_2 = 1;
			}
			
		}
		else if (flag2_2 == 1) {
			pylon2_2 = TCNT0 - pylon2_2_zero;
			flag2_2 = 0;
		}
		//-------------------------------------
		if (PINB &= 1<<4) {
			if (flag2_3 == 0) {
				pylon2_3_zero = TCNT0;
				flag2_3 = 1;
			}
			
		}
		else if (flag2_3 == 1) {
			pylon2_3 = TCNT0 - pylon2_3_zero;
			flag2_3 = 0;
		}
		//-------------------------------------
		if (PINB &= 1<<3) {
			if (flag3_1 == 0) {
				pylon3_1_zero = TCNT0;
				flag3_1 = 1;
			}
			
		}
		else if (flag3_1 == 1) {
			pylon3_1 = TCNT0 - pylon3_1_zero;
			flag3_1 = 0;
		}
		//-------------------------------------
		if (PINB &= 1<<2) {
			if (flag3_2 == 0) {
				pylon3_2_zero = TCNT0;
				flag3_2 = 1;
			}
			
		}
		else if (flag3_2 == 1) {
			pylon3_2 = TCNT0 - pylon3_2_zero;
			flag3_2 = 0;
		}
		//-------------------------------------
		if (PINB &= 1<<1) {
			if (flag3_3 == 0) {
				pylon3_3_zero = TCNT0;
				flag3_3 = 1;
			}
			
		}
		else if (flag3_3 == 1) {
			pylon3_3 = TCNT0 - pylon3_3_zero;
			flag3_3 = 0;
		}
		//-------------------------------------
		if (pylon1_1 > 20) PORTD |= 1<<0;
		else PORTD &= ~(1<<0);
		//-------------------------------------
		if (pylon1_2 > 20) PORTD |= 1<<1;
		else PORTD &= ~(1<<1);
		//-------------------------------------
		if (pylon1_3 > 20) PORTD |= 1<<2;
		else PORTD &= ~(1<<2);
		//-------------------------------------
		if (pylon2_1 > 20) PORTD |= 1<<3;
		else PORTD &= ~(1<<3);
		//-------------------------------------
		if (pylon2_2 > 20) PORTD |= 1<<4;
		else PORTD &= ~(1<<4);
		//-------------------------------------
		if (pylon2_3 > 20) PORTD |= 1<<5;
		else PORTD &= ~(1<<5);
		//-------------------------------------
		if (pylon3_1 > 20) PORTD |= 1<<6;
		else PORTD &= ~(1<<6);
		//-------------------------------------
		if (pylon3_2 > 20) PORTD |= 1<<7;
		else PORTD &= ~(1<<7);
		//-------------------------------------
		if (pylon3_3 > 20) PORTB |= 1<<0;
		else PORTB &= ~(1<<0);
		//-------------------------------------
		if (PINC &= 0<<3) {
			if (PINC &= 0<<2){
				if (PINC &= 0<<1) {
					if (PINC &= 0<<0) {
						if (PINB &= 0<<5) {
							if (PINB &= 0<<4) {
								if (PINB &= 0<<3) {
									if (PINB &= 0<<2) {
										if (PINB &= 0<<1) TCNT0 = 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

