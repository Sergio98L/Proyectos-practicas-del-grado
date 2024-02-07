#include <iostream>
#include "ModuloCoordenada.h"
#include "ModuloJuegoPM.h"
#include "ModuloMatriz.h"
#include <Windows.h>

bool cargar(tMatriz& mat, istream& ent) {


	//Carga la matriz inicial del fichero
	ent >> mat.numFilas >> mat.numCols;
	for (int i = 0; i < mat.numFilas; i++) {
		for (int j = 0; j < mat.numCols; j++) {
			ent >> mat.elementos[i][j];
		}
	}

	//Mostrar primera matriz
	/*
	for (int i = 0; i < mat.numFilas; i++) {
		for (int j = 0; j < mat.numCols; j++) {
			cout << mat.elementos[i][j] << " ";
		}
		cout << endl;
	}
	*/
	return true;
}
bool swap(tMatriz& mat, tCoor pos1, tCoor pos2)
{
	int aux;
	bool sol = false;
	bool pos1Existe = true;
	bool pos2Existe = true;
	if (pos1.ejeY+1 > mat.numFilas || pos1.ejeY<0 || pos1.ejeX + 1 > mat.numCols || pos1.ejeX < 0) { pos1Existe = false; }
	if (pos2.ejeY+1 > mat.numFilas || pos2.ejeY<0 || pos2.ejeX + 1 > mat.numCols || pos2.ejeX < 0) { pos2Existe = false; }
	if (pos1Existe && pos2Existe)
	{
		sol = true;
		aux = mat.elementos[pos1.ejeY][pos1.ejeX];
		mat.elementos[pos1.ejeY][pos1.ejeX] = mat.elementos[pos2.ejeY][pos2.ejeX];
		mat.elementos[pos2.ejeY][pos2.ejeX] = aux;
	}
	return sol;
}
bool swapD(tMatriz& mat, int d)
{
	bool sol = false;
	bool dExiste = true;
	bool matrizCuadrada = true;
	if (d+1 > mat.numFilas || d < 0) { dExiste = false; }
	if (mat.numCols != mat.numFilas) { matrizCuadrada = false; }
	if (matrizCuadrada && dExiste)
	{
		bool SinError = true;
		tCoor pos1;
		tCoor pos2;
		for (int i = 0; i < mat.numFilas - d; i++)
		{
			pos1.ejeY = i;
			pos1.ejeX = d + i;
			pos2.ejeY = d + i;
			pos2.ejeX = i;

			SinError = swap(mat, pos1, pos2);
			if (SinError == false) { cout << "Error inseperado" << endl; }
		}
		sol = true;
	}

	return sol;
}
bool voltearF(tMatriz& mat, int f)
{
	bool resultado = true;
	tCoor coor1, coor2;
	coor1.ejeY = f;
	coor2.ejeY = f;
	for (int i = 0; i < (mat.numCols / 2); i++)
	{
		coor1.ejeX = i;
		coor2.ejeX = mat.numCols - 1 - i;
		if (swap(mat, coor1, coor2) == false)
		{
			resultado = false;
		}
	}
	return resultado;
}
bool voltearC(tMatriz& mat, int c)
{
	bool resultado = true;
	tCoor coor1, coor2;
	coor1.ejeX = c;
	coor2.ejeX = c;
	for (int i = 0; i < (mat.numFilas / 2); i++)
	{
		coor1.ejeY = i;
		coor2.ejeY = mat.numFilas - 1 - i;
		if (swap(mat, coor1, coor2) == false)
		{
			resultado = false;
		}
	}
	return resultado;
}
bool voltearD(tMatriz& mat, int d)
{
	bool result = false;
	tCoor pos1;
	tCoor pos2;
	if (d >= 0)
	{
		for (int i = 0; i < (mat.numCols - d) / 2; i++)
		{
			pos1.ejeX = d + i;
			pos1.ejeY = 0 + i;
			pos2.ejeX = mat.numCols - 1 - i;
			pos2.ejeY = mat.numFilas - 1 - d - i;
			result = true;
			if (swap(mat, pos1, pos2)==false) { result = false; }
		}
	}
	else
	{
		for (int i = 0; i < (mat.numFilas - d) / 2; i++)
		{
			pos1.ejeY = d + i;
			pos1.ejeX = 0 + i;
			pos2.ejeY = mat.numFilas - 1 - i;
			pos2.ejeX = mat.numCols - d - i;
			result = true;
			if (swap(mat, pos1, pos2) == false) { result = false; }
		}
	}
	return result;
}
void voltearV(tMatriz& mat)
{
	for (int f = 0; f < mat.numFilas; f++)
	{
		voltearF(mat, f);
	}
}
void voltearH(tMatriz& mat)
{
	for (int c = 0; c < mat.numCols; c++)
	{
		voltearC(mat, c);
	}
}
bool swapC(tMatriz& mat, int c1, int c2)
{
	bool sol = false;
	bool c1Existe = true;
	bool c2Existe = true;
	if (c1+1 > mat.numFilas  || c1 < 0) { c1Existe = false; }
	if (c2+1 > mat.numFilas || c2 < 0) { c2Existe = false; }
	if (c1Existe && c2Existe)
	{
		bool SinError = true;
		tCoor pos1;
		tCoor pos2;
		pos1.ejeX = c1;
		pos2.ejeX = c2;
		for (int i = 0; i < mat.numFilas; i++)
		{
			pos1.ejeY = i;
			pos2.ejeY = i;
			SinError = swap(mat, pos1, pos2);
			if (SinError == false) { cout << "Error inseperado" << endl; }
		}
		sol = true;
	}
	return sol;
}
bool swapF(tMatriz& mat, int f1, int f2)
{
	bool sol = false;
	bool f1Existe = true;
	bool f2Existe = true;
	if (f1+1 > mat.numFilas || f1 < 0) { f1Existe = false; }
	if (f2+1 > mat.numFilas || f2 < 0) { f2Existe = false; }
	if (f1Existe && f2Existe)
	{
		bool SinError = true;
		tCoor pos1;
		tCoor pos2;
		pos1.ejeY = f1;
		pos2.ejeY = f2;
		for (int i = 0; i < mat.numCols; i++)
		{
			pos1.ejeX = i;
			pos2.ejeX = i;
			SinError = swap(mat, pos1, pos2);
			if (SinError == false) { cout << "Error inseperado" << endl; }
		}
		sol = true;
	}
	return sol;
}
bool VoltearID(tMatriz& mat)
{
	bool result = true;
	if (mat.numCols != mat.numFilas)
	{
		result = false;
	}
	else
	{
		for (int d = 1; d < mat.numCols; d++)
		{
			swapD(mat, d);
		}
	}
	return result;
}
void rotarD(tMatriz& mat)
{
	if (mat.numCols >= mat.numFilas)
	{
		int aux = mat.numFilas;
		int aux2 = mat.numCols - mat.numFilas;
		voltearH(mat);
		for (int i = mat.numFilas; i < mat.numFilas + aux2; i++) {
			for (int j = 0; j < mat.numCols; j++) {
				mat.elementos[i][j] = 0;
			}
		}

		mat.numFilas = mat.numCols;
		voltearH(mat);
		VoltearID(mat);
		voltearV(mat);
		mat.numCols = aux;
	}
	else
	{
		int aux = mat.numCols;
		int aux2 = mat.numFilas - mat.numCols;
		for (int i = mat.numCols; i < mat.numCols + aux2; i++) {
			for (int j = 0; j < mat.numFilas; j++) {
				mat.elementos[j][i] = 0;
			}
		}

		mat.numCols = mat.numFilas;
		VoltearID(mat);
		voltearV(mat);
		mat.numFilas = aux;
	}
}
bool swapAdy(tMatriz& mat, tCoor pos1, tCoor pos2)
{
	bool resultado = true;
	if ((abs(pos1.ejeX - pos2.ejeX) < 2 && abs(pos1.ejeY - pos2.ejeY) < 2) || pos1.ejeX < 1 || pos1.ejeY < 1 || pos2.ejeX < 1 || pos2.ejeY < 1 || pos1.ejeX > mat.numCols - 2 || pos1.ejeY > mat.numFilas - 2 || pos2.ejeX > mat.numCols - 2 || pos2.ejeY > mat.numFilas - 2)
	{
		resultado = false;
	}
	else
	{
		tCoor coor1, coor2;
		for (int i = 0; i < 8; i++)
		{
			coor1.ejeX = pos1.ejeX + dx[i];
			coor1.ejeY = pos1.ejeY + dy[i];
			coor2.ejeX = pos2.ejeX + dx[i];
			coor2.ejeY = pos2.ejeY + dy[i];
			if (swap(mat, coor1, coor2) == false)
			{
				resultado = false;
			}
		}
	}
	return resultado;
}