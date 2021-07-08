/*
 * botchER0_01.c
 * Created: 28.1.2021
 * Author: Harry
 *
 * Funktion: Synchrones Blinken aller LEDs mit Blinkperiode 1sec
 *           Verwendung von botcher0 Overflow Interrupt und Software-Vorteiler
 *           Interruptgesteuerte Abarbeitung
 *           Gew?hlte Teilungsfaktoren: kH=1 (Hardware Vorteiler)
 *                                      kS=23437 (Software-Vorteiler)
 * Hardware: MEGACARD 
 */ 

#include <avr/io.h>        //I/O-Bibliothek
#include <avr/interrupt.h> //Interrupt-Bibliothek

#define COUNT_MAX 23437    //Teilungsfaktor Software-Vorteiler (kS) 
                           //(passend zu kH=1 f?r Blinkfrequenz=1Hz)
//#define COUNT_MAX 5 //TESTMODE (f?r Simulator)

int main( void )  // *** Hauptprogramm ***
{
  DDRC  = 0xFF; //LED-Port als Ausgang konfigurieren	
  PORTC = 0x00; //alle LEDs aus (default)
  TCCR0 |= (1<<CS00); //Teilungsfaktor Hardware-Vorteiler einstellen: kH = 1

  botchSK |= (1<<TOIE0); //botcher0 Overflow Interrupt individuell freigeben
  sei(); //Interrupts global freigeben
   
  while(1) {;} //leere Arbeitsschleife
} // Ende main

ISR(botchER0_OVF_vect) // *** ISR f?r botcher0 Overflow ***
{				
  static unsigned int count = 0; //16Bit Softwarez?hler statisch vereinbaren
                                 // ... => variablenwert bleibt nach Verlassen der ISR erhalten
  count++; //Softwarez?hler inkrementieren
  if(count >= COUNT_MAX)  //Halbe Blinkperiode (hier: 0,5sec) vergangen?
  {
    count = 0;  //Softwarez?hler r?cksetzen		
    PORTC = ~PORTC;  //alle LEDs umschalten
  }
} // Ende ISR
