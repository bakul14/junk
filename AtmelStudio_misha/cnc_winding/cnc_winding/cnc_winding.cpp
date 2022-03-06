/*
* CNC_WINDING_MACHINE.cpp
*
* Created: 18.01.2021 15:57:48
*  Author: user_01
*/

/*

PC0 dir1
PC1 step1
PC2 en1
PC3 en2
PC4 step2
PC5 dir2

*/

/*

PD0
PD1
PD2   END1
PD2   END2
PD4
PD5
PD6
PD7

*/



#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

// uint32_t qty = 1000;
// volatile uint32_t pulse_rpm = 0;
//
// uint8_t mass [11] = {
// 	0b11010111,
// 	0b00010100,
// 	0b11001101,
// 	0b01011101,
// 	0b00011110,
// 	0b01011011,
// 	0b11011011,
// 	0b00010101,
// 	0b11011111,
// 	0b01011111,
// 	0b00001000
// };
//
// uint8_t i = 0;
//
// volatile uint8_t r0 = 0;
// volatile uint8_t r1 = 0;
// volatile uint8_t r2 = 0;
// volatile uint8_t r3 = 0;
// volatile uint8_t r4 = 0;
// volatile uint8_t r5 = 0;
// volatile uint8_t r6 = 0;
// volatile uint8_t r7 = 0;
// volatile uint8_t r = 10;
//
// bool dp0 = 0;
// bool dp1 = 0;
// bool dp2 = 0;
// bool dp3 = 0;
// bool dp4 = 0;
// bool dp5 = 0;
// bool dp6 = 0;
// bool dp7 = 0;
//
// #define step1 1
// #define dir1 0
// #define en1 2
// #define step2 4
// #define dir2 5
// #define en2 3
//
// 	int up = 0;
// 	int down = 0;
//
// 	uint8_t n = 0; //_передача
// 	int rpm = 200; //об_мин
// 	float d = 2; //диаметр_провода_мм
// uint8_t a = 10;
//

void segchar (unsigned char seg) {}
int main(void)
{
	unsigned char z = 0;
	

	//
	// 	DDRB = 0xff;; //SPI_out
	// 	DDRC = 0xff; //(step_dir_enable)x2
	// 	DDRD = 0; //buttons
	//
	// 	SREG |= 1<<7; //разрешить_глобальные_прерывания
	// 	SPCR = 0b01010000; //SPI_enable_MSB_clk/4
	//
	//
	//
	// 	TCCR0 = 0b00000010; //TIMER0_clk/8
	//
	// 	TCCR1A = 0;
	// 	TCCR1B = 0b00001010; //TIMER1_clk/8_CTC_mode_(interrupt)
	//
	// 	if (rpm < 38) {TCCR2 = 0b00001101; n = 1;} //TIMER2_clk/128_CTC_mode_(interrupt)
	// 	if (rpm >= 38) {TCCR2 = 0b00001100; n = 2;} //TIMER2_clk/64_CTC_mode_(interrupt)
	// 	if (rpm >= 75) {TCCR2 = 0b00001011; n = 4;} //TIMER2_clk/32_CTC_mode_(interrupt)
	// 	if (rpm >= 300) {TCCR2 = 0b00001010; n = 16;} //TIMER2_clk/8_CTC_mode_(interrupt)
	//
	// 	OCR1A = 149820/d/rpm; //2497/d/(rpm/60)
	// 	OCR2 = (4687.5/rpm)*n-1; //78/rpm/60-1 4680
	//
	// 	TIMSK = 0b00010001; //INTERRUPT: TIMER0_overflow, TIMER1_CTC, TIMER2_CTC
	//
	// 	PORTC &= ~(1<<dir1);
	
	while(1)
	{
		segchar(z);
		
		// 		if (PIND & 1<<0 && pulse_rpm < qty*1600) TIMSK |= 1<<7;  //2497/d/(rpm/60)
		// 		else TIMSK &= ~(1<<7);
		// 		if (PIND & 1<<1) PORTC &= ~(1<<en1); else PORTC |= 1<<en1;
		//
		//         up = pulse_rpm/1600;
		
		// 		r0 = up/1000;
		// 		r1 = up%1000/100;
		// 		r2 = up%1000%100/10;
		// 		r3 = up%1000%100%10;
		// 		r4 = down/1000;
		// 		r5 = down%1000/100;
		// 		r6 = down%1000%100/10;
		// 		r7 = down%1000%100%10;
		
	}
}

// ISR (TIMER0_OVF_vect) {
// 	switch (i) {
// 		case 0: SPDR = mass[r0] | dp0<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b10000000; while(!(SPSR & (1<<SPIF))); break;
// 		case 1: SPDR = mass[r1] | dp1<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b01000000; while(!(SPSR & (1<<SPIF))); break;
// 		case 2: SPDR = mass[r2] | dp2<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00100000; while(!(SPSR & (1<<SPIF))); break;
// 		case 3: SPDR = mass[r3] | dp3<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00010000; while(!(SPSR & (1<<SPIF))); break;
// 		case 4: SPDR = mass[r4] | dp4<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000010; while(!(SPSR & (1<<SPIF))); break;
// 		case 5: SPDR = mass[r5] | dp5<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000100; while(!(SPSR & (1<<SPIF))); break;
// 		case 6: SPDR = mass[r6] | dp6<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00001000; while(!(SPSR & (1<<SPIF))); break;
// 		case 7: SPDR = mass[r7] | dp7<<5; while(!(SPSR & (1<<SPIF))); SPDR = 0b00000001; while(!(SPSR & (1<<SPIF))); break;
// 	}
// 	PORTB |= 1<<2;
// 	PORTB &= ~1<<2;
//
// 	SPDR = 0b10101010;
// 	while(!(SPSR & (1<<SPIF)));
// 	PORTB |= 1<<1;
// 	PORTB &= ~1<<1;
//
// 	i++;
// 	if (i > 7) i = 0;
// }
//
// ISR (TIMER1_COMPA_vect) {
// 	PORTD ^= 1<<step2;
//
// }
//
// ISR (TIMER2_COMP_vect) {
// 	PORTC ^= 1<<step1;
// 	pulse_rpm++;
// 	if (pulse_rpm >= qty*1600) TIMSK &= ~(1<<7 | 1<<4);
// }

