#include <iostream>
#include "ModuloCoordenada.h"
#include "ModuloJuegoPM.h"
#include "ModuloMatriz.h"
#include "UtilidadesSYS.h"
#include <Windows.h>
#include <iomanip>


void mainJuegoPM() {

	tJuegoPM jpm;

	int num_modo;
	string modo;
	bool no_salir = true;

	num_modo = menu();

	if (num_modo == 0) {
		no_salir = false;
	}
	else if (num_modo == 1) {
		modo = "1D";
	}
	else {
		modo = "2D";
	}

	if (no_salir) {
		iniciar(jpm, modo);
	}
}
int  menu() {


	bool correcto = false;
	int c;

	cout << "Seleccione su modo de juego:" << endl << endl;

	while (!correcto) {
		cout << "Para seleccionar modo 1D introduzca 1" << endl;
		cout << "Para seleccionar modo 2D introduzca 2" << endl;
		cout << "Para salir del juego introduzca 0" << endl;
		cout << "Introduzca un numero: ";

		cin >> c;
		switch (c) {
		case 0:
			cout << "Saliendo";
			correcto = true;
			break;
		case 1:
			correcto = true;
			break;
		case 2:
			correcto = true;
			break;
		default:
			cout << "Numero introducido no valido" << endl;
			correcto = false;
		}
	}
	return c;
}
bool iniciar(tJuegoPM& jpm, string modo) {
	//Iniciar los campos de jpm
	jpm.modo = modo;
	jpm.max_acciones = 0;
	cargar(jpm);
	jugar(jpm);
	return true;
}
bool cargar(tJuegoPM& jpm) {

	string nom_archivo = "";
	cout << "Introduzca el nombre del archivo que desea abrir: ";
	cin >> nom_archivo;

	nom_archivo += "_" + jpm.modo + ".txt";

	bool abierto = true;
	ifstream ent;

	ent.open(nom_archivo);
	if (ent.is_open()) {
		cargar(jpm.mat, ent);
		cargar(jpm.sol, ent);
	}
	else {
		abierto = false;
		cout << "No se pudo abrir el archivo";
	}
	ent >> jpm.max_acciones;
	ent.close();

	/*
		/// /////////////////////
		int d = 2;
		int c1=1;
		int c2=2;

		//Funciona: voltearF(jpm.mat, d);
		//Funciona: voltearC(jpm.mat, d);
		//Funciona: voltearH(jpm.mat);
		//Funciona:	voltearV(jpm.mat);
		//Funciona: swapC(jpm.mat, c1, c2);
		//Funciona:	swapF(jpm.mat, c1, c2);

		//voltearD(jpm.mat, d);
		//swapD(jpm.mat, d);

		for (int i = 0; i < jpm.mat.numFilas; i++) {
			for (int j = 0; j < jpm.mat.numCols; j++) {
				cout << jpm.mat.elementos[i][j] << " ";
			}
			cout << endl;
		}



		*//// /////////////////////


	return abierto;
}
bool jugar(tJuegoPM& jpm) {

	bool continua_juego = true;

	for (int i = 0; i < jpm.max_acciones; i++) {

		mostrar(jpm);
		cout << endl << "Movimientos disponibles: " << jpm.max_acciones-i << endl << endl;
		accion(jpm);
		mostrar(jpm);
		
		cout << endl;

	}
	continua_juego = false;
	return continua_juego;
}
bool accion(tJuegoPM& jpm) {

	int accion = 0;
	bool correcto = false;
	int c1 = 0;
	int c2 = 0;

	if (jpm.modo == "1D") {

		cout << endl << "Acciones disponibles en el modo 1D:" << endl << endl;
		cout << "1: Intercambiar dos filas" << endl;
		cout << "2: Intercambiar dos columnas" << endl;
		cout << "3: Intercambiar dos diagonales" << endl;
		cout << "4: Voltear una fila" << endl;
		cout << "5: Voltear una columna" << endl;
		cout << "6: Voltear una diagonal" << endl << endl;

		while (!correcto) {
			cout << "Introduzca el numero de la accion que desea realizar :";
			cin >> accion;

			switch (accion) {
			case 1:

				cout << endl << "Seleccione la fila 1:  ";
				cin >> c1;
				cout << endl << "Seleccione la fila 2: ";
				cin >> c2;

				if (swapF(jpm.mat, c1, c2)) {
					correcto = true;
					break;
				}
				else {
					cout << "Filas no validas" << endl;
					correcto = false;
					break;
				}
			case 2:

				cout << endl << "Seleccione una columna:  ";
				cin >> c1;
				cout << endl << "Introduzca la columna por la que quiere intercambiar la columna seleccionada anteriormente: ";
				cin >> c2;
	
				if (swapC(jpm.mat, c1, c2)) {
					correcto = true;
					break;
				}
				else {
					cout << "Columnas no validas" << endl;
					correcto = false;
					break;
				}

			case 3:

				cout << endl << "Seleccione la diagonal que desea intercambiar:  ";
				cin >> c1;

				if (swapD(jpm.mat, c1)) {
					correcto = true;
					break;
				}
				else {
					cout << "Columnas no validas" << endl;
					correcto = false;
					break;
				}

			case 4:

				cout << endl << "Seleccione la fila que desea voltear:  ";
				cin >> c1;

				if (voltearF(jpm.mat, c1)) {
					correcto = true;
					break;
				}
				else {
					cout << "Fila no valida" << endl;
					correcto = false;
					break;
				}
			case 5:

				cout << endl << "Seleccione la columna que desea voltear:  ";
				cin >> c1;

				if (voltearC(jpm.mat, c1)) {
					correcto = true;
					break;
				}
				else {
					cout << "Columna no valida" << endl;
					correcto = false;
					break;
				}

			case 6:

				cout << endl << "Seleccione la diagonal que desea voltear:  ";
				cin >> c1;

				if (voltearD(jpm.mat, c1)) {
					correcto = true;
					break;
				}
				else {
					cout << "Diagonal no valida" << endl;
					correcto = false;
					break;
				}

			default:
				cout << "Numero introducido no valido" << endl;
				correcto = false;
			}
		}
		return correcto;
	}
	else if (jpm.modo == "2D") {
		cout << "Acciones disponibles en el modo 2D:" << endl << endl;
		cout << "1: Dar la vuelta a la imagen completa con respecto a su eje vertical central" << endl;
		cout << "2: Dar la vuelta a la imagen completa con respecto a su eje horizontal central." << endl;
		cout << "3: Rotar una imagen 90 grados en el sentido de las agujas del reloj." << endl;
		cout << "4: Intercambiar las posiciones vecinas o adyacentes de las posiciones [a,b] y [c,d]." << endl;
		cout << "5: Dar la vuelta a  la imagen completa respecto a la diagonal principal" << endl << endl;

		while (!correcto) {
			cout << "Introduzca el numero de la accion que desea realizar :";
			cin >> accion;

			switch (accion) {
			case 1:

				voltearV(jpm.mat);
				correcto = true;
				break;

			case 2:

				voltearH(jpm.mat);
				correcto = true;
				break;

			case 3:

				rotarD(jpm.mat);
				correcto = true;
				break;

			case 4:
				tCoor pos1, pos2;

				cout << endl << "Seleccione la coordenada 1:  ";
				cin >> pos1.ejeX >> pos1.ejeY;
				cout << endl << "Seleccione la coordenada 2: ";
				cin >> pos2.ejeX >> pos2.ejeY;

				if ((pos1.ejeX >= 0 && pos1.ejeY >= 0) && (pos2.ejeX >= 0 && pos2.ejeY >= 0)&& (swapAdy(jpm.mat, pos1, pos2))) {
					correcto = true;
					break;
				}
				else
				{
					cout << "Coordenadas no validas" << endl;
					correcto = false;
					break;
				}

			case 5:

				VoltearID(jpm.mat);
				correcto = true;
				break;

			default:
				cout << "Numero introducido no valido" << endl;
				correcto = false;
			}
		}
	}
}
void mostrar(tJuegoPM const& jpm)
{
	borrar();
	cout << "   ";
	for (int i = 0; i < jpm.mat.numCols; i++)
		cout << i / 10;
	cout << endl;
	cout << "   ";
	for (int i = 0; i < jpm.mat.numCols; i++)
		cout << i % 10;

	cout << endl;
	for (int i = 0; i < jpm.mat.numFilas; i++)
	{
		colorCTA(15, 0);
		std::cout << std::setfill(' ') << std::setw(3);
		cout << i;
		for (int j = 0; j < jpm.mat.numCols; j++)
		{

			colorCTA(0, jpm.mat.elementos[i][j]);

			cout << " ";
		}
		colorCTA(15, 0);
		cout << endl;

	}
	colorCTA(15, 0);

	cout << endl;
	cout << "   ";
	for (int i = 0; i < jpm.sol.numCols; i++)
		cout << i / 10;
	cout << endl;
	cout << "   ";
	for (int i = 0; i < jpm.sol.numCols; i++)
		cout << i % 10;
	cout << endl;
	for (int i = 0; i < jpm.sol.numFilas; i++)
	{
		colorCTA(15, 0);
		std::cout << std::setfill(' ') << std::setw(3);
		cout << i;
		for (int j = 0; j < jpm.sol.numCols; j++)
		{

			colorCTA(0, jpm.sol.elementos[i][j]);

			cout << " ";
		}
		colorCTA(15, 0);
		cout << endl;

	}
	colorCTA(15, 0);

}

