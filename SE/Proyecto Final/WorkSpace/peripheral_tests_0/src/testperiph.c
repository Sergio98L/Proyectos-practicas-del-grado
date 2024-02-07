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
#include "motor_hw.h"
#include "ledsrgb.h"

# define CLEAR_DISPLAY_CMD 0x00000001
# define RETURN_HOME_CMD 0x00000002
# define WRITE_CMD 0x00000200
# define FIRST_ROW 0x00000080
# define SECOND_ROW 0x000000C0

#define BASE_ADDRESS_KEYPAD 0xCAE00000
#define BASE_ADDRESS_MOTOR 0xC0A00000
#define BASE_ADDRESS_LEDSRGB 0xCB200000

void LCD_enviarCMD ( Xuint32 cmd ){
	// Comprobamos que la FIFO no esté llena
	while ( PANTALLALCD_mWriteFIFOFull(XPAR_PANTALLALCD_0_BASEADDR)){}
	// Escribimos el comando en la FIFO
	PANTALLALCD_mWriteToFIFO (XPAR_PANTALLALCD_0_BASEADDR, 0, (0x0 << 31) + cmd); //0x0 << 31 para escribir a 0 el bit 31 para que el multiplexor active el lcd
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
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B');
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'F' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'V' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
}
void mostrarMensajeResultadoLCD(){
	xil_printf (" Mostrar mensaje resultado\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'J' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + '/' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
}
void mostrarMensajeModoLCD(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
}
void mostrarMensajeModoAuto(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'Q' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
}
void mostrarMensajeInicialModoAuto(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
}
void mostrarMensajeInicialModoMan(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
}
void mostrarMensajeModoManSubir(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + '(' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ')' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + '(' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + ')' );
}
void mostrarMensajeModoManBajar(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'J' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + '(' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + ')' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + '(' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + ')' );
}
void mostrarMensajeBajandoBarrera(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'J' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
}
void mostrarMensajeSubiendoBarrera(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );

}
void mostrarMensajeEspere(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'F' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'V' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );



}
void mostrarMensajeBucleModoAuto(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'C' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'R' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );



}

