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

//int contador = 0;

/*#int_timer0
void timer_0()
{
   set_timer0(15536);
   contador++;
}*/

void main(void)
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   
/*   setup_timer_0(rtcc_internal | rtcc_div_8);
   set_timer0(15536);
    
   enable_interrupts(int_timer0);
   enable_interrupts(global);  */
   
   long long contador = 128;
   
   while(TRUE)
   {
/*      if(contador == 2)
      {
         contador = 0;
         output_c(128);
      }
      
      if(contador == 1)
      {
         output_c(0);
      }*/
      
/*      output_c(0xCC);
      delay_ms(200);
      output_c(0x00);     
      delay_ms(100);  */
      
      if((contador & 32) == 32)
      {
         output_d(contador);
      }
      if((contador & 32) != 32)
      {
         output_d(0);
      }
      output_c(contador);
      delay_ms(300);
      contador = contador >> 1;
      if(contador == 0)
      {
         contador = 128;
      }
//      output_d(contador >> 8);
//      output_c(contador >> 16);
   }
}
