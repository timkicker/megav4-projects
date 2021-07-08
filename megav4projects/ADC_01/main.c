/* ADC_01.c
* Created: 8.4.2019
* Hardware: MEGACARD v4
* Zweck: Verwendung des ADC beim Atmega16
* Implementation einer Benutzbibiothek für ADC
* Funktion: digitalisierten Spannungswert auf LED-Port ausgeben
Einlesen vom ADC mittels "polling"
ADC Betriebsmode: Einzelwandlung
-> Eingabe: Potentiometer R20 (MEGACARD) über Pin PA5
-> Ausgabe: 8-Bit Digitalwert auf PortC (LED7:0)
*/
#include <avr/io.h> //I/O-Systembibliothek einbinden
//Befindet sich im Standard-Include-Verzeichnis
#include "my_ADC.h" //ADC Benutzerbibilothek einbinden;
//muss sich im Projektverzeichnis befinden

int main(void)
{
	DDRC=0xFF; //LED auf ausgang
	PORTC=0x00; //LED Ausschalten
	
	DDRA &= ~(1<<PA5); //PA5 als eingang
	
	ADMUX|=1<<REFS0;  //Referenzspannung auf VCC 5V setzen
	
    /* Replace with your application code */
    while (1) 
    {
		PORTC = read_ADC8(PA5); //Wert an Pin messen und auf LED schreiben
    }
}

