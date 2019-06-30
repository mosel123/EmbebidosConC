#include <18f4620.h>
#use delay(clock=16000000)

#include <stdio.h>
#include <stdlib.h>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG, XT

#define puertoB 0x01
#define puertoC 0x02
#define puertoD 0x03

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

long contadorB = 1;
long contadorC = 128;
long contadorD = 1;

int1 banderaB=0;
int1 banderaC=0;
int1 banderaD=0;

void main(void)
{
   set_tris_a(0xFF);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   
   long puertoA = 0x00;
   //long secuencia = 0x00;
   
   while(TRUE)
   {
      //////////////////////////
      puertoA = input_A();
      //////////////////////////
      if((puertoA&0x09) > 0x00)
      {
         banderaB = 1;
      }
      else if((puertoA&0x09) != 0x09)
      {
         banderaB = 0;
      }  
      if(banderaB == 1)
      {
         contadorB = contadorB << 1;
         if(contadorB >= 128)
         {
               contadorB = 1;
         }
      }
      //////////////////////////
      if((puertoA&0x12) > 0x00)
      {
         banderaC = 1;
      }
      else if((puertoA&0x12) != 0x12)
      {
         banderaC = 0;
      }  
      if(banderaC == 1)
      {
         contadorC = contadorC >> 1;
         if(contadorC == 1)
         {
               contadorC = 128;
         }
      }
      //////////////////////////
      if((puertoA&0x34) > 0x00)
      {
         banderaD = 1;
      }
      else if((puertoA&0x34) != 0x34)
      {
         banderaD = 0;
      }  
      if(banderaD == 1)
      {
         contadorD = contadorD << 2;
         if(contadorD >= 128)
         {
               contadorD = 1;
         }
      }
      //////////////////////////
      output_B(contadorB);
      output_C(contadorC);
      output_D(contadorD);
      delay_ms(100);
      //////////////////////////
/*      if((puertoA&0x01) == 0x01 || (puertoA&0x08) == 0x08)
      {
         secuencia = puertoB;
      }
      else if((puertoA&0x02) == 0x02 || (puertoA&0x10) == 0x10)
      {
         secuencia = puertoC;
      }
      else if((puertoA&0x04) == 0x04 || (puertoA&0x20) == 0x20)
      {
         secuencia = puertoD;
      } 
      
      switch(secuencia)
      {
         case puertoB: 
            output_b(contadorB);
            delay_ms(100);
            contadorB = contadorB >> 1;
            if(contadorB > 128)
            {
               contadorB = 1;
            }
            secuencia = 0x00;
            break;
         case puertoC:
            output_c(contadorC);
            delay_ms(100);
            contadorC = contadorC >> 1;
            if(contadorC == 0)
            {
               contadorC = 128;
            }
            secuencia = 0x00;
            break;
         case puertoD:
            output_d(contadorD);
            delay_ms(100);
            contadorD = contadorD << 2;
            if(contadorD > 128)
            {
               contadorD = 1;
            }
            secuencia = 0x00;
            break;
      }*/
      
   }
}
