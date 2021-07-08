/*
 * Tasterprellen_01.c
 * Created: 24.10.2016 23:25:50
 * Author: Harry
 * Hardware: MEGACARD
 * Zweck: Detektion von Tasterereignissen
 *        OHNE Tasterentprellung
 */ 

#include <avr/io.h>
#define TASTER PA0  
                   
int main(void)
{
  DDRA=0x00;  
  PORTA=0x0F; 
  DDRC=0xFF;  
  PORTC=0x01; 
  
 	while(1) 
	{ 
		if (!(PINA & (1<<TASTER))) 
		{ 
			PORTC = (PORTC<<1) | (PORTC>>7); 
			while(!(PINA & (1<<TASTER))) {;} 
		} 
	} 
} 