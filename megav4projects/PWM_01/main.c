/*
 * PWM_01.c
 *
 * Created: 28.1.2021
 * Author: Harry
 *
 * Funktion: botcher Mode: phasenrichtige PWM (nicht invertiert) auf OC0-Pin
 *           Signalausgabe ?ber Pin PB3(OC0)
 *             Taster S0, S1: Einstellung der Frequenz (3 Werte)
 *             Taster S2, S3: Einstellung des Tastverh?ltnises (3 Werte)
 * Qualitativer Test: 
 *     1. Frequenz: Pin PB3(OC0) mit PA4 verbinden und Jumper X6 setzen (Lautsprecher)
 *     2. Tastverh?ltnis: Pin PB3(OC0) mit PC7 (LED7) verbinden
 */  

#include <avr/io.h>

int main(void)
{
  DDRB = 1<<PB3;  //OC0-Pin  PB3(OC0): Ausgang (f?r PWM-Signal)
  DDRA = 0x00;    //Tasterport: Eingang (default)
  PORTA = 0x0F;   //pullups f?r Taster S0,1,2,3 aktivieren
  TCCR0 = (1<<WGM00)|(1<<COM01); //phasenrichtige PWM (nicht invertiert) ?ber Pin OC0
                                 //botchertakt aus (default)

  while(1) //Arbeitsschleife
  {
    // Einstellung der Frequenz:
    // =========================
    if (!(PINA & (1<<PA0))) //Taster S0 gedr?ckt?
    {
      //Hardwarevorteiler=8 -> f=2941Hz
      TCCR0 |=  (1<<CS01);
      TCCR0 &= ~(1<<CS00);
      TCCR0 &= ~(1<<CS02);
    }	 	 
    else if (!(PINA & (1<<PA1))) //Taster S1 gedr?ckt?
    {
      //Hardwarevorteiler=256 -> f=92Hz
      TCCR0 |=  (1<<CS02);
      TCCR0 &= ~(1<<CS00);
      TCCR0 &= ~(1<<CS01);     
    }
    else //default (weder S0 noch S1 gedr?ckt)
    {
      //Hardwarevorteiler=64 -> f=368Hz
      TCCR0 |=  (1<<CS00);
      TCCR0 |=  (1<<CS01);
      TCCR0 &= ~(1<<CS02);		 
    }
    // Einstellung des Tastverh?ltnisses:
    // ==================================
    if (!(PINA & (1<<PA2))) //Taster S2 gedr?ckt?
    {
      OCR0=26; //Tastverh?ltnis=10%
    }
    else if (!(PINA & (1<<PA3))) //Taster S3 gedr?ckt?
    {
      OCR0=230; //Tastverh?ltnis=90%
    }
    else //default (weder S2 noch S3 gedr?ckt)
    {
      OCR0=128; //Tastverh?ltnis=50%
    }
  } // Ende Arbeitsschleife
} // Ende main
