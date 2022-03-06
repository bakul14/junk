#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	bool flag1 = 0;
	bool flag2 = 0;
	int a = 0;
	DDRD = 0b00000011;
	PORTD = 0b00000100;
	while(1) {
		if (!(PIND&0b00000100) && flag1 == 0)
		{
			flag1 = 1;
			flag2 = !flag2;
			if (flag2 == 1 && a>1000) {
				PORTD = 0b00000101;
			}
			else {
				PORTD = 0b00000100;
				
			}
			
		}
		if (!(PIND&0x00) && flag1 == 1) {
			flag1 = 0;
		}
		
		a++;
		//a = 0;
	}
}
