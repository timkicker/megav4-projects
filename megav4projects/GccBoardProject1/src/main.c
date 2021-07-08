/*
 * Bitoperationen.c
 * Created: 26.9.2017
 * Author: Harry
 * Hardware: - Simulator
 * Zweck: Verwendung des Simulators zur Programmanalyse
 * Einstellungen: Unter Project->Properties - Opbotchization "None (-O0)"
 *                Im Solution Explorer mit rechter Maustaste auf Projekt: "Set as StartUp Project"
 */ 

#include <avr/io.h> //I/O-Systembibliothek einbinden

volatile unsigned char x,y; //globale Variablen; Speicherklasse "volatile"
volatile signed char z=-10; //...(in SRAM angelegt ; Variablen vom Compiler nicht wegopbotchierbar)
volatile unsigned int neu =1000;
                          
int main(void) {
    // Vorbelegung der Variablenwerte (Defaultwerte=0)
	DDRA = 0xF0; //Datenrichtungs-Register für PortA (SFR)
	x=0xAB; //SRAM Speicherzelle //1010 1011    32 + 11 + 128 = 139 + 32 = 171
	y=0x01; 
	
	while(1) //Arbeitsschleife
	{ 
      DDRA ^= 0xff;   // 1-komplement (Alle Datenrichtungen von PortA umkehren)
	  x ^= 0xff;	  // 1-komplement (bitweises invertieren)
	  y <<= 2;		  // 2 bit logisch nach links schieben
	  z >>= 1;        // 1 bit arithmetisch nach rechts schieben
	  neu += 2;
	} 
}