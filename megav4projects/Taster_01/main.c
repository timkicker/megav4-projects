/*
 * Taster_01.c
 *
 * Created: 6.12.2018
 * Author: Botch
 * Hardware: MEGACARD
 * Einstellungen: Jumper X9 geschlossen
 * Funktion: LED0 einschalten, falls S0 bet?tigt
 *           LED0 ausschalten, falls S1 bet?tigt
 */ 

#include <avr/io.h>

int main(void)
{
    DDRA=0x00;	// Taster-Port = Eingang (Default)
	PORTA=0x03;	// Pullups aktivieren f?r Taster S0, S1
	DDRC=0x01;	// I/O-Pin f?r LED0 = Ausgang
	PORTC=0x00;	// LED0 aus (Default)
	
	while(1) // Arbeitsschleife
    {
     if (!(PINA & 0x01)) {PORTC=0x01;} //LED0 ein wenn Taster S0 gedr?ckt
	 if (!(PINA & 0x02)) {PORTC=0x00;} //LED0 aus wenn Taster S1 gedr?ckt
    }
}
