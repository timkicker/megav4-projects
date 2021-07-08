/*
 * Makro_01.c
 *
 * Created: 08.04.2021 08:31:18
 * Author : - botch
 * Hardware: AtMega16
 * Mithilfe 2er Makros soll einmail ein Bit in einer Variable gesetzt werden und im 2. eines gelöscht.
 */ 

#include <avr/io.h>
#define Set_Bit(var,bit) (var |= (1<<bit));   // Erstellung des Makros zum Setzen des Bit "bit" in der Variable "var"
#define Clear_Bit(var,bit) (var &= ~(1<<bit));// Erstellung des Makros zum Löschen des Bit "bit" in der Variable "var"


int main(void)
{
    /* Replace with your application code */
	unsigned int testInt = 0xF0F0;  //Variable zum Testen wird initialisiert
	unsigned char testBit = 8; //Bit zum Testen wird initialisiert
	unsigned char testBit2 = 7;
    while (1) 
    {
		Set_Bit(testInt,testBit);  //Bit wird durch Makro gesetzt
		Clear_Bit(testInt,testBit2);//Bit wird durch Makro gelöscht
    }
}