void mostrarMensajeApagandoSistema(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'P' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'G' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );
	LCD_enviarCMD ( WRITE_CMD + 'N' );
	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'O' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'L' );
	LCD_enviarCMD ( SECOND_ROW ); // cambio fila
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'I' );
	LCD_enviarCMD ( WRITE_CMD + 'S' );
	LCD_enviarCMD ( WRITE_CMD + 'T' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'M' );
	LCD_enviarCMD ( WRITE_CMD + 'A' );

}
void mostrarMensajeDebug1(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'G' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + '1' );
}
void mostrarMensajeDebug2(){
	xil_printf (" Mostrar mensaje operacion\r\n");
	LCD_inicializa ();

	LCD_enviarCMD ( WRITE_CMD + 'D' );
	LCD_enviarCMD ( WRITE_CMD + 'E' );
	LCD_enviarCMD ( WRITE_CMD + 'B' );
	LCD_enviarCMD ( WRITE_CMD + 'U' );
	LCD_enviarCMD ( WRITE_CMD + 'G' );
	LCD_enviarCMD ( WRITE_CMD + ' ' );
	LCD_enviarCMD ( WRITE_CMD + '2' );
}
int getNumber(char nOperador){ //funcion para leer tecla del keypad y convertirla a su valor en decimal

	print("---Entrando en getNumber---\n\r");
	Xuint32 value,dato,oldValue;
	int num = 0;
	//mostrarMensajeOperadorLCD(nOperador);
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
void motorBajarBarrera() {
	Xuint32 Data;
	int i;
	for(i=0; i<70; i++ ){
		Data = 0x9E000000;
		MOTOR_HW_mWriteReg( BASE_ADDRESS_MOTOR, 0, Data );
		Data = MOTOR_HW_mReadReg ( BASE_ADDRESS_MOTOR, 0);
		while (!(Data & 0x40000000)) {
			Data = MOTOR_HW_mReadReg ( BASE_ADDRESS_MOTOR, 0);
		}
	}
}
void motorSubirBarrera() {
	Xuint32 Data;
	int i;
	for(i=0; i<70; i++ ){
		Data = 0x0E000000;
		MOTOR_HW_mWriteReg ( BASE_ADDRESS_MOTOR , 0, Data );
		Data = MOTOR_HW_mReadReg ( BASE_ADDRESS_MOTOR , 0);
		while (!(Data & 0x40000000)) {
			Data = MOTOR_HW_mReadReg ( BASE_ADDRESS_MOTOR , 0);
		}
	}

}
void iluminaPWMLeds(int r, int g, int b) {
	//usa los valores invertidos
	LEDSRGB_mWriteSlaveReg0(BASE_ADDRESS_LEDSRGB, 0, r); //Red
	LEDSRGB_mWriteSlaveReg1(BASE_ADDRESS_LEDSRGB, 0, g); //Green
	LEDSRGB_mWriteSlaveReg2(BASE_ADDRESS_LEDSRGB, 0, b); //Blue
}
void esperar(int delay) {
	int i, j;
	for (i = 0; i < delay; i = i + 1) {
		for (j = 0; j < 500; j = j + 1) {
			//no hago nada
		}
	}
}
int timerModoAuto(int delay) {
	//Queremos meter una forma de salir del bucle sin tener que esperar, en este caso que el usuario pulse una tecla
	//Si retorna 1 es que el usuario ha pulsado una tecla lo que significa que sale del modo automatico y vuelve al menu principal
	Xuint32 entrada;
	Xuint32 teclaOld;
	int teclaPulsada = 0;
	/* Se escribe un 0 para borrar la �ltima tecla le�da */
				TECLADOKEYPAD_mWriteReg(BASE_ADDRESS_KEYPAD, 0 ,0);
	int i, j;
	for (i = 0; i < delay; i = i + 1) {
		for (j = 0; j < 500; j = j + 1) {
			entrada =TECLADOKEYPAD_mReadReg(BASE_ADDRESS_KEYPAD, 0);

			if (entrada != teclaOld) {
				teclaOld = entrada;
				teclaPulsada = (entrada && 0x1);
				xil_printf("  El valor de teclaPulsada es %d\n\r", teclaPulsada);
				if (teclaPulsada) {
					return 0;
					}
			}
		}
	}

	return 1;
}
const int apagando[8][7] = {
    {0x1E, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x12},//A
    {0x1E, 0x12, 0x12, 0x1E, 0x10, 0x10, 0x10},//P
    {0x1E, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x12},//A
    {0x1E, 0x10, 0x10, 0x1E, 0x12, 0x12, 0x1E},//G
    {0x1E, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x12},//A
    {0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11},//N
    {0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0E},//D
    {0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F}//O

};
const int bajando[8][7] = {
    {0x1C, 0x12, 0x12, 0x1C, 0x12, 0x12, 0x1C},//B
    {0x1E, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x12},//A

    {0x1E, 0x02, 0x02,0x12, 0x12, 0x12, 0x1E},//J

    {0x1E, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x12},//A
    {0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11},//N
    {0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0E},//D
    {0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F},//O
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}//Espacio

};
const int subiendo[8][7] = {
    {0x1E, 0x10, 0x10, 0x1E, 0x02, 0x02, 0x1E},//S
    {0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1E},//U
    {0x1C, 0x12, 0x12, 0x1C, 0x12, 0x12, 0x1C},//B
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E},//I
    {0x1E, 0x10, 0x10, 0x1C, 0x10, 0x10, 0x1E},//E
    {0x11, 0x19, 0x15, 0x13, 0x11, 0x11, 0x11},//N
    {0x0E, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0E},//D
    {0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F}//O

};


void BANNER_enviarDato(Xuint32 col, Xuint32 fil,Xuint32 dato){


	while(PANTALLALCD_mWriteFIFOFull(XPAR_PANTALLALCD_0_BASEADDR)){}
	Xuint32 data;
	data = ((fil & 0xff)<< (31-7)) + ((col & 0xff) << (31-15)) + ((dato & 0xff)<< (31-23));
	//xil_printf("data %08x\n",data);
	PANTALLALCD_mWriteToFIFO (XPAR_PANTALLALCD_0_BASEADDR, 0, (0x1 << 31) + data); //0x0 << 31 para escribir a 1 el bit 31(esta invertido) para que el multiplexor active el lcd

}

