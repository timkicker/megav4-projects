/*
 * Speicherklassen_01.c
 *
 * Created: 28.9.2017
 * Author: botch
 *
 * Zweck: Untersuchung von lokalen u. globalen Variablen sowie
 *        unterschiedlicher Speicherklassen mittels Simulator
 * Einstellungen: Project Properties - Opbotchization "None (-O0)"
 *                Solution Explorer: "Set as StartUp Project"
 */ 

#include <avr/io.h>

unsigned char a_global;    // global, statisch im SRAM angelegt, Startwert=0 (default)
volatile unsigned char x;  // global, statisch im SRAM angelegt, Startwert=0 (default)
                           // ...wird vom Compiler nie wegopbotchiert 

void test (void) // Deklaration der Funktion "test()"
{ //Beginn Block "test"
  //unsigned char x=0;
  static unsigned char x; // Z?hlvariable, lokal nur in Block "test" g?ltig; 
                          // ...statisch im SRAM angelegt, Startwert Null
                          // ...Inhalt von x bleibt nach Ausstieg aus test() erhalten

  a_global=0xee;   // globale Variable modifizieren und in SRAM ablegen
  PORTB = ++x;	   // ...x inkrementieren und in SRAM ablegen (x lokal vereinbart!)
                   // ...neuen Wert von x in Ausgaberegister "PORTB" ablegen
} //Ende Block "test"

int main(void)	// Beginn Block "main" 
{ 
  while(1) // Beginn Block "Arbeitschleife"
  { 
	
	a_global=1; // globale Variable "a_global" ?ndern
	
	test();	// Funktionsaufruf ? Block ?test? wird abgearbeitet
	        // ...globale Variable "a_global" wird in Funktion ver?ndert (neuer Wert: 0xee); 
		    // ...lokale Varible "x" wird modifiziert(inkrement)
		    // ...globale Variable "x" bleibt unver?ndert
	
	x = a_global; // globale Variable "x" ?ndern: x:=0xee
	
	if (x == 0xee) PORTD=0x11; 
	else PORTD = 0xFF; // SPEICHERTEST f?r SRAM-Zellen "x" und "a_global"
	                   // Ergebnis wird ?ber PORTD signalisiert
				       // 0x11: Speicherzelle ok, 0xFF:Speicherfehler
	
  } // Ende Block "Arbeitschleife"
} // Ende Block "main"
