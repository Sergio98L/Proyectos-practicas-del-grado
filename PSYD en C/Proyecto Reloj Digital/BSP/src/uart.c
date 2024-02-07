#include <s3c44b0x.h>
#include <uart.h>

void uart0_init( void )
{
    UFCON0 = 0x1;
    UMCON0 = 0x0;
    ULCON0 = 0x3;
    UBRDIV0 = 34;
    UCON0 = 0x5;
}

void uart0_putchar( char ch )
{
    while( (UFSTAT0 & (1<<9)));
    UTXH0 = ch;
}

char uart0_getchar( void )
{
    while( ((UFSTAT0 & 0xF) )==0) ; // QUE PONEMOS AQUI????? ¿CÓMO SABEMOS QUE VALE 0?
    return URXH0;
}

void uart0_puts( char *s )
{
    while(*s != '\0'){
    	uart0_putchar(*s++);

    }
}

void uart0_putint( int32 i )
{
	 char buf[11 +1];  // ESTO ESTA BIEN?
	 char *p = buf + 12;
	 boolean negativo=FALSE;
	 int8 c;
	 *p = '\0';

	 if (i<0){

		 i*= -1;
		 negativo= TRUE;
	 }

	 do {

		 c=i%10;
		 *--p = '0'+ c;
		 i/=10;
	 } while(i);

	 if (negativo)
	 {
		*--p= '-';
	 }
	 uart0_puts (p);


}

void uart0_puthex( uint32 i )
{
    char buf[8 + 1];
    char *p = buf + 8;
    uint8 c;

    *p = '\0';

    do {
        c = i & 0xf;
        if( c < 10 )
            *--p = '0' + c;
        else
            *--p = 'a' + c - 10;
        i = i >> 4;
    } while( i );

    uart0_puts( p );
}

void uart0_gets( char *s )
{
    char cadena=uart0_getchar();
    while (cadena != '\n')
    {
    	*s++ = cadena;
    	cadena = uart0_getchar();

    }

    *s= '\0';
}

int32 uart0_getint( void )
{
   int32 resultado=0;
   char cadena [256], *p;
   uart0_gets(cadena);
   boolean negativo=FALSE;
   p= cadena;


	   if(*p =='-'){
		negativo = TRUE;
		p++;
	   }
	   while (*p != '\0'){
		   resultado = (*(p++)-'0')+ resultado*10;


   }
   if(negativo)
	 resultado *= -1;
   return resultado;
}

uint32 uart0_gethex( void )
{
	uint32 resultadohex=0;
	char cadena [256], *p;
	uart0_gets(cadena);
	p=cadena;
	while(*p!= '\0'){
		if (*p >= '0' && *p <= '9')
			resultadohex = (*(p++)-'0')+ resultadohex*16;
		else if(*p >= 'A' && *p <= 'F')
			resultadohex = ((*(p++)-'A')+ 10)+ resultadohex*16;
		else if (*p >= 'a' && *p <= 'f')
			resultadohex = ((*(p++)-'a')+ 10)+ resultadohex*16;


		}
	return resultadohex;
}
