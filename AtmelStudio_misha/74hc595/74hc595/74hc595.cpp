/*
* _74hc595.cpp
*
* Created: 12.10.2020 21:39:51
*  Author: user_01
*/
// 0 - точка вкл., 1 - точка выкл.

//MUX3:0 : 0000 - adc0, 0001 - adc1, adc2 - 0010

// пусть максимальный ток = 100А = 5В на выходе ОУ. максимальная рассеиваемая мощность 0,5вт, при токе 100А Rш = 0.00005 Om. u = ir = 0.00005*100=0.005v
// j = 5/0.005 = 1000. r1/r2 = 1/999. провод 10мм2, длина = 0.00005*10/0.017 = 29.4мм
// PD4 - ИСКУСТВЕННАЯ ЗЕМЛЯ
// шаг регулировки газа - 32мкс
// выходные импульсы газа - 1023..2023мкс
#define adcc0 400 // минимальное входное напряжение ручки газа
#define adcc1 600 // максимальное входное напряжение ручки газа
#define adcc01 1023 // разность adc1 и adc0
#define k 5
#define n 4
#define F_CPU 2000000
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t mass12 [10] = {0b00000001, 0b11000111, 0b00100010, 0b10000010, 0b11000100, 0b10001000, 0b00001000, 0b11000011, 0b00000000, 0b10000000};
uint8_t mass3  [10] = {0b00000001, 0b00110111, 0b01000010, 0b00010010, 0b00110100, 0b00011000, 0b00001000, 0b00110011, 0b00000000, 0b00010000};
uint8_t mass45 [10] = {0b00010000, 0b01111100, 0b00100010, 0b00101000, 0b01001100, 0b10001000, 0b10000000, 0b00111100, 0b00000000, 0b00001000};

volatile uint8_t v = 0; // экран, верхняя строка
volatile int q = 0;     // экран, нижняя строка


volatile uint8_t r1 = 0;
volatile uint8_t r2 = 0;
volatile uint8_t r3 = 0;
volatile uint8_t r4 = 0;
volatile uint8_t r5 = 0;

volatile bool dp1 = 1;
volatile bool dp2 = 1;
volatile bool dp3 = 1;
volatile bool dp4 = 1;
volatile bool dp5 = 1;


uint8_t a = 0;



volatile uint16_t hz = 0;
volatile bool flag1 = 0;
volatile bool flag2 = 0;
volatile bool flag3 = 0;
volatile int voltage = 0;
int main(void) {

	uint8_t mode = 1;
	uint8_t light = 0;

	int mileage_now = 0;
	// 	int mileage_total = 0;



	
	
	ADMUX = 0b01000010;
	ADCSRA = 0b11001100;
	
	DDRB |= ((1<<3)|(1<<2)|(1<<5));         //ножки_SPI_на_выход
	PORTB &= ~((1<<3)|(1<<2)|(1<<5));       //сбрасываем состояние ножек шины SPI
	SPCR = 0b01010000;                      //включить_шину SPI, режим_MASTER_(ведущий)
	
	DDRD &= ~(1<<7 | 1<<6 | 1<<5); // кнопки
	PORTD |= 1<<7 | 1<<6 | 1<<5; // кнопки подтянуть к +
	DDRD |= 1<<0; // фара

	TCCR1A = 0b10000010;
	TCCR1B = 0b00010001; //  clk/1
	ICR1 = 20000;
	
	DDRB |= 1<<1; // газ
	
	DDRC &= ~(1<<0 | 1<<1 | 1<<2);
	
	TCCR0 = 0b00000101; // clk/1024
	TCNT0 = 0;
	TCCR2 = 0b00000101; // clk/1024
	TCNT2 = 0;
	SREG |= 1<<7; //разрешить_глобальные_прерывания
	TIMSK |= 1<<0; //вкл_прерывания_по_переполнению_таймера0


	
	GICR = 0b01000000; // enable interrupt int0
	MCUCR = 0b00000010; // falling, int0
	
	for (a = 0; a<5; a++) {
		SPDR = 0xff;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<2); //enter
		PORTB &= ~(1<<2); //enter
	}




	
	
	
	
	
	while(1)
	{
		
		if (!(PIND & 1<<7) && flag1 == 0) {
			light++;
			flag1 = 1;
		}
		if (light > 2) light = 0;


		if (!(PIND & 1<<6) && flag2 == 0) {
			mode++;
			flag2 = 1;
		}
		if (mode > 5) mode = 1;

		
		switch (light)
		{
			case 0: PORTD &= ~(1<<0); break;
			case 1: PORTD ^= 1<<0; break;
			case 2: PORTD |= 1<<0; break;
		}
		
		switch (mode) {
			case 1:
			dp2 = 1; dp3 = 0; q = voltage*0.1; break;

			case 2:
			q = mileage_now;
			dp2 = 1; dp3 = 0;
			break;
			
			case 3: q = 3; break;
			case 4: q = 4; break;
		}
			
		if (TCNT2 > 250) v = 0;
		mileage_now = hz * 0.002; // пробег в сотнях метров, 4 магнита, колесо 10 дюймов
		
		r1 = v*0.1;
		r2 = q*0.01;
		r3 = q%100*0.1;
		r4 = q%10;
		r5 = v%10;
	}
}
ISR (TIMER0_OVF_vect) {
	SPDR = mass45 [r5] | dp5<<0;
	while(!(SPSR & (1<<SPIF)));
	SPDR = mass45 [r4] | dp4<<0;
	while(!(SPSR & (1<<SPIF)));
	SPDR = mass3 [r3]  | dp3<<7;
	while(!(SPSR & (1<<SPIF)));
	SPDR = mass12 [r2] | dp2<<4;
	while(!(SPSR & (1<<SPIF)));
	SPDR = mass12 [r1] | dp1<<4;
	while(!(SPSR & (1<<SPIF)));
	
	PORTB |= (1<<2); //enter
	PORTB &= ~(1<<2); //enter

	TCNT0 = 0;
	if (PIND & 1<<6) flag2 = 0;
	if (PIND & 1<<7) flag1 = 0;

}

ISR (INT0_vect) {
	v = 1400/TCNT2;//3.6*0.254*3.14/n/0.000512/t получаем скорость в км/час
	TCNT2 = 0;
	hz++;
}
ISR (ADC_vect) {
	switch (ADMUX) {
		case 0b01000000: voltage = ADC*0.49*k; ADMUX = 0b01000010; break;
	    case 0b01000010: OCR1A = 5*(ADC - 372) + 1560; ADMUX = 0b01000000; break;
	}
	ADCSRA |= 1<<ADSC;
}