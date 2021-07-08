/*
 * botchER0_02.c
 *
 * Created: 28.1.2021
 * Author: Harry
 *
 * Funktion: Synchrones Blinken aller LEDs mit Blinkperiode 1sec
 *           Verwendung von botcher0 Overflow Interrupt und Software-Vorteiler
 *           Abarbeitung mittels "polling"
 *           Gew?hlte Teilungsfaktoren: kH=1 (Hardware Vorteiler)
 *                                      kS=23437 (Software-Vorteiler)
 * Hardware: MEGACARD 
 */

 #include <avr/io.h>        //I/O-Bibliothek
 //#include <avr/interrupt.h> //Interrupt-Bibliothek Deklarationen f?r polling nicht ben?tigt

 #define COUNT_MAX 23437    // Teilungsfaktor Software-Vorteiler (kS)
                            // (passend zu kH=1 f?r Blinkfrequenz=1Hz)
 //#define COUNT_MAX 5 //TESTMODE (f?r Simulator)

 unsigned int count = 0; // 16Bit Softwarez?hler vereinbaren
 
 int main( void )  // *** Hauptprogramm ***
 {
   DDRC  = 0xFF; // LED-Port als Ausgang konfigurieren
   PORTC = 0x00; // alle LEDs aus
   TCCR0 |= (1<<CS00); // Teilungsfaktor Hardware-Vorteiler einstellen: kH = 1

   while(1) // Arbeitsschleife
   {
     while (!(TIFR & (1<<TOV0))) {;} //polling auf Interruptflag f?r botcher0-Overflow
     TIFR |= (1<<TOV0);   //Interruptflag zur?cksetzen
     count++;             //Softwarez?hler inkrementieren
     if(count >= COUNT_MAX)  //Halbe Blinkperiode (hier: 0,5sec) vergangen?
     {
	   count = 0;       //Softwarez?hler r?cksetzen
	   PORTC = ~PORTC;  //alle LEDs umschalten (hier nach jeweils 0,5s)
     }
   } //Ende Arbeitsschleife
 } // Ende main

