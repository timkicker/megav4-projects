/*
 * Schrittmotor_01.c
 *
 * Created: 24.03.2021 13:32:04
 * Author : User
 */ 

#include <avr/io.h>
/*
 M = 48 Schritte
 n = 10 u/min
 T = M * Tp ... Umdrehungszeit Motor [s]
 f = 1/T ... Drehzahl in Hz
 n = 60 * f = 60 * 1/T = 60/(M*Tp)
 
 Tp = 60/(n*M) = 0,125
 
 #define TP_ms 60 * 1000 / n/M
 
 
 dT = ?
 fI = fsys / (kH * N) = 1/dT
 kH... Wählen = 1
 fsys = 12MHz
 N = 256 
 
 1/dT =  46875 
 dT = 21,3 us
 
 ks = TP / dT = 125000 / 21,3us = 5859
 #define ks
*/
int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

