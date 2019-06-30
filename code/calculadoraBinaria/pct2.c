//Calculadora b�sica de 8x8//
#include <18F4620.h>
#use delay(clock=16000000)

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOMCLR, STVREN, NOLVP, NODEBUG, NOPBADEN

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

#define opSuma 0x01
#define opResta 0x02
#define opProducto 0X03
#define opDivision 0X04

int opcion=0x00;

void errorSecuencia();
int evalua(int opcion);

void main (void)
{
    setup_oscillator(OSC_16MHZ);
   
    set_tris_a(0xc0);
    set_tris_b(0xF0);
    set_tris_c(0xFF);
    set_tris_d(0xFF);
    set_tris_e(0x08);
   
    signed long resultado = 0x00;
   
    while(TRUE)
    {       
        int operacion = evalua(opcion);
        switch(operacion)
        {
            case opSuma:
                resultado = (long)input_c() + (long)input_d();
                opcion = 0x00;
                break;
            case opResta:
                resultado = (long)input_c() - (long)input_d();
                opcion = 0x00;
                break; 
            case opProducto: 
                resultado = (long)input_c() * (long)input_d();
                opcion = 0x00;
                break;
            case opDivision:
                if((long)input_d() == 0)
                {
                    errorSecuencia();
                    opcion = 0x00;
                    break;
                }
                else
                {
                    resultado = (long)input_c() / (long)input_d();
                    opcion = 0x00;
                    break;
                }
        }
      
    output_a(resultado);
    output_b(resultado >> 6 );
    output_e(resultado >> 10);
    }
}   

int evalua(int opcion)
{
    if(input(PIN_B4) == FALSE)
    {
        opcion = opSuma;
    }
    else if (input(PIN_B5) == FALSE)
    {
        opcion = opResta;
    }
    else if (input(PIN_B6) == FALSE)
    {
        opcion = opProducto;
    } 
    else if (input(PIN_B7) == FALSE)
    {
        opcion = opDivision;
    }
    
    return opcion;
}

void errorSecuencia()
{
    for(int i=0; i < 3; i++)
    {
        output_a(0xFF);
        output_b(0xFF);
        output_e(0xFF);
        delay_ms(200);
        output_a(0x00);
        output_b(0x00);
        output_e(0x00);
        delay_ms(200);
    }
}