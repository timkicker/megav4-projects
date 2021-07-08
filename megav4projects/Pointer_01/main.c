#include <avr/io.h>
volatile unsigned char *px, x; // Pointer px und Variable x vereinbaren
volatile unsigned int *ptri; // Pointer für direkte Adressierung vereinbaren
volatile unsigned char *ptr; // Pointer für Zugriff auf SFR vereinbaren
int main(void)
{
	DDRC=0xFF; // PortC als Ausgang konfigurieren
	ptri = 0x0070; // Pointer initialisieren (Inhalt = Adresse 0x70 im SRAM)
	// -> direkte Adressierung - MIT VORSICHT VERWENDEN!!
	px = &x; // Pointer px auf variable x setzen (REFERENZIERUNG)
	// -> px referenziert auf Adresse der Variable x
	// oder einfacher: px "zeigt" auf x
	*px = 0xBA; // Wert von x über Pointer px ändern (DEREFERENZIERUNG)
	PORTC = *px; // Wert von x auf PortC ausgeben (DEREFERENZIERUNG)
	ptr = &PORTC; // Pointer auf Portvariable (SFR) setzen
	*ptr = 0xCC; // Ausgabe des Wertes 0xCC auf PortC
	while(1) //Arbeitsschleife
	{
		(*ptr)++; //Referenzierte Variable (hier: PORTC) inkrementieren
		*ptri=0xFEDC; // SRAM Integer-Speicherzelle (2Byte!) mit Wert 0xFEDC beschreiben
		ptri++; // Pointer auf nächste Integer-Speicherstelle setzen
		// (-> Adresse wird um 2 erhöht!!)
	}
}