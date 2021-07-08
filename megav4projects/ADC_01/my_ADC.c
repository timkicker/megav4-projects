/* my_ADC.c
* Created: 07.04.2021
* Benutzerbibliothek: ADC-Funktionen
*/
#include <avr/io.h>
unsigned char read_ADC8(unsigned char kanal) //ADC Funktion
//Eine ADC Wandlung durchführen ("polling")
// -> Eingabeparameter: kanal MUX-Kanal (unipolar) 0...7
// -> Rückgabeparamer: ADC-Wert (8 Bit)
 {
	 ADMUX |=(1<<kanal);            //Multiplexer Einstellung
	 ADMUX |=(1<<MUX2);
	 ADMUX |=(1<<MUX0);
	 
	 ADMUX|=1<<ADLAR;                    //Ergebnis linksbündig setzen
	 ADMUX|=1<<REFS0;                    //Referenzspannung auf VCC setzen
	 
	 
	 ADCSRA|=1<<ADPS0;                    //kadc=128
	 ADCSRA|=1<<ADPS1;                    //kadc=128
	 ADCSRA|=1<<ADPS2;                    //kadc=128
	 
	 ADCSRA&=~(1<<ADATE);                //Einzelwandlung
	 
	 ADCSRA|=1<<ADEN;                    //ADC Einschalten
	 
	 ADCSRA|=1<<ADSC;                    //Wandlung starten
	 while(ADCSRA&(1<<ADSC)){;}            //Warten bis Wandlung fertig
	 ADCSRA&=~(1<<ADEN);                //ADC ausschalten
	 
	 return ADCH; //8-Bit ADC-Wert übergeben
 }