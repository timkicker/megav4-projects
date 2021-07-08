/*
 * LED_01.c
 *
 * Created: 29.11.2018
 * Author : Harry
 * Hardware: MEGACARD
 * Einstellungen: Jumper X9 schlie?en
 * Funktion: Die LEDs sollen im Rhythmus von 200ms umgeschaltet werden
 * Modifikation: alle LEDs gleichzeitig alle 100ms umschalten
 */

 //#define F_CPU 12000000UL //Systemtakt 12MHz (Information f?r Delayfunktion)
				//hier auskommentiert, da bereits in Project-Properties definiert
 #include <avr/io.h>         //Systembibliothek: SFR Register und Bitdefinitionen
 #include <util/delay.h>     //Systembibliothek: Delay-Funktionen

 int main(void) //Modul Hauptprogramm
 {
	 DDRC=0xFF;  //LED-Port: Ausgang
	 PORTC=0x55; //LEDs 0,2,4,6 einschalten 0101 0101
	 //PORTC=0x00; //Modifikation: alle LEDs ausschalten (default)
	 
	 while(1)  //Beginn Arbeitsscheife (Endlosschleife)
	 {
		 PORTC = ~PORTC;	//alle LEDs umschalten
		 _delay_ms(200);	//200ms warten
         //_delay_ms(100);	////Modifikation: 100ms warten
	 } // Ende Arbeitsscheife
 }

