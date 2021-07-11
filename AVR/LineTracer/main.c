#define F_CPU 16000000UL
#define  RIGHT 3
#define  LEFT 2
#define STRAIGHT 1
#define BACKWARD 0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int direction=STRAIGHT;

//왼쪽 모터 속도 변수 : OCR1A, 오른쪽 모터 속도 변수 : OCR1B
//방향 변수 : direction (RIGHT, LEFT, STRAIGHT, BACKWARD 정의되어 있음)
//모터 속도 : 500~600사이
//알고리즘 : 일정 주기마다 방향을 업데이트해 나아감.

int main()
{
	//========기본 세팅========
	EIMSK=0B00000011;
	EICRA=0b00001010;
	
	sei();
	
	DDRA=0XFF;
	DDRB=0XFF;
	DDRC=0XFF;
	DDRD=0X00;
	PORTC=(1<<PC7)|(0<<PC6)|(1<<PC5)|(0<<PC4);
	
	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(0<<WGM10);
	TCCR1B=(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10);
	
	ICR1=799;
	OCR1A=400;
	OCR1B=400;
	//=====================
	
	//======방향 확인======
	while(1)
	{
		if(direction==STRAIGHT)
		{
			PORTC=(0<<PC7)|(1<<PC6)|(0<<PC5)|(1<<PC4);
			OCR1A=500;
			OCR1B=500;
			PORTA=0B00000001;
		}
		else if(direction==BACKWARD)
		{
			PORTC=(1<<PC7)|(0<<PC6)|(1<<PC5)|(0<<PC4);
			OCR1A=500;
			OCR1B=500;
			PORTA=0B00000010;
		}	
		else if (direction==LEFT)
		{
			OCR1A+=10;
			OCR1B=500;
			PORTA=0B00000100;
		}
		else if (direction==RIGHT)
		{
			OCR1A=500;
			OCR1B+=10;
			PORTA=0B00001000;
		}
		if (OCR1A>=600) OCR1A=600;
		if (OCR1B>=600) OCR1B=600;
		_delay_ms(100);
	}
	//=================
}

ISR(INT0_vect)
{
	if(direction==STRAIGHT) direction=RIGHT;
	else if (direction==RIGHT) direction=LEFT;
	else direction=STRAIGHT;
}

ISR(INT1_vect)
{
	direction=BACKWARD;
}