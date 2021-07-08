/*
 * Schleifentest_01.c
 *
 * Created: 28.9.2017
 * Author: Harry
 * Hardware: MEGACARD
 * Zweck: Test der Z?hlschleife
 */ 

#define F_CPU 12000000UL // Systemtakt auf 12MHz einstellen
#include <util/delay.h>  // Delay-Funktionen einbinden (Systembibliothek)
#include <avr/io.h>	     // I/O Definitionen einbinden (Systembibliothek)

int main(void)
{
    //PORTKONFIGURATION:
	DDRC=0xFF;  //LED-Port: Ausgang
    PORTC=0x00; //alle LEDs ausschalten (default)
    
	for(;;) //Endlosschleife
    {
        for (unsigned char i=0; i<=8; i++) //lokale Deklaration der Laufvariablen i
		{
			PORTC=i; //Ausgabe der Laufvariablen auf die LEDs (Dualcode)
			_delay_ms(500); //0,5sec warten
		} 
    } 
}