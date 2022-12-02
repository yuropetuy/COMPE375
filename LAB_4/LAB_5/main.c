/*
 * LAB_5.c
 *
 * Created: 10/6/2022 10:58:03 PM
 * Author : Brent Son
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#define LEDON PORTB |= (1<<4)
#define LEDOFF 

//10 increments of 1s is 10ms
//(1/16000000) * 1024 * 156 = 0.009984 or about 10 ms 

void buttonPressed()
{
	if(OCR0B < OCR0A)
	{
		OCR0B += (0.1 * OCR0A);				//add 10% to the duty cycle
	}
	else(OCR0B == OCR0A);					// do nothing if at 100%
}

void buttonNotPressed()
{
	if(OCR0B > 0)
	{
		OCR0B -= (0.1 * OCR0A);				//subtract 10% from duty cycle
	}
	else(OCR0B == 0);						//do nothing at 0%
}

int main(void)
{
	TCCR0A |= (1<<WGM01);					//set Mode of Operation to CTC
	OCR0A = 155;							//set increment time to 155 units
	OCR0B = 0;								// set duty cycle to 0% of period		
	TCCR0B |= (1<<CS02) | (1<<CS00);		//set pre-scaler value to 1024
    while (1) 
    {
		//detect button input
		if(button pressed)
		{
			buttonPressed();	
		} 
		else if(button not pressed)
		{
			buttonNotPressed();
		}
		LEDON								//turn on LED
		while(!(TIFR0 & (1<<OCF0B)));		//wait for duty cycle overflow flag
		TIFR0 |= (1<<OCF0B);				//reset OCR0B overflow flag
		LEDOFF								//turn off LED
		while(!(TIFR0 & (1<<OCF0A)));		//wait for period overflow flag
		TIFR0 |= (1<<OCF0A);				//reset OCR0A overflow flag
    }
}

