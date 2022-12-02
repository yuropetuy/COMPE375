/*
 * LAB_7.c
 *
 * Created: 11/17/2022 2:41:40 PM
 * Author : Brent
 */ 

//#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

/*
REDID: 82718705
X: 7 + 1 = 8ms = 8000us interrupt period to start the A/D
Y: 0 % 6 = A/D Channel 0
Z: (5 + 1) * 100 = 600Hz PWM Frequency

LED0: PB5 

LED Timer Controls:
Desired Period: 1667us
Prescale: 256
OCRA value: 104 - 1

AD Timer Controls
Desired Period: 8000us
Prescale: 1024
OCRA value:124 - 1
*/

uint16_t variable = 0;

ISR(ADC_vect)
{
	OCR2B = OCR2A * (ADC / 1024.0);
	//take sample from ADC
	//data transfered is in "ADC" register
}

ISR(TIMER2_COMPA_vect)
{
	//LED on
	//OCR2B = variable / OCR2A;
	PORTB |= (1<<PORTB5);
}

ISR(TIMER2_COMPB_vect)
{
	//LED off
	PORTB &= ~(1<<PORTB5);
}

int main(void)
{
	//Pin Enables
	DDRB |= (1<<DDRB5);
	DDRC &= ~(1<<DDRC0);
	
	//Turn off LED
	PORTB &= ~(1<<PORTB5);
	
	//A/D Timer Init
	//Timer 0
	TCCR0A |= (1<<WGM01);				//CTC Mode
	TCCR0B |= (1<<CS00) | (1<<CS02);	//PS:1024 
	TIMSK0 |= (1<<OCIE0A);				//Enable OCF0A Interrupt
	OCR0A = 124;
	OCR2B = 0;
	
    //LED Timer Init
	//Timer 2
	TCCR2A |= (1<<WGM21);					//CTC Mode
	TCCR2B |= (1<<CS22);					//PS: 256
	TIMSK2 |= (1<<OCIE2A) | (1<<OCIE2B);	//Enable OCF2A Interrupt
	OCR2A = 53;
	
	//ADC Init
	ADMUX |= (1<<REFS0);	//Channel 0
	ADCSRA |= (1<<ADEN) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS1) | (1<<ADPS0);	//enable auto trigger and conversion complete interrupt
	ADCSRB |= (1<<ADTS1) | (1<<ADTS0);		//enable compare match
	
	//Global interrupt enable
	sei();
	
    while (1) 
    {
    }
}

