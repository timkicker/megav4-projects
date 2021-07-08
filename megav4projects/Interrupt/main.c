/*
 * Interrupt.c
 *
 * Created: 20/01/2021 08:02:08
 * Author : timki
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT1_vect)
{
	PORTC++; //LED Status inkrementieren	
}


int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	DDRD= (0 << PD3) // PORTD als Imput
    PORTD= (1 << PD3) 
	MCUCR = (1 << ISC11 | 1 << ISC10);
	GICR = (1 << INT1); // INT0 Enable
	
	sei();
    while (1) 
    {
    }
}

