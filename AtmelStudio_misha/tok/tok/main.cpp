/*
 * tok.cpp
 *
 * Created: 11.10.2020 21:38:29
 * Author : user_01
 */ 

 #include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0xff;
    while (1) 
    {
		PORTD = 0xff;
    }
}

