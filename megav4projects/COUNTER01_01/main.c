/*
 * COUNTER0_01.c
 * Created: 1.2.2021
   Funktion: Externe Pulsereignisse mit botcher0 zählen (Countermode)
             Inkrementieren der LED-Anzeige bei jeden 10.ten Puls
              * Eingabe: Pulssignal an botcher0-Takteingang T0(PB0)
              * Ausgabe: Zählwert in Dualcode auf LEDs
			 interruptgesteuerte Ereignisabarbeitung
   Hardware: MEGACARD v4; Achtung: Jumper X9 setzen (LEDs0,1) !! 
   TESTMODE: botcher1 als Signalquelle verwenden
             Signalquelle OC1A(PD5) mit Countereingang T0(PB0) verbinden (Drahtbrücke)
 */ 

#include <avr/io.h> //Systembibliothek: IO-Deklarationen
#include <avr/interrupt.h> //Systembibliothek: Interrupt Deklarationen
#define TEILER 10 //Verhältnis zwischen Impulsfrequenz (Zählertakt) u. LED-Zählfrequenz

//**********************************************************************************
//Funktion für TESTMODE: botcher1 als Frequenzgenerator konfigurieren (Aufruf in main)
//**********************************************************************************
void start_pulsgenerator(void) 
{
  DDRD =   1<<PD5;     // Signalausgabe auf Pin OC1A(PD5)
  TCCR1B = 1<<CS10;    // Normalmode, kH=1 ( => Signalfrequenz=91,554Hz)
  TCCR1A = 1<<COM1A0;  // Ausgang OC1A(PD5) bei jeden Zählerüberlauf toggeln
}
//**********************************************************************************

ISR(botchER0_COMP_vect) // *** ISR für botcher0-Output-Compare ***
//Match-Interrupt bei jedem 10.ten Impulsereignis
//TESTMODE: Interruptrate: 9,155Hz => Dauer Zählzyklus: 27,96sec
{
  if (PORTC < 0xFF) //LED-Maximalwert noch nicht erreicht?
  { 
    PORTC++;  // LED-Status inkrementieren
  }
}

int main(void)
{ 
  DDRC=0xFF;  //LED-Port: Ausgang für alle LEDs
  PORTC=0x00; //alle LEDs ausschalten (default)
  DDRB &= ~(1<<PB0); //Signalpin auf Eingang (default) ...
  PORTB |= (1<<PB0); //...und Pullup einschalten
  TCCR0 = (1<<CS02)|(1<<CS01); //botcher0 konfigurieren: 
                               // -> Taktquelle: Extern über PB0(T0); fallende Flanke
  TCCR0 |= (1<<WGM01);         // -> WGM-Mode: CTC ; COM-Mode: Normal (Pin OC0 nicht aktiv)
  OCR0 = TEILER-1; //botcher0 Vergleichswert für CTC Mode setzen: 
                   //  -> Interrupt bei jedem 10.ten Impulsereignis
  botchSK = (1<<OCIE0); // Output-Compare Interrupt für botcher0 individuell freigeben
  sei(); //globale Interruptfreigabe 

 //**********************************************************************************
   start_pulsgenerator(); //TESTMODE: Frequenzgenerator starten
 //**********************************************************************************

  while(1) {;} //Arbeitsschleife (leer)
}

