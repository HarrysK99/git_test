/*
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
	DDRA=0XFF;
	PORTA=0B10000000;
	DDRB=0XFF;
	TCCR0=0B01101010;
	
	while(1)
	{
		OCR0=0X00;
		_delay_ms(1000);
		//OCR0=0X3F;
		//_delay_ms(1000);
		//OCR0=0X7F;
		//_delay_ms(3000);
		OCR0=0XBF;
		_delay_ms(3000);
		OCR0=0XFF;
		_delay_ms(3000);
	}
}
*/