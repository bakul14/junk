/*
* logicanalyzer.cpp
*
* Created: 05.12.2020 16:47:18
*  Author: user_01
*/


#include <avr/io.h>

int main(void)
{
   DDRB = 0xff;
   DDRC = 0xff;
   DDRD = 0xff;
   
   
   PORTD |= 1<<0;
   PORTD |= 1<<1;
   PORTD |= 1<<2;
   PORTD |= 1<<3;
   PORTD |= 1<<4;
   PORTD |= 1<<5;
   PORTD |= 1<<6;
   PORTD |= 1<<7;
   
   PORTB |= 1<<0;
   PORTB |= 1<<1;
   PORTB |= 1<<2;
   PORTB |= 1<<3;
   PORTB |= 1<<4;
   PORTB |= 1<<5;
   
   PORTC |= 1<<0;
   PORTC |= 1<<1;
 
//--------------------------  
   
   PORTD &= ~1<<0;
   PORTD &= ~1<<1;
   PORTD &= ~1<<2;
   PORTD &= ~1<<3;
   PORTD &= ~1<<4;
   PORTD &= ~1<<5;
   PORTD &= ~1<<6;
   PORTD &= ~1<<7;
   
   PORTB &= ~1<<0;
   PORTB &= ~1<<1;
   PORTB &= ~1<<2;
   PORTB &= ~1<<3;
   PORTB &= ~1<<4;
   PORTB &= ~1<<5;
   
   PORTC &= ~1<<0;
   PORTC &= ~1<<1;  
       
}
