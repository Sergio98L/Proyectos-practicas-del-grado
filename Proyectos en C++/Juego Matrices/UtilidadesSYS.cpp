#include "UtilidadesSYS.h"
#include <iostream>
#include <Windows.h>
using namespace std;


void chcp1252()
{   
	//Para que se muestren correctamente los acentos por pantalla
	system("chcp 1252");
}

void borrar()
{
	// Para borrar la consola 
	system("cls");
}

void pausa()
{
	system("pause");
}

 
uint8 colores[10] = { 0, 12, 10, 9, 14, 13, 3, 15, 8, 11 };
// negro(0), rojo(12), verde(10), azul(9), amarillo(14), magenta(13), cian2(3), blanco(15), gris(8), cian1(11) 

void colorCTA(uint8 color, uint8 fondo)  // fondo es un dígito
{   
	/* comentarios acerca de los colores:
	-----------------------------------
	Por defecto, el color de primer plano, aquel con el que se muestran los trazos de los
	caracteres, es blanco, mientras que el color de fondo es negro. Podemos cambiar esos
	colores,  aunque debemos hacerlo utilizando rutinas que son específicas
	de Visual Studio, por lo que debemos ser conscientes de que el programa no será
	portable a otros compiladores.
	
	Disponemos de 16 colores diferentes entre los que elegir, con valores de 0 a 15, tanto
	para el primer plano como para el fondo.
	
	Visual Studio incluye una biblioteca, Windows.h, que tiene, entre otras, rutinas para la
	consola. Una de ellas es SetConsoleTextAttribute(), que permite ajustar los colores
	de fondo y primer plano.

	Este se utiliza para cambiar el color de la pantalla de texto.
	El color al que cambia es colores[fondo].
	Los atributos de cada pixel se guardan en un byte y cada bit
	representa un aspecto del pixel. 
	Con la expresión: color | (colores[fondo] << 4)
	Se modifica el bit del color de fondo.

	Basta proporcionar un color para el fondo (1 a 14) y esta rutina lo establecerá, con el
	color de primer plano en 'color'. Debes cambiar el color de fondo cada vez que
	tengas que dibujar una casilla y volverlo a poner a negro (0) a continuación.

	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | (colores[fondo] << 4));

	
}
