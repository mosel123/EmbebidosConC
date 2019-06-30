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
#use fast_io(e)

void main(void)
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   
   while(TRUE)
   {  
      for(long long i=3; i>=1; i*=4)
      {
         output_c(i);
         output_d(i >> 8);
         output_b(i >> 16);
         delay_ms(200);
      }
   }
}
