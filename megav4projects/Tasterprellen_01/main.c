/*
 * Tasterprellen_01.c
 * Created: 28.9.2017
 * Author: Harry
 * Hardware: MEGACARD
 * Zweck: Detektion von Tasterereignissen
 *        OHNE Tasterentprellung
 */ 

#include <avr/io.h>
#define TASTER PA0 //verwendeten Taster definieren:
//PA0 f?r S0, PA1 f?r S1, PA2 f?r S2, PA3 f?r S3

int main(void) //Beginn Hauptprogramm
{ //Konfiguration der I/O-Pins:
	DDRA=0x00;  //Tasterport: Eingang (default)
	PORTA=0x0F; //Pullups f?r Taster S0,1,2,3 aktivieren
	DDRC=0xFF;  //LED-Port: Ausgang
	PORTC=0x01; //LED0 ein, LED1...7 aus
	
	while(1) //Beginn Arbeitsschleife
	{ if (!(PINA & (1<<TASTER)))    //Wenn Taster Sx gedr?ckt
		{ PORTC = (PORTC<<1) | (PORTC>>7); //LED Status um 1 Bit links rotieren
			while(!(PINA & (1<<TASTER))) {;} //warten solange Taster gedr?ckt
		} //Ende if
	} //Ende Arbeitsschleife
} //Ende Hauptprogramm
