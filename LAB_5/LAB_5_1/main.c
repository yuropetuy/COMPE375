/*
 * LAB 5.c
 *
 * Created: 10/20/2022 3:02:22 PM
 * Author : Brent Son
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <math.h>

//progression of notes: A, A#, B, C, C#, D, D#, E, F, F#, G, G#, A, A#, B
/*
int scan(void)
{
	//variables
	int key[2];
	int i,j;
	static int x;
	
	//scan key
	PORTD |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
	for(i = 3; i < 8 ; i++)
	{
		PORTD &= ~(1<<i);
		for(j = 0; j < 4; j++)
		{
			if (!(PINB & (1<<j) && !(PORTD & (1<<i))))
			{
				key[0] = i;
				key[1] = j;
			}
		}
		PORTD |= (1<<i);
	}
	if(key[0] == 3)
	{
		if(key[1] == 0)
		x = 0;
		else if(key[1] == 1)
		x = 1;
		else if(key[1] == 2)
		x = 2;
		else if(key[1] == 3)
		x = 3;
	}
	else if(key[0] == 4)
	{
		if(key[1] == 0)
		x = 4;
		else if(key[1] == 1)
		x = 5;
		else if(key[1] == 2)
		x = 6;
		else if(key[1] == 3)
		x = 7;
	}
	else if(key[0] == 5)
	{
		if(key[1] == 0)
		x = 8;
		else if(key[1] == 1)
		x = 9;
		else if(key[1] == 2)
		x = 10;
		else if(key[1] == 3)
		x = 11;
	}
	else if(key[0] == 7)
	{
		if(key[1] == 0)
		x= 12;
		else if(key[1] == 1)
		x = 13;
		else if(key[1] == 2)
		x = 14;
		else if(key[1] == 3)
		x = 15;
	}
	return x;
}
*/

/*
void calculate_timer_period(int x)
{
	float exp = (1/12);
	float y = pow(2, exp);
	//float t_on = (1 / (440 * pow(y, x)));
	//float time_period = (t_on * 256) / 0.004545;
	float t_on = 440 * pow(y, x);
	float t_on_adjusted = pow(t_on , -1);
	float time_period = (t_on_adjusted * 256) / 0.004545;
	OCR0A = (time_period) - 1;
	//OCR0A = 101;
	OCR0B = OCR0A * 0.5;
}
*/

int main(void)
{	
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
	
	//enable audio output
	DDRB |= (1<<DDB4);
	DDRB |= (1<<DDB5);
	
	//initialize timer and timer settings
	TCCR0A |= (1 << WGM01);		//timer mode CTC mode
	TCCR0B |= (1<<CS02);		// set pre scale value to 256
	
	//variables
	int key[2];
	int i,j;
	int x;
	
	
    while (1) 
    {
		//x = scan();
		
		PORTD |= (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);
		for(i = 3; i < 8 ; i++)
		{
			PORTD &= ~(1<<i);
			for(j = 0; j < 4; j++)
			{
				if (!(PINB & (1<<j)))
				{
					key[0] = i;
					key[1] = j;
				}
			}
			PORTD |= (1<<i);
		}
		if(key[0] == 3)
		{
			if(key[1] == 0)
			//x = 0;
			OCR0A = 141;
			else if(key[1] == 1)
			//x = 1;
			OCR0A = 133;
			else if(key[1] == 2)
			//x = 2;
			OCR0A = 126;
			else if(key[1] == 3)
			//x = 3;
			OCR0A = 118;
		}
		else if(key[0] == 4)
		{
			if(key[1] == 0)
			//x = 4;
			OCR0A = 112;
			else if(key[1] == 1)
			//x = 5;
			OCR0A = 105;
			else if(key[1] == 2)
			//x = 6;
			OCR0A = 99;
			else if(key[1] == 3)
			//x = 7;
			OCR0A = 93;
		}
		else if(key[0] == 5)
		{
			if(key[1] == 0)
			//x = 8;
			OCR0A = 88;
			else if(key[1] == 1)
			//x = 9;
			OCR0A = 83;
			else if(key[1] == 2)
			//x = 10;
			OCR0A = 78;
			else if(key[1] == 3)
			//x = 11;
			OCR0A = 74;
		}
		else if(key[0] == 7)
		{
			if(key[1] == 0)
			//x= 12;
			OCR0A = 70;
			else if(key[1] == 1)
			//x = 13;
			OCR0A = 66;
			else if(key[1] == 2)
			//x = 14;
			OCR0A = 62;
			else if(key[1] == 3)
			OCR0A = 58;
			//x = 15;
		}
		
		//calculate_timer_period(x);
		/*
		float exp = 0.83333333;
		float y = pow(2, exp);
		float t_on = 440 * pow(y, x);
		float t_on_adjusted = pow(t_on , -1);
		float time_period = (t_on_adjusted * 256) / 0.004096;
		int time_period_adjusted = (int)time_period;
		//OCR0A = time_period_adjusted - 1;
		OCR0B = (OCR0A * 0.5);
		*/
		OCR0B = (OCR0A * 0.5);
		//t off
		PORTB &= ~(1<<PORTB4);
		PORTB &= ~(1<<PORTB5);
		//busy while loop for OCR0B overflow flag
		while(!(TIFR0 & (1<<OCF0B)));
		//OCR0B overflow flag reset
		TIFR0 |= (1<<OCF0B);
		
		//t on
		PORTB |= (1<<PORTB4);
		PORTB |= (1<<PORTB5);
		//busy while loop for OCR0A overflow flag
		while(!(TIFR0 & (1<<OCF0A)));
		//OVR0A overflow flag reset
		TIFR0 |= (1<<OCF0A);	
	}
}






