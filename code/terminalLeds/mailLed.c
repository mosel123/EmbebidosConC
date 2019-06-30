//Secuencia de leds activada desde la consola//
#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>

#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#define debugSerial

#ifdef debugSerial
   #define TX_232        PIN_C6
   #define RX_232        PIN_C7
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif 

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

#define verdadero 0x01
#define falso 0x00
#define maxBffSize 0x1E

char bandera;
char banderaEnter;
char banderaEcho;
char buffRx[maxBffSize]={};

float entero;
int indexBff = 0;
long sumaDatos = 0;

int1 banderaA = falso;
int1 banderaB = falso;
int1 banderaD = falso;

#bit flagSerial = bandera.0
#bit flagEnter = banderaEnter.0
#bit flagEcho = banderaEcho.0

#INT_RDA
void isr_rda(void) 
{
   buffRx[indexBff] = getc();
   indexBff++;
   flagSerial = verdadero;
   flagEcho = verdadero;
   if (indexBff == maxBffSize)
   {
      indexBff = 0;
   }
   if(buffRx[indexBff-1] == 0x0D)
   {
      flagEnter = verdadero;
   }
}

void main(void)
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_c(0x80);
   set_tris_d(0x00);
   
   enable_interrupts(global);   
   enable_interrupts(INT_RDA);

   
   #ifdef debugSerial
   {
      printf("Ingresa un numero: ");
      printf("\r\n");
   }
   #endif 
              
   if(flagSerial)
   {
      flagSerial = falso;
   }
   
   long contadorA = 0x01;
   long contadorB = 0x80;
   long contadorD = 0x01;
   
   while(TRUE)
   {
      //////////////////////////////////////Muestra datos
      if(flagEcho)
      {
         for(char indexWalk=0; indexWalk < indexBff; indexWalk++)
         {
            putc(buffRx[indexWalk]);
         }
         flagEcho = falso;
      }
      
      //////////////////////////////////////Conversion de datos
      for(int indexSuma = 0; indexSuma < indexBff; indexSuma++)
      {
         if(buffRx[indexSuma]==0x0D)
         {
            buffRx[indexSuma]=0x00;
         }
      }
      entero=atof(buffRx);
      sumaDatos=entero;
     
      //////////////////////////////////////Comparación
      if(flagSerial)
      {  
         if(flagEnter)
         {
            flagSerial=falso;
            flagEnter=falso;
            
            //////////////////////////////////////PuertoA
            if((sumaDatos&0x49) > 0x00)
            {
               banderaA=verdadero;
            }
            else if((sumaDatos&0x49) != 0x49)
            {
               banderaA = falso;
            }  
            if(banderaA == verdadero)
            {
               contadorA = contadorA << 1;
               if(contadorA > 128)
               {
                  contadorA = 1;
               }
            }    
            
            //////////////////////////////////////PuertoB
            if((sumaDatos&0x92) > 0x00)
            {
               banderaB=verdadero;
            }
            else if((sumaDatos&0x92) != 0x92)
            {
               banderaB = falso;
            }  
            if(banderaB == verdadero)
            {
               contadorB = contadorB >> 1;
               if(contadorB == 1)
               {
                  contadorB = 128;
               }
            }
            
            //////////////////////////////////////PuertoD
            if((sumaDatos&0x124) > 0x00)
            {
               banderaD=verdadero;
            }
            else if((sumaDatos&0x124) != 0x124)
            {
               banderaD = falso;
            }  
            if(banderaD == verdadero)
            {
               contadorD = contadorD << 1;
               if(contadorD > 128)
               {
                  contadorD = 1;
               }
            }
         }
      }
      
      //////////////////////////////////////MuestraSecuencia
      output_A(contadorA);
      output_B(contadorB);
      output_D(contadorD);
      delay_ms(100);
   }  
}


