#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

//#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #use fast_io(c)
#endif

void main (void){
   setup_oscillator(OSC_16MHZ);
#ifdef __DEBUG_SERIAL__ //Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n");//Puedes usar putc o printf. Revisa la documentaci�n de CCS para ver que mas puedes hacer.
#endif
   set_tris_d(0xff);
   set_tris_c(0xff);
   set_tris_b(0xf0);
   set_tris_a(0x00);
   set_tris_e(0x0);
   
   int8 operacion = input_b();
   int8 numerouno = input_c();
   int8 numerodos = input_d();
   int16 resultado;
   if(input(PIN_B7)==1)
   {
       delay_ms(40);//evitar rebote
       resultado = numerouno+numerodos;
       output_a(resultado);
       output_b(resultado>>7);
       output_e(resultado<<10);
   }
   delay_ms(500);
}
