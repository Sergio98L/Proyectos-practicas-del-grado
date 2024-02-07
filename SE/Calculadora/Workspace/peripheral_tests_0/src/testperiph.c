/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */


#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xbasic_types.h"
#include "xbram.h"
#include "bram_header.h"
#include "xbasic_types.h"
#include "xgpio.h"
#include "gpio_header.h"
#include "tecladokeypad.h"
#include "pantallalcd.h"

# define CLEAR_DISPLAY_CMD 0x00000001
# define RETURN_HOME_CMD 0x00000002
# define WRITE_CMD 0x00000200
# define FIRST_ROW 0x00000080
# define SECOND_ROW 0x000000C0

#define BASE_ADDRESS_KEYPAD 0xCAE00000

void LCD_enviarCMD ( Xuint32 cmd ){
	// Comprobamos que la FIFO no esté llena
	while ( PANTALLALCD_mWriteFIFOFull(XPAR_PANTALLALCD_0_BASEADDR)){}
	// Escribimos el comando en la FIFO
	PANTALLALCD_mWriteToFIFO (XPAR_PANTALLALCD_0_BASEADDR, 0, cmd );
}

void LCD_inicializa () {
	PANTALLALCD_mResetWriteFIFO (XPAR_PANTALLALCD_0_BASEADDR);
	LCD_enviarCMD(CLEAR_DISPLAY_CMD);
	LCD_enviarCMD(RETURN_HOME_CMD); // moverse al comienzo de la pantalla LCD
	LCD_enviarCMD(WRITE_CMD); // primera escritura
}
void mostrarMensajeInicialLCD(){
	xil_printf (" Mostrar mensaje inicial\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + ':' );
	LCD_enviarCMD ( WRITE_CMD + ')' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + '1' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
}
void mostrarMensajeResultadoLCD(){
	xil_printf (" Mostrar mensaje resultado\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ':' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
}
void mostrarMensajeOperacionLCD(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
}
void mostrarMensajeOperadorLCD(char nOperador){
	xil_printf (" Mostrar mensaje operador\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'Z' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	if(nOperador == '1'){
		LCD_enviarCMD ( WRITE_CMD + '1');
	}else{
		LCD_enviarCMD ( WRITE_CMD + '2');
	}

	LCD_enviarCMD ( WRITE_CMD + 'e' );
	LCD_enviarCMD ( WRITE_CMD + 'r' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
}
int getNumber(char nOperador){ //funcion para leer tecla del keypad y convertirla a su valor en decimal

	print("---Entrando en getNumber---\n\r");
	Xuint32 value,dato,oldValue;
	int num = 0;
	mostrarMensajeOperadorLCD(nOperador);
	value = TECLADOKEYPAD_mReadReg(BASE_ADDRESS_KEYPAD,0); //se lee la tecla

	dato = (value>>28) & 0xF;//la convierto a numero o letra

	TECLADOKEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,value);
	TECLADOKEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,0);
	oldValue = dato;
	while(dato == 0){
		if(value != oldValue){
			dato = (value>>28) & 0xF;
			//xil_printf("se ha leido %01x \n\r",dato);
			oldValue = value;
		}
		value = TECLADOKEYPAD_mReadReg(BASE_ADDRESS_KEYPAD,0);
		//dato = KEYPAD_mReadReg(XPAR_KEYPAD_0_BASEADDR,0);
		TECLADOKEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,0);
	}

	switch ( dato ) {
	case 0x0:
		num = 0;
		break;
	case 0x1:
		num = 1;
		break;
	case 0x2:
		num = 2;
		break;
	case 0x3:
		num = 3;
		break;
	case 0x4:
		num = 4;
		break;
	case 0x5:
		num = 5;
		break;
	case 0x6:
		num = 6;
		break;
	case 0x7:
		num = 7;
		break;
	case 0x8:
		num = 8;
		break;
	case 0xA:
		num = 10;
		break;
	case 0x9:
		num = 9;
		break;
	case 0xB:
		num = 11;
		break;
	case 0xC:
		num = 12;
		break;
	case 0xD:
		num = 13;
		break;
	case 0xF:
		num = 15;
		break;
	case 0xE:
		num = 14;
		break;
	default:
		num = -1;
	}

	value = TECLADOKEYPAD_mReadReg(BASE_ADDRESS_KEYPAD,0);
	TECLADOKEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD,0,0);
	xil_printf("  El valor de num en getNumber es %d\n\r", num);
	return num;
}

