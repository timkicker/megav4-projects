/*
 * INT1_02.c
 *
 * Created: 14.1.2021
 * Author: Harry
 *
 * Funktion: Externer Interrupt 1 durch dr?cken von Taster Sx (x=0,1,2,3) ausgel?st
 *           Abarbeitung mittels "polling"
 *           Jedes Tasterdr?cken imkrementiert dual-code auf LEDs
 *           Achtung: Keine Tasterentprellung implementiert!
 * Hardware: MEGACARD v4: Jumper X9 schlie?en
 *           PD3(INT1) muss extern mit PAx (Taster Sx) verbunden sein !
 */

#include <avr/io.h>          //IO-Deklarationen einbinden

int main(void)             // *** Hauptprogramm ***
{
 DDRC  = 0xFF;             // LED Port: Ausgang
 PORTC = 0x00;             // alle LEDs aus (default)
 DDRD &= ~(1<<PD3);		   // Interrupt Pin: PD3(INT1) ist Eingang (default)
 PORTD |= (1<<PD3);		   // Interrupt Pin: pullup f?r PD3 aktivieren (wegen Tasteranbindung)
 						   //                -> High-Pegel bei nicht bet?tigten Taster Sx
						   
 MCUCR |= (1<<ISC11);     // INT1 konfigurieren: fallende Flanke (Tasterdruck an Sx)
  
 while(1) //Arbeitschleife
 {
	while (!(GIFR & (1<<INTF1))) {;} //polling auf Interruptflag f?r INT1
	GIFR |= (1<<INTF1);           //Interruptflag f?r INT1 r?cksetzen 
	PORTC++;                      //LED-Status inkrementieren 
 }  //Ende while   
} // Ende main
