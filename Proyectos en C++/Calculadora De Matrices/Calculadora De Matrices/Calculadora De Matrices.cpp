// Calculadora De Matrices.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int num_filas = 10;
const int num_columnas = 10;

typedef int Matriz[num_filas][num_columnas];


int main()
{
	Matriz matriz_1;
	Matriz matriz_2;

	int usuario_fila = 0;
	int usuario_columna = 0;
	int numero = 0;
	int usuario_matriz = 0;


	cout << "Introduzca la fila y la columna donde desee introducir un numero" << endl;
	cin >> usuario_fila;
	cin >> usuario_columna;

	cout << "Introduzca el numero que desee introducir" << endl;
	cin >> numero;

	cout << "Introducir valor en matriz 1 o matriz 2" << endl;
	cin >> usuario_matriz;


	//Inicializar la matriz
	for (int fila = 0; fila < num_filas; fila++) {
		for (int columna = 0; columna < num_columnas; columna++) {
			matriz_1[fila][columna] = 0;
			matriz_2[fila][columna] = 0;

			if (fila == usuario_fila && columna == usuario_columna) {
				if (usuario_matriz == 1) {
					matriz_1[fila][columna] = numero;
				}
				else if (usuario_matriz == 2) {
					matriz_2[fila][columna] = numero;
				}
			}
		}
	}

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
