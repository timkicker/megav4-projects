/*
 * INT1_01.c
 *
 * Created: 14.1.2021
 * Author: botch
 *
 * Funktion: Externer Interrupt 1 durch dr?cken von Taster Sx (x=0,1,2,3) ausgel?st
 *           interruptgesteuerte Abarbeitung
 *           Jedes Tasterdr?cken imkrementiert dual-code auf LEDs
 *           Achtung: Keine Tasterentprellung implementiert!
 * Hardware: MEGACARD v4: Jumper X9 schlie?en
 *           PD3(INT1) extern mit PAx (Taster Sx) verbinden !
 */

#include <avr/io.h>          //IO-Deklarationen einbinden
#include <avr/interrupt.h>   //Interrupt Deklarationen

ISR(INT1_vect)              // *** ISR f?r INT1 ***
{
 PORTC++;                   //LED-Status inkrementieren
}

int main(void)             // *** Hauptprogramm ***
{
 DDRC  = 0xFF;             // LED Port: Ausgang
 PORTC = 0x00;             // alle LEDs aus (default)
 DDRD &= ~(1<<PD3);		   // Interrupt Pin: PD3(INT1) ist Eingang (default)
 PORTD |= (1<<PD3);		   // Interrupt Pin: pullup f?r PD3 aktivieren (wegen Tasteranbindung)
						   //                -> High-Pegel bei nicht bet?tigten Taster Sx
						   
 MCUCR |= (1<<ISC11);    // INT1 konfigurieren: fallende Flanke (Tasterdruck an Sx)
 GICR |= (1<<INT1);      // INT1 individuell freigeben
 sei();                  // globale Interruptfreigabe
 
 while(1)  {;}              // Arbeitsschleife (keine Aktion)
} // Ende Hauptprogramm
