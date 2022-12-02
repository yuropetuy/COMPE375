/*
 * LAB_6.c
 *
 * Created: 10/27/2022 11:11:12 PM
 * Author : Brent Son
 */ 

#define 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

//827108705
//X = 7 + 1 = 8 ms timer interrupt period
//Z = (5 + 1) * 100 = 600 Hz 
//OCR0A = 125
//OCR1A = 167 
//Timer 0 for keypad scan
//Timer 1 for LED

void timer_1(int val)
{
	OCR1B = (val * 0.1) * OCR1A;
}

int main(void)
{
	//Enable LED
	DDRB |= (1<<5);
	
	//keypad enable
	
	//enable keypad pull up inputs
	DDRB &= ~(1<<DDB0);
	DDRB &= ~(1<<DDB1);
	DDRB &= ~(1<<DDB2);
	DDRB &= ~(1<<DDB3);

	PORTB |= (1<<PORTB0);
	PORTB |= (1<<PORTB1);
	PORTB |= (1<<PORTB2);
	PORTB |= (1<<PORTB3);
	
	//enable keypad outputs
	DDRD |= (1<<DDD3);
	DDRD |= (1<<DDD4);
	DDRD |= (1<<DDD5);
	DDRD |= (1<<DDD6);		//skip this pin as it is physically damaged
	DDRD |= (1<<DDD7);

    //timer 0 initialization
	TCCR0A |= (1<<WGM01);				//CTC Mode
	TCCR0B |= (1<<CS00 | 1<<CS02);		//PS: 1024
	TIMSK0 |= (1<<OCIE0A);	//Enable OCF1A Interrupt
	OCR0A = 125;
	
	//timer 1 initialization
	TCCR1A |= (1<<WGM01)		//CTC Mode
	TCCR1B |= (1<<CS02);		//PS: 256
	OCR1A = 167;
	TIMSK1 |= (1<<OCIE1A | 1<<OCIE1B);
	sei();
	
    while (1) {}
}

ISR(TIMER0_COMPA_vect)
{
	//variables
	int i, j;
	
	PORTD |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	for(i = 3; i < 8 ; i++)
	{
		PORTD &= ~(1<<i);
		for(j = 0; j < 4; j++)
		{
			while (!(PINB & (1<<j)))
			{
				if(i == 3)
				{
					if(j == 0)
					timer_1(1);
					else if(j == 1)
					timer_1(2);
					else if(j == 2)
					timer_1(3);
					//else if(j == 3)
					//OCR0A = 118;
				}
				else if(i == 4)
				{
					if(j == 0)
					timer_1(4);
					else if(j == 1)
					timer_1(5);
					else if(j == 2)
					timer_1(6);
					//else if(j == 3)
					//OCR0A = 93;
				}
				else if(i == 5)
				{
					if(j == 0)
					timer_1(7);
					else if(j == 1)
					timer_1(8);
					else if(j == 2)
					timer_1(9);
					//else if(j == 3)
					//OCR0A = 74;
				}
				else if(i == 7)
				{
					//if(j == 0)
					//OCR0A = 70;
					else if(j == 1)
					timer_1(0);
					//else if(j == 2)
					//OCR0A = 62;
					//else if(j == 3)
					//OCR0A = 58;
				}
}

ISR(TIMER1_COMPA_vect)
{
	PORTB |= (1<<5);
}

ISR(TIMER1_COMPB_vect)
{
	PORTB &= ~(1<<5);
}
