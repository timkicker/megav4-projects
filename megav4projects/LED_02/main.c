/*
 * LED_02.c
 *
 * Created: 19.11.2020 07:51:40
 * Author : Harry
 * Einstellungen: Jumper X9 schlie?en
 * Funktion: LEDs-Status soll alle 500ms um 1 erh?ht werden 
 */ 

#define F_CPU 12000000UL //Systemtakt 12MHz (Information f?r Delayfunktion)
#include <avr/io.h>         //Systembibliothek: SFR Register und Bitdefinitionen
#include <util/delay.h>     //Systembibliothek: Delay-Funktionen

int main(void) //Modul Hauptprogramm
{
	DDRC=0xFF;  //LED-Port: Ausgang
	PORTC=0x00; //alle LEDs ausschalten (default)
	
	while(1)  //Beginn Arbeitsscheife (Endlosschleife)
	{
		PORTC++;	//LED-Status um 1 erh?hen; Alternative: PORTC=PORTC+1;
		_delay_ms(500);	//500ms warten
	} // Ende Arbeitsscheife
}

