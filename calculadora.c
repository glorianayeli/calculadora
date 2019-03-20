#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b) 
#use fast_io(c) 
#use fast_io(d)    
void error();  
void main (void)
{  
     set_tris_d(0xff);
     set_tris_c(0xff);
     set_tris_b(0xf0);
     set_tris_a(0xC0);
     set_tris_e(0x0);
     int8 numero1;
     int8 numero2;
     int16 resultado=0x00;
    while(TRUE)
    {
        int16 numero1 = input_c();
        int16 numero2 = input_d();

        if(input(PIN_B7)==1)
        {
            resultado = (int16)numero1+numero2;
        } 
        else if(input(PIN_B6)==1)
        {
            resultado = (int16)numero1-numero2;
        }
        else if(input(PIN_B5)==1)
        {
            if((numero1==0xff)&&(numero2==0xff))
            {
                error();
            }
            else
               resultado=(int16)numero1*numero2;
        }
        else if(input(PIN_B4)==1)
        {
            if(numero2>0)
            {
                resultado=(int16)numero1/numero2;
            }
            else
            {
                error();
            }
        }
        output_a(resultado);
        output_b(resultado>>6);
        output_e(resultado>>10);
    }
}
void error()
{
    for(int parpadeo=1;parpadeo<=5;parpadeo++)
    {
        output_a(0b111111);
        output_b(0xf);
        output_e(0b111);
    }
}
