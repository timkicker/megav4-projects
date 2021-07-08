/*
 * Tasterprellen_02.c
 *
 * Created: 27.9.2017
 * Author: botch
 * Hardware: MEGACARD
 * Zweck: Detektion von Tasterereignissen
 *        MIT softwarem??iger Tasterentprellung; Standardvariante
 */

#define F_CPU 12000000UL  //Systemtakt 12MHz
#include <util/delay.h>   //Systembibliothek f?r Delay-Funktionen
#include <avr/io.h>
#define TASTER PA0 //verwendeten Taster definieren:
                   //PA0 f?r S0, PA1 f?r S1, PA2 f?r S2, PA3 f?r S3
#define T_PRELL_MS 20 //Entprellzeit f?r Taster in ms

int main(void) //Beginn Hauptprogramm
{ //Konfiguration der I/O-Ports:
	DDRA=0x00;  //Tasterport: Eingang (Default)
	PORTA=0x0F; //Pullups f?r Taster S0,1,2,3 aktivieren
	DDRC=0xFF;  //LED-Port: Ausgang
	PORTC=0x01; //LED0 ein, LED1...7 aus

	while(1)  //Beginn Arbeitsschleife
	{ 
	  if (!(PINA & (1<<TASTER))) //Wenn Taster Sx gedr?ckt
	  { 
	    PORTC = (PORTC<<1) | (PORTC>>7); //LED Status um 1 Bit links rotieren
		_delay_ms(T_PRELL_MS);  //Entprellung f?r Tasterschlie?en
		while(!(PINA & (1<<TASTER))) {;} //warten solange Taster gedr?ckt
		_delay_ms(T_PRELL_MS);  //Entprellung f?r Taster?ffnen
	  } //Ende if
	} //Ende Arbeitsschleife
} //Ende Hauptprogramm