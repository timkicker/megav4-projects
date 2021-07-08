/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <avr/io.h>
#define TASTER PA0 //Taster Auswählen

int main(void) //Beginn Hauptprogramm
{
	DDRA=0x00;
	PORTA=0x0F; // 0|1==Eingang mit Pullup
	DDRC=0xFF;
	PORTC=0x01; //LED 1 ist ein. Ausgang ohne Pull Up da 1|1;
	while (1) //Beginn Arbeitsschleife
	{
		if (!PINA & (1<<TASTER))) // wenn Taster SO gedrückt wird die 1 weggeschoben so entstehr durch die & Maske eine 0.
		// wenn aber Taster S1 gedrückt wird sind auf PINA und Taster die Gleichen Bits auf 1 geschalten=1


		PORTC =(PORTC<<1) |(PORTC>>7)    // LED werden abwechselb leutchten, da die 1 hin und her geschoben wird
		while (!(PINA & (1<<TASTER)))
		{

		}


	} //Ende Arbeitsschleife
}//Ende Hauptprogramm