/*
 * LAB_8.c
 *
 * Created: 12/1/2022 5:20:27 PM
 * Author : Brent Son
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>

uint8_t EEMEM data = 0;

void LEDOFF()
{
	PORTB &= ~(1<<PORTB5);
}

void LEDON()
{
	PORTB |= (1<<PORTB5);
}

void LED_Init()
{
	//Set data direction to output
	DDRB |= (1<<5);
	
	//Set LED to off
	PORTB &= ~(1<<5);
	
}

void Timer_Init()
{
	uint8_t scale;
	
	scale = eeprom_read_byte(&data);
	
	//Timer Mode CTC Mode
	TCCR0A |= (1<<WGM01);
	
	//Period is 5ms => OCRA: 156
	//Prescale: 256
	TCCR0B |= (1<<CS02);
	
	//Set OCR0A
	OCR0A = 156;
	
	//Set OCR0B
	OCR0B = (scale * 0.1) * OCR0A;
	
	//Interrupt Enable
	TIMSK0 |= (1<<OCIE0A) | (1<<OCIE0B);
}

uint8_t Update_Val()
{
	uint8_t new_val = data;	
	
	if(new_val < 10)
		new_val += 1;
	else if (new_val >= 10)
		new_val = 0;
		
	return new_val;
}

void EEPROM_Update()
{
	uint8_t update_val;
	update_val = Update_Val();
	
	eeprom_write_byte(&data, update_val);
}

int main(void)
{
	LED_Init();    
	Timer_Init();
	EEPROM_Update();
	
    while (1) 
    {
		LEDON();
		while(!(TIFR0 & (1<<OCF0B))); 
		TIFR0 |= (1<<OCF0B);
		
		LEDOFF();
		while(!(TIFR0 & (1<<OCF0A)));
		TIFR0 |= (1<OCF0A);
		
	}
}

