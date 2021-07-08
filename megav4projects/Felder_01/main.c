/*
 * Felder_01.c
 *
 * Created: 17.03.2021 08:34:19
 * Author : - botch
 * Hardware: ATMega16
 * Use: Gelernte Felder (Arrays, Strings) andwenden und üben
 */ 

#include <avr/io.h>
#define N 4 //Feldgröße über Symbolkonstante festlegen
unsigned int tabelle[N]; //eindimensionale Feldvariable ohne Anfangswerte
unsigned char vektor[]={1,2,3,4,5}; //eindimensionale Feldvariable mit Initialisierung
unsigned char string[]="1,2,3,4,5"; //String (9 Zeichen und abschließende 0)
unsigned char matrix[2][3] = 
{ {0x11,0x22,0x33},{0x44,0x55,0x66} };
//zweidimensionale Feldvariable vereinbaren und vorbelegen
int main(void)
{ for (unsigned char i=0; i<N; i++) //Zählschleife für Index
	{ tabelle[i]=0xFFFF-i; } //Feldelement belegen
	PORTA=sizeof(tabelle); //Feldgröße ausgeben
	PORTB=tabelle[1]; //LSByte des Feldelements ausgeben
	PORTC=tabelle[1]>>8; //MSByte des Feldelements ausgeben
	vektor[0]='H'; //Zeichen 'H' = ACSII Code 0x48
	string[0]=0x7A; //ASCII Code 0x7A = Zeichen 'z'
	vektor[4]=sizeof(string); //Stringlänge=10 (einschließlich abschließende 0)
	PORTD=sizeof(matrix); //Feldgröße ausgeben
	for (unsigned char i=0;i<2;i++) //Zeilenindex inkrementieren
	{ for (unsigned char j=0;j<3;j++) //Spaltenindex inkrementieren
		{ matrix[i][j]=i+j; } //Matrixelement neu belegen
	}
	while(1) {;} //Leere Arbeitsschleife
}

