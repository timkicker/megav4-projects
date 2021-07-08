/**
 * \file
 *
 * \brief Empty user application template
 *
 */
/* Tasterprellen_01.c
* Created: 10.12.2020
* Author: Tim Kicker
* Hardware: MEGACARD
* Zweck: Beispielaufgabe eines Interrupts
*/


#include <asf/io.h>
#include <avr/interrupt.h>
#include <util//delay.h>

ISR(INT1_vect)
{
	PORTC++; //steigende Flanke (Prellen!)
}

void io_init()
{
	//Ports
	PORTA |= (1<<PA0); //Pullup einschalten
	DDRC=0xFF;
	
	//Interrupts
	MCUCR|=(1<<ISC11 | 1<<ISC10); //INT1 steigende Flanke
	GICR |= (1<<INT1); // INT freigegeben
}

int main (void)
{
	io_init();
	sei(); //Alle INTs freigeben
	while (1)
	{
		;
	}
}
