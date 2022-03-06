/*
* interrupt_winding.cpp
*
* Created: 08.02.2021 9:08:28
*  Author: user_01
*/



#include <avr/io.h>
#include <avr/interrupt.h>

#define plus 0
#define minus 1
#define enter 4
#define razryad 5
#define dir_button  6
#define play  7

#define step1 1
#define dir1 0
#define en1 2
#define step2 4
#define dir2 5
#define en2 3


volatile uint16_t rpm = 40;
volatile uint16_t d100 = 0;

volatile uint32_t accel1;
volatile uint16_t accel22 = 4000;
volatile uint8_t accel2;

volatile uint16_t N = 0;
volatile uint16_t N0 = 0;



uint8_t mass [11] = {
	0b11010111,
	0b00010100,
	0b11001101,
	0b01011101,
	0b00011110,
	0b01011011,
	0b11011011,
	0b00010101,
	0b11011111,
	0b01011111,
	0b00001000
};

volatile uint8_t r0 = 0;
volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;
volatile uint8_t r6 = 0;
volatile uint8_t r7 = 0;

volatile uint16_t up = 0;
volatile uint16_t down = 0;

bool dp0 = 0;
bool dp1 = 0;
bool dp2 = 0;
bool dp3 = 0;
bool dp4 = 0;
bool dp5 = 0;
bool dp6 = 0;
bool dp7 = 0;

volatile uint16_t data_out = 0b10000001;


volatile uint8_t laynow = 1;
volatile uint32_t nnow = 0;
volatile uint16_t kolvonow = 0;

bool flag = 1;
bool flag_pp = 0;

uint16_t k = 100; //коэффициент_ввода_чисел_по_разрядам
bool dir = 0;
uint8_t mode = 0b00000001;

volatile uint8_t r = 0;


volatile bool smena = 1;





void work() {
	TIMSK |= 1<<4 | 1<<7;
	PORTC &= ~(1<<en2 | 1<<en1);
	
	PORTC ^= !dir<<dir2;
	
	while (1) {
		// 		if (PIND & 1<< plus && flag && rpm < 450) {
		// 			rpm += 10;
		// 			flag = 0;
		// 		}
		// 		if (PIND & 1<< minus && flag && rpm > 40) {
		// 			rpm -= 10;
		// 			flag = 0;
		// 		}
		//         case (PIND) {
		// 			switch 0b00000001:
		// 			switch 0b00000010:
		// 			switch 0b00010000:
		// 		}

		if (PIND & 1<<enter && flag) { 
			if (smena == 1) smena = 0;
			else smena = 1;
			 flag = 0;
		 }
			
		
		switch (smena) {
			case 0:		
			if (PIND & 1<<plus && flag && d100 < 300) {
				d100 = d100 + 1;;
				flag = 0;
			}
			if (PIND & 1<<minus && flag && d100 > 10) {
				d100 = d100 - 1;
				flag = 0;
			}
			data_out = 0b01000001 | 1<<(dir+4) | 1<<(smena+2);
			down = d100;
			dp5 = 1;
			break;
			
			
			case 1:
			if (PIND & 1<< plus && flag && rpm < 450) {
				rpm += 10;
				flag = 0;
			}
			if (PIND & 1<< minus && flag && rpm > 40) {
				rpm -= 10;
				flag = 0;
			}
			data_out = 0b01000001 | 1<<(dir+4) | 1<<(smena+2);
			down = rpm;
			dp5 = 0;
			break;
		}
		
		


		if (kolvonow >= N) {
			TIMSK &= ~(1<<4 | 1<<7);
			PORTC |= 1<<en1 | 1<<en2;
		}
		if (kolvonow >= N0*laynow) {
			TIMSK &= ~(1<<4 | 1<<7);
			laynow++;
			PORTC ^= 1<<dir2;
			accel22 = 4000;
			TIMSK |= 1<<4 | 1<<7;
		}
		
		kolvonow = nnow/1600;
		
		up = kolvonow;
		
		
		
		OCR1A = 150000/rpm/d100*100 - 1 + accel1;
		OCR2 = 9375/rpm - 1 + accel2;
		accel2 = accel22/16;
		accel1 = accel2*16/d100*100;
		
		
		
		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;
		
		
		switch (r) {
			case 0: SPDR = mass[r0] | dp0<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
			case 1: SPDR = mass[r1] | dp1<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
			case 2: SPDR = mass[r2] | dp2<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
			case 3: SPDR = mass[r3] | dp3<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
			case 4: SPDR = mass[r4] | dp4<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
			case 5: SPDR = mass[r5] | dp5<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
			case 6: SPDR = mass[r6] | dp6<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
			case 7: SPDR = mass[r7] | dp7<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
		}
		PORTB |= 1<<2;
		PORTB &= ~1<<2;
		
		SPDR = data_out;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= 1<<1;
		PORTB &= ~1<<1;
		
		r++;
		if (r > 7) r = 0;
	}
}



int main(void)
{
	
	PORTC |= 1<<en1 | 1<<en2;
	
	SREG |= 1<<7;
	
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0;
	
	SPCR = 0b01010000; //SPI_enable_MSB_clk/4
	
	TCCR1A = 0;
	TCCR1B = 0b00001010;
	
	TCCR2 = 0b00001100;
	
	r0 = r1 = r2 = r3 = r4 = r5 = r6 = r7 = 10;
	
	TCCR0 = 0b00000101;
	

	TIMSK |= 1<<0;
	while(1)
	{
		if (rpm > 450) rpm = 450;
		if (rpm < 40) rpm = 40;

		r0 = up/1000;
		r1 = up%1000/100;
		r2 = up%1000%100/10;
		r3 = up%1000%100%10;
		r4 = down/1000;
		r5 = down%1000/100;
		r6 = down%1000%100/10;
		r7 = down%1000%100%10;


		switch (mode) {
			case 0b00000001: up = N; dp1 = 0; break;
			case 0b00000010: up = N0; dp1 = 0; break;
			case 0b00000100: up = d100; dp1 = 1; break;
			case 0b00001000: rpm = up = rpm; dp1 = 0; break;
		}

		
		if (PIND & 1<<plus && flag) {
			switch (mode) {
				case 0b00000001: N = N + k; up = N; break;
				case 0b00000010: N0 = N0+k; up = N0; break;
				case 0b00000100: d100 = d100+k; up = d100; break;
				case 0b00001000: rpm = rpm+10; up = rpm; break;
			}
			flag = 0;
		}
		
		
		if (PIND & 1<<minus && flag) {
			switch (mode) {
				case 0b00000001: N = N - k; up = N; break;
				case 0b00000010: N0 = N0 - k; up = N0; break;
				case 0b00000100: d100 = d100 - k; up = d100; break;
				case 0b00001000: rpm = rpm - 10; up = rpm; break;
			}
			flag = 0;
		}
		
		
		if (PIND & 1<<enter && flag) {
			mode <<= 1;
			flag = 0;
		}
		if (mode > 0b00001000) {
			mode = 0b00000001;
		}
		
		
		if (PIND & 1<< razryad && flag) {
			if (k == 1) k = 1000;
			k /= 10;
			flag = 0;
		}
		
		
		if (PIND & 1<< dir_button && flag) {
			dir = !dir;
			flag = 0;
		}
		
		if (PIND & 1<<play && flag) {
			flag = 0;
			dp1 = 0;
			data_out = 0b01000000 | 1<<(dir+4);
			work();
		}
		
		if (PIND & 1<<razryad && PIND & 1<<enter) {
			r4 = r5 = r6 = r7 = 10;
			data_out = 0;
			TIMSK |= 1<<7;
			PORTC &= ~(1<<en1);
			accel22 = 4000;
			dp1 = 0;
			while (1) {
				r0 = up/1000;
				r1 = up%1000/100;
				r2 = up%1000%100/10;
				r3 = up%1000%100%10;
				if (PIND & 1<< plus && flag && rpm < 450) {
					rpm += 10;
					flag = 0;
				}
				if (PIND & 1<< minus && flag && rpm > 40) {
					rpm -= 10;
					flag = 0;
				}
				up = rpm;
				
				
				
				OCR2 = 9375/rpm - 1 + accel2;
				accel2 = accel22/16;
				
				
				switch (r) {
					case 0: SPDR = mass[r0] | dp0<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
					case 1: SPDR = mass[r1] | dp1<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
					case 2: SPDR = mass[r2] | dp2<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
					case 3: SPDR = mass[r3] | dp3<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
					case 4: SPDR = mass[r4] | dp4<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
					case 5: SPDR = mass[r5] | dp5<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
					case 6: SPDR = mass[r6] | dp6<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
					case 7: SPDR = mass[r7] | dp7<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
				}
				PORTB |= 1<<2;
				PORTB &= ~1<<2;
				
				SPDR = data_out;
				while(!(SPSR & (1<<SPIF)));
				PORTB |= 1<<1;
				PORTB &= ~1<<1;
				
				r++;
				if (r > 7) r = 0;
				
			}
		}
		
		
		
		
		
		
		
		data_out = mode | 1<<7 | 1<<(dir+4);
		


		
		switch (r) {
			case 0: SPDR = mass[r0] | dp0<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
			case 1: SPDR = mass[r1] | dp1<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
			case 2: SPDR = mass[r2] | dp2<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
			case 3: SPDR = mass[r3] | dp3<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
			case 4: SPDR = mass[r4] | dp4<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
			case 5: SPDR = mass[r5] | dp5<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
			case 6: SPDR = mass[r6] | dp6<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
			case 7: SPDR = mass[r7] | dp7<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
		}
		PORTB |= 1<<2;
		PORTB &= ~1<<2;
		
		SPDR = data_out;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= 1<<1;
		PORTB &= ~1<<1;
		
		r++;
		if (r > 7) r = 0;
		
		
		
	}
}


ISR (TIMER0_OVF_vect) {
	if (PIND == 0) flag = 1;
}

ISR (TIMER1_COMPA_vect) {
	PORTC ^= 1<<step2;
}

ISR (TIMER2_COMP_vect) {
	PORTC^= 1<<step1;
	if (accel22 == 0) accel22 = 1;
	accel22 = accel22 - 1;
	nnow++;
	
}