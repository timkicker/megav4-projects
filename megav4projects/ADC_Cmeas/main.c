/*
 * ADC_Cmeas.c
 *
 * Created: 6/23/2021 8:29:36 AM
 * Author : - botch
 * Hardware ATMega16
 * Usage: Messung einer Kapazität mittels des ADCs der Megacard16
 */ 

#include <avr/io.h>
#include <avr/interrupt.h> //Interrupt Bibliothek einbinden

ISR(ADC_vect) //ISR für ADC Wandlung
{
	unsigned static int Z; //Variable Z initialisieren
	Z = (ADLAR / 1024)*2.56; //Z berechnen 
	if (Z<=10) //Wenn Z kleiner als 10 (U gleich 0)
		{
			PORTB |= (1<<PB3); 
			PORTC = (1<<PC1); 
		} //PB3 auf High Pegel und LED1 ein
		
	if (Z>=(0.63*2.56))  // Wenn Tau erreicht (0.63*Uref)
		{
			PORTC = 0xFF;
			PORTB &= ~(1<<PB3); 
		}	//Alle LEDs ein
}

int main(void)
{
    DDRC=0xFF; //LEDs auf ausgang
	DDRB=(1<<PB3); //PB3 für Pegel (H,L)
	PORTC=0x00; //LEDs aus 
	
	ADMUX |= (1<<REFS0) & (1<<MUX0) & (1<<MUX1) & (1<<MUX2);
		//Referenzsspannung von AVcc und Kanalauswahl auf PA7
	
	ADCSRA |= (1<<ADPS0) & (1<<ADPS1) & (1<<ADPS2);
		//Wandlungsteiler 128
		
	ADCSRA |= (1<<ADATE); //Dauerwandlung	
	ADCSRA |= (1<<ADEN); //ADC Starten	
	ADCSRA |= (1<<ADIF); //Interrupt lokal freigeben
	sei(); //Interrupt global freigeben
	ADCSRA |= (1<<ADSC); //Wandlung Starten
    while (1) {;} ´//Leere Arbeitsschleife
}

