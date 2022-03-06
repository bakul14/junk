#include <avr/io.h>
int a;
int main(void)
{
    DDRD = 0xff;
	TCCR0 |= (1<<0) | (1<<2);
	TCCR0 &= ~(1<<1);
    while (1) 
    {
		if (TCNT0 == 255)
		{
			a++;
		}
		
		if (a == 30)
		{
			DDRD |= 1<<0;
		}
		else {
			DDRD = 0x00;
		}
		if (a>30) a = 0;
		
			
		
    }
}

