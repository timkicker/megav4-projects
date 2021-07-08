/*
 * INT1_01.c
 *
 * Created: 6.1.2021
 * Author: botch
 *
 * Funktion: Externer Interrupt 1 durch dr?cken von Taster Sx (x=0,1,2,3) ausgel?st
 *           Jedes Tasterdr?cken imkrementiert dual-code auf LEDs
 *           Achtung: Keine Tasterentprellung implementiert!
 * Hardware: MEGACARD
 *           PD3(INT1) muss extern mit PAx (Taster Sx) verbunden sein !
 */

#include <avr/io.h>               //IO-Deklarationen einbinden
#include <avr/interrupt.h>   //Interrupt Deklarationen einbinden

ISR(INT1_vect)   // *** ISR f?r INT1 ***
{
                          //LED-Status inkrementieren
}

int main(void)    // *** Hauptprogramm ***         
{
 
  while(1)  {;}        // Arbeitsschleife (keine Aktion)
} // Ende main
