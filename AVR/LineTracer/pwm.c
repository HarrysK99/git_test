/*
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int main()
{
	EIMSK=0B00000011;
	EICRA=0b00001010;
	
	sei();
	
	DDRA=0XFF;
	DDRD=0X00;
	DDRB=0XFF;
	DDRC=0XFF;
	DDRE=0X02;
	DDRF=0X00;
	PORTA=0X00;
	PORTB=0XFF;
	PORTC=0B10100000;
	
	TIMSK=(0<<TICIE1)|(1<<OCIE1A)|(0<<OCIE1B)|(0<<TOIE1);
	ETIMSK|=(0<<OCIE1C);
	TCCR1A=(1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
	
	TCNT1H=0X00;
	TCNT1L=0X00;
	while(1)
	{
		PORTC=(1<<PC7)|(0<<PC6)|(1<<PC5)|(0<<PC4);
		_delay_ms(1000);
		PORTC=(0<<PC7)|(1<<PC6)|(0<<PC5)|(1<<PC4);
		_delay_ms(1000);
	}
	
	ICR1=8192;
	//OCR1A=ICR1;
	//OCR1B=ICR1;
	//while(1);
	
	while(1)
	{
		OCR1A=ICR1*0.1;
		_delay_ms(1000);
		OCR1A=ICR1*0.3;
		_delay_ms(1000);
		OCR1A=ICR1*0.5;
		_delay_ms(1000);
		OCR1A=ICR1*0.7;
		_delay_ms(1000);
		OCR1A=ICR1*0.9;
		_delay_ms(1000);
	}
	
}



*/