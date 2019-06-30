#include <18f4620.h>
#include <stdio.h>
#include <stdlib.h>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG, XT
#use delay(clock=16000000)

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

#define debugSerial //Desactivada

#ifdef debugSerial
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
#endif 

void main(void)
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   
   while(TRUE)
   {
      
   }
}
