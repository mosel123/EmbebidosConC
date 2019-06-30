//Interrupciones timer0 (Secuencias en anillo)//
#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG, XT

#use delay(clock=16000000)

#use fast_io (a)
#use fast_io (b)
#use fast_io (c)
#use fast_io (d)

int contador1 = 0;
int contador2 = 0;
int contador3 = 0;
int contador4 = 0;

int secuencia1 = 1;
int secuencia2 = 1;
int secuencia3 = 1;
int secuencia4 = 1;

#int_timer0
void timer_0()
{
   set_timer0(15536);
   
   contador1++;
   contador2++;
   contador3++;
   contador4++;
}

void main(void)
{
    setup_oscillator(OSC_16MHZ);
    
    setup_timer_0(rtcc_internal | rtcc_div_8);
    set_timer0(15536);
    
    enable_interrupts(int_timer0);
    enable_interrupts(global);
   
    set_tris_a(0x00);
    set_tris_b(0x00);
    set_tris_c(0x00);
    set_tris_d(0x00);
    set_tris_e(0x00);
    
    while(TRUE)
    { 
    //Secuencia de 200ms
        if(contador1 == 2)
        {
            contador1 = 0;
            secuencia1 *= 2;
            if(secuencia1 == 64)
            {
                secuencia1 = 1;   
            }
        }
        output_a(secuencia1);
        
    //Secuencia de 400ms
        if(contador2 == 4)
        {
            contador2 = 0;
            secuencia2 *= 2;
            if(secuencia2 == 256)
            {
                secuencia2 = 1;   
            }
        }
        output_c(secuencia2);
        
    //Secuencia de 700ms
        if(contador3 == 7)
        {
            contador3 = 0;
            secuencia3 *= 2;
            if(secuencia3 == 256)
            {
                secuencia3 = 1;
            }
        }
        output_d(secuencia3);  
        
    //Secuencia de 1000ms
        if(contador4 == 10)
        {
            contador4 = 0;
            secuencia4 *= 2;
            if(secuencia4 == 256)
            {
                secuencia4 = 1;   
            }
        }
        output_b(secuencia4);
    }
}