void intToChar(int num, char* buffer, int bufferSize) {
    int i = 0;
    int temp = num;

    if (num < 0) {
        buffer[i++] = '-';
        temp = -num;
    }

    int divisor = 1;
    while (temp / divisor >= 10) {
        divisor *= 10;
    }

    while (divisor != 0) {
        buffer[i++] = '0' + temp / divisor;
        temp %= divisor;
        divisor /= 10;

        if (i >= bufferSize - 1) {
            break;  // Evitar desbordamiento del búfer
        }
    }

    buffer[i] = '\0';  // Asegurar que la cadena termina con null
}

int main ()
{


	Xuint32 baseaddr;
	print("---Test para el keypad---\n\r");
	baseaddr = BASE_ADDRESS_KEYPAD;
	Xuint32 entrada;
	Xuint32 teclaOld;
	char keypad[80];
	char caracter;
	int pos = 0;
	int salir = 0;
	int teclaPulsada = 0;
	int num1;
	int num2;
	int result;
	int sumar;

entrada = TECLADOKEYPAD_mReadReg(baseaddr, 0);
// xil_printf("Se ha leido %x del registro 0 del teclado \n\r", entrada);
/* Se escribe un 0 para borrar la �ltima tecla le�da */
TECLADOKEYPAD_mWriteReg(baseaddr, 0, 0);
/* Se guarda el �ltimo valor recibido para compararlo con el siguiente */
teclaOld = entrada;
mostrarMensajeInicialLCD();


while ((pos < 80) && !salir) {
	entrada =TECLADOKEYPAD_mReadReg(baseaddr, 0);
	/* Se escribe un 0 para borrar la �ltima tecla le�da */
	TECLADOKEYPAD_mWriteReg(baseaddr, 0 ,0);
	if (entrada != teclaOld) {
		//xil_printf("Se ha leido %x del registro 0 del teclado \n\r", entrada);
		teclaOld = entrada;
		/* Hacemos AND con el bit que marca si se ha pulsado una tecla */
		teclaPulsada = (entrada && 0x1);
		xil_printf("  El valor de teclaPulsada es %d\n\r", teclaPulsada);
	}

	if (teclaPulsada) {

		/* La tecla pulsada se recibe en los bits 27-31, as� que los desplazamos */
		caracter = (char) (entrada >> 28);
		xil_printf("  El valor de caracter es %c\n\r", caracter);
		/* Se termina cuando se pulsa la tecla F */
		salir = (caracter == 0x0F);
		xil_printf("  El valor de salir es %d\n\r", salir);
		mostrarMensajeOperacionLCD();

		if (!salir) {
			/* Si el caracter est� entre 0xA y 0xE (10 y 14), a�adimos la letra may�scula
			 * sumando 55 al valor, de modo que 65 es 'A', 66 es 'B?', etc.; si no,
			 * a�adimos 48 al valor, de modo 48 es '0', 49 es '1', etc.
			 */
			caracter = (caracter > 9) ? (0x37 + caracter) : (0x30 + caracter);
			xil_printf("Se ha pulsado el caracter %c\n\r", caracter);

			if(caracter == 'A' || caracter == 'B'){
				if(caracter == 'A'){
					sumar=0;
				}else{
					sumar=1;
				}
				num1 =0;
				num2=0;
				LCD_enviarCMD(CLEAR_DISPLAY_CMD);
				xil_printf("Entrando en A o B \n\r");
				num1 = getNumber('1');
				xil_printf("Se ha introducido el numero %d\n\r", num1);
				num2 = getNumber('2');
				xil_printf("Se ha introducido el numero %d\n\r", num2);
				result=0;
				if(sumar == 0){
					result=num1+num2;
				}else{
					result=num1-num2;
				}

				xil_printf("El resultado de la suma es %d\n\r", result);
				char buffer[20];  // Ajusta el tamaño según tus necesidades
				intToChar(result, buffer, sizeof(buffer));
				int i=0;
				LCD_enviarCMD(CLEAR_DISPLAY_CMD);
				mostrarMensajeResultadoLCD();
				 for (i=0;buffer[i] != '\0'; ++i) {
					 xil_printf("El resultado de la suma en char es %c\n\r", buffer[i]);
					 //Meto el if este para retrasar un poco la ejecucion del bucle y no se deje caracteres por imprimir
					 if(i==0){
						 LCD_enviarCMD(WRITE_CMD + ' ');
					 }
				     LCD_enviarCMD(WRITE_CMD + buffer[i]);
				 }

			}

			//LCD_enviarCMD ( WRITE_CMD + caracter );
			keypad[pos] = caracter;
			pos++;
		}
	}
}
return 0;
}

