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

#define debugSerial

#ifdef debugSerial
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
#endif 

#define verdadero 0x01
#define falso 0x00
#define maxBffSize 0x1E
#define inicio 0

char bandera;
char banderaPrintf;
char banderaEnter;
char buffRx[maxBffSize];
int indexBff = 0;

#bit flagSerial = bandera.0
#bit flagImprime = banderaPrintf.0
#bit flagEnter = banderaEnter.0

#INT_RDA
void isr_rda(void) 
{
   buffRx[indexBff] = getc();
   indexBff++;
   flagSerial = verdadero;
   if (indexBff == maxBffSize)
   {
      indexBff = 0;
   }
   if(buffRx[inicio] == 0x3C && buffRx[indexBff-2] == 0x3E)
   {
      flagImprime = verdadero;
   }
   if(buffRx[indexBff-1] == 0x0D)
   {
      flagEnter = verdadero;
   }
}

void main(void)
{
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x80);
   set_tris_d(0x00);
   
   printf("Ingresa un palabra... ");
   printf("\n \r");
   
   while(TRUE)
   {
      if(flagSerial == verdadero) 
      {
         flagSerial = falso;
         if(flagImprime == verdadero && flagEnter == verdadero)
         {
            flagImprime = falso;
            flagEnter = falso;
            for (char indexWalk = 1; indexWalk < indexBff-2; indexWalk++) 
            {
               printf("%c",buffRx[indexWalk]);
            }        
         }
      }
   }
}
