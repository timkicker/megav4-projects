/*
* ADC_02.c
* Created: 9.4.2019 
* Hardware: MEGACARD v4
* Zweck: Verwendung des ADC beim Atmega16
* Funktion: gemittelten Stellwinkel des MEGACARD-Potis auf LED-Port ausgeben
 interruptgesteuertes Einlesen vom ADC-Wertes
 ADC Betriebsmode: Freilaufbetrieb
 -> Eingabe: Potentiometer R20 (MEGACARD) ?ber Pin PA5
 -> Berechnung des Poti-Stellwinkels aus ADC-Wert 
 -> Ausgabe: 8-Bit Mittelwert auf PortC (LED7:0)
 * User: botch -
*/

#include <avr/io.h> 
#include <avr/interrupt.h> 
#define PHI_MAX 210 //maximaler Poti-Stellwinkel 
#define Z_MAX 255 //maximaler ADC-Wert (8Bit Mode)
volatile char phi_alt=0;			//statische 8Bit Variable definieren
unsigned char phi=0;			//aktueller Poti-Stellwinkel definieren
unsigned char phi_min=0;
unsigned char Z=0;				//ADC-Wert konfigurieren
unsigned char phi_mittel=0;		//Gleitender Mittelwert konfigurieren



ISR(ADC_vect) 
{

	
	Z=ADCH;							//ADC-Wert einlesen	
	phi=PHI_MAX*Z/(Z_MAX+1);		//POTI-Stellwinkel berechnen
	phi_mittel=(phi+phi_alt)/2;		//Gleit.Mittelwert berechnen	
						//Auf LED's ausgeben
	phi_alt=phi;					//Stellw. (alt) aktualisieren
	if(!(PINA & (1<<PA0) ))
	{
		PORTC=phi_min;
	}
	else if(!(PINA & (1<<PA1)))
	{
		PORTC = PHI_MAX;
	}
	else
	{
		PORTC=phi_mittel;	
	}
	
	phi_mittel = mittelBerechnen(phi);
		
	
}

void port_init()
{
	DDRC=0xFF;			//LED auf Ausgang 
	PORTC=0x00;			//Alle LED's ausschalten
	DDRA&= ~(1<<PA5);	//PA5,PA0,PA1 auf Eingang schalten
	DDRA&= ~(1<<PA0) | (1<<PA1);
	PORTA|= (1<<PA1) | (1<<PA0);
}

void ADC_init()
{
	ADMUX|=(1<<MUX0)|(1<<MUX2);		//Multiplexer Einstellung auf Kanal ADC5
	ADMUX|=1<<ADLAR;				//Linksbuendig
	ADMUX|=1<<REFS0;				//Referenzspannung auf VCC 
	
	ADCSRA|=1<<ADPS1;				//kadc=64
	ADCSRA|=1<<ADPS2;				
	
	ADCSRA|=1<<ADEN;				//ADC Einschalten
	
	ADCSRA|=(1<<ADATE);				//Freilaufbetrieb 

	ADCSRA|=(1<<ADIE);				//ADC-Interrupt freigeben
	ADCSRA|=1<<ADSC;				//Wandlung starten
}

int main(void)
{
	port_init();			//Funtkion PORT-Initialisierung
	ADC_init();				//Funtkion ADC Konfiguration
	sei();					//Interrupt Global freigeben
    while (1) { }			//Leere Arbeitsschleife
}

unsigned char mittelBerechnen(unsigned char phiNew)
{
	#define N 5
	static unsigned char mittelAlle[N];
	static unsigned char mittelFuenf = 0;
	static unsigned char i = 0;
		
	mittelFuenf[i] = phiNew;
	i++;
	mittelFuenf = 0;
	for ( int x = 0; x < N ; x++)
	{
		mittelFuenf = mittelFuenf + mittelAlle[x];
	}
	mittelFuenf = (mittelFuenf / N);
	if (i > (N-1)) {i=0;}
	return mittelFuenf;
}