void borrarBanner(){
	Xuint32 dato,fila,columna,data;
	dato=0x0;
	for(fila = 0; fila < 7; fila++){
			for(columna = 0; columna < 8; columna++){
				data = (( fila & 0xff ) << (31 -7)) +  (( columna & 0xff ) << (31 -15)) + (( dato & 0xff ) << (31 -23));
				PANTALLALCD_mWriteToFIFO( XPAR_PANTALLALCD_0_BASEADDR , 0, (0x1 << 31) + data);
			}
	}
}
void escribirBanner(const int word[8][7]){

	int i, j;
		for(i = 0; i < 8; i++){
			for(j = 0; j < 7; j++){
				BANNER_enviarDato(i,j,word[i][j]);
			}
		}
}
int main ()
{
	Xuint32 baseaddr;
	print("---Test para el keypad---\n\r");
	baseaddr = BASE_ADDRESS_KEYPAD;
	Xuint32 entrada;
	Xuint32 teclaOld;
	//char keypad[80];
	char caracter;
	int pos = 0;
	int salir = 0;
	int teclaPulsada = 0;
	int num1;
	int num2;
	int num3;
	int secsBarrera;
	int pueba;
	int barreraBajada=0;
	int barreraSubida =1; //Por defecto la barrera esta subida


	Xuint8 menuPrincipal = 1; //Si es 1 es verdadero
	Xuint8 modoAutomatico = 0;//Si es 0 es falso
	Xuint8 modoManual = 0;

	Xuint8 mensajeInicialMenuPrincipal = 0; //Si es 1 es verdadero
	Xuint8 mensajeInicialmodoAutomatico = 0;//Si es 0 es falso
	Xuint8 mensajeInicialmodoManual = 0;

entrada = TECLADOKEYPAD_mReadReg(baseaddr, 0);
// xil_printf("Se ha leido %x del registro 0 del teclado \n\r", entrada);
/* Se escribe un 0 para borrar la �ltima tecla le�da */
TECLADOKEYPAD_mWriteReg(baseaddr, 0, 0);
/* Se guarda el �ltimo valor recibido para compararlo con el siguiente */
teclaOld = entrada;
mostrarMensajeInicialLCD();

//rojo/verde,azul
iluminaPWMLeds(255,0,255);
esperar(5000);
//iluminaPWMLeds(255,0,0);
mostrarMensajeModoLCD();


while (!salir) {

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
		mostrarMensajeModoLCD();

		if (!salir) {
			/* Si el caracter est� entre 0xA y 0xE (10 y 14), a�adimos la letra may�scula
			 * sumando 55 al valor, de modo que 65 es 'A', 66 es 'B?', etc.; si no,
			 * a�adimos 48 al valor, de modo 48 es '0', 49 es '1', etc.
			 */
			caracter = (caracter > 9) ? (0x37 + caracter) : (0x30 + caracter);
			xil_printf("Se ha pulsado el caracter %c\n\r", caracter);

			if(caracter == 'A' || caracter == 'B' || caracter == 'C'){
				if(caracter == 'A'){
					modoAutomatico=1;
					modoManual =0;
					menuPrincipal =0;
					mensajeInicialmodoAutomatico =1;
				}else if(caracter == 'B'){
					modoAutomatico =0;
					modoManual=1;
					menuPrincipal = 0;
					mensajeInicialmodoManual = 1;
				}else if(caracter == 'C'){
					modoAutomatico =0;
					modoManual=0;
					menuPrincipal = 1;
					mensajeInicialMenuPrincipal= 0;
				}

				if(modoAutomatico){
					LCD_enviarCMD(CLEAR_DISPLAY_CMD);
					mostrarMensajeInicialModoAuto();
					esperar(5000);
					mostrarMensajeModoAuto();

					char numSelec[20];
					int i=0;
					num1 =0;
					num2=0;
					xil_printf("Entrando en modo Automatico \n\r");

					num1 = getNumber('1');
					intToChar(num1, numSelec, sizeof(numSelec));
					xil_printf("Se ha introducido el numero %d\n\r", num1);

					for (i=0;numSelec[i] != '\0'; ++i) {
						if(i==0){
							 LCD_enviarCMD(WRITE_CMD + ' ');
						 }
						 LCD_enviarCMD(WRITE_CMD + numSelec[i]);
					 }



					i=0;
					num2 = getNumber('2');
					intToChar(num2, numSelec, sizeof(numSelec));
					xil_printf("Se ha introducido el numero %d\n\r", num2);
					for (i=0;numSelec[i] != '\0'; ++i) {
						 LCD_enviarCMD(WRITE_CMD + numSelec[i]);
					 }




					secsBarrera=0;
					secsBarrera = num1 * 10 + num2;
					xil_printf("El resultado final es: %d\n\r", secsBarrera);


					char buffer[20];  // Ajusta el tamaño según tus necesidades
					intToChar(secsBarrera, buffer, sizeof(buffer));
					i=0;
					LCD_enviarCMD(CLEAR_DISPLAY_CMD);
					mostrarMensajeResultadoLCD();
					 for (i=0;buffer[i] != '\0'; ++i) {
						 xil_printf("La barrera bajara cada %c\n\r", buffer[i]);
						 //Meto el if este para retrasar un poco la ejecucion del bucle y no se deje caracteres por imprimir
						 if(i==0){
							 LCD_enviarCMD(WRITE_CMD + ' ');
						 }
						 LCD_enviarCMD(WRITE_CMD + buffer[i]);
					 }
					 LCD_enviarCMD(WRITE_CMD + ' ');
					 LCD_enviarCMD(WRITE_CMD + 's');
					 LCD_enviarCMD(WRITE_CMD + 'e');
					 LCD_enviarCMD(WRITE_CMD + 'c');
					 LCD_enviarCMD(WRITE_CMD + 's');
					 esperar(5000);
				}



			}
			if(menuPrincipal){
				if(mensajeInicialMenuPrincipal){
					mostrarMensajeInicialLCD();
					esperar(5000);//3 segundos aprox
					mensajeInicialMenuPrincipal=0;
				}
				mostrarMensajeModoLCD();
			}
			if(modoManual){
				if(mensajeInicialmodoManual){
					mostrarMensajeInicialModoMan();
					esperar(5000);//3 segundos aprox
					mensajeInicialmodoManual=0;
				}
				if(barreraSubida){
					LCD_inicializa ();
					mostrarMensajeModoManBajar();
				}else{
					LCD_inicializa ();
					mostrarMensajeModoManSubir();
				}

				if(caracter == 'D' && barreraSubida){//Bajar la barrera
					iluminaPWMLeds(0,255,255);

					LCD_inicializa ();
					mostrarMensajeBajandoBarrera();
					motorBajarBarrera();
					LCD_inicializa ();
					mostrarMensajeModoManSubir();

					barreraBajada=1;
					barreraSubida =0;

				}else if(caracter == 'E' && barreraBajada){//Subir la barrera

					LCD_inicializa ();
					mostrarMensajeSubiendoBarrera();
					motorSubirBarrera();
					iluminaPWMLeds(255,0,255);
					LCD_inicializa ();
					mostrarMensajeModoManBajar();

					barreraBajada=0;
					barreraSubida =1;
				}

				}
		}

	}
	if(modoAutomatico){
			LCD_inicializa ();
			mostrarMensajeBucleModoAuto();
			//Aproximacion de cuanto delay le tenemos que meter usando una regla de 3
			//el delay es +-1 segundo de lo introducido por el usuario

			if(timerModoAuto((5000*secsBarrera)/8)){
				if(barreraSubida){//Bajar la barrera
					iluminaPWMLeds(0,255,255);
					LCD_inicializa ();
					mostrarMensajeEspere();
					esperar(1000);
					escribirBanner(bajando);
					motorBajarBarrera();
					barreraBajada=1;
					barreraSubida =0;

				}else if(barreraBajada){//Subir la barrera
					LCD_inicializa ();
					mostrarMensajeEspere();
					esperar(1000);
					escribirBanner(subiendo);
					motorSubirBarrera();
					iluminaPWMLeds(255,0,255);
					barreraBajada=0;
					barreraSubida =1;
				}
			}else{
				modoAutomatico =0;
				modoManual=0;
				menuPrincipal = 1;
			}
		}
}
borrarBanner();
LCD_inicializa ();
mostrarMensajeApagandoSistema();
esperar(1000);
escribirBanner(apagando);
esperar(15000);
borrarBanner();
LCD_inicializa ();
iluminaPWMLeds(255,255,255);
return 0;
}

