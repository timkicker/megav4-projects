/*
* TIMER0_02.c
* Created: 19.1.2021
*
* Funktion: Synchrones Blinken aller LEDs mit Blinkperiode 1sec
* Verwendung von Timer0 Overflow Interrupt und Software-Vorteiler
* Abarbeitung mittels "polling"
* Gewählte Teilungsfaktoren: kH=1 (Hardware Vorteiler)
 * kS=23437 (Software-Vorteiler)
* Hardware: MEGACARD
*/

#include <avr/io.h>
#define COUNT_MAX 23437		//System-Vorteiler initialisieren

static int count=0;			//Zählvariable initialisieren

void port_init()
{
	DDRC=0xFF;				//LED Port auf Ausgang geschaltet
	PORTC=0x00;				//alle LED ausschalten
}

void polling_init()
{
	while (!(TIFR & (1<<TOV0))){;}				//solgane keine Interrupt an Timer0 angefordert wird warten
	TIFR|=1<<TOV0;				//TOV0 in TIFR zurücksetzen
	count++;					//Zählvariable inkrementieren
	if (count>=COUNT_MAX)		//Abfrage ob Zählvariable größer gleich Software-Vorteiler
	{
		PORTC=~PORTC;			//LED-Staten aller LED's umschalten
		count=0;				//Zählvariable auf 0
	}
}

void timer_init()
{
	TCCR0|= 1<<CS00;			//Hardware-Vorteiler initialisieren kH=1
								//Systemtakt/1 eingestellt
}

int main(void)
{
	port_init();			//Zugriff auf PORT initialisierung
	timer_init();			//Zugriff auf Timer initialisierung
    /* Replace with your application code */
    while (1) 
    {
		polling_init();		//Zugriff auf Polling
    }
}

