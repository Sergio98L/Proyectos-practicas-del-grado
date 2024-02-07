#include "ModuloCoordenada.h"
#include "utilidadesSYS.h"
#include <fstream>
#ifndef Matriz_H
#define Matriz_H

using namespace std;
const int Max_Dim = 64;

const int dx[8] = { -1,-1,-1,0,0,1,1,1 };
const int dy[8] = { -1,0,1,-1,1,-1,0,1 };

typedef struct {
	int numFilas, numCols;
	int elementos[Max_Dim][Max_Dim];
}tMatriz;

bool	cargar(tMatriz& mat, istream& ent);
bool swapD(tMatriz& mat, int d);
bool swap(tMatriz& mat, tCoor pos1, tCoor pos2);
bool voltearF(tMatriz& mat, int f);
bool voltearC(tMatriz& mat, int c);
bool voltearD(tMatriz& mat, int d);
void voltearH(tMatriz& mat);
void voltearV(tMatriz& mat);
bool swapC(tMatriz& mat, int c1, int c2);
bool swapF(tMatriz& mat, int f1, int f2);
bool swapAdy(tMatriz& mat, tCoor pos1, tCoor pos2);
bool VoltearID(tMatriz& mat);
void rotarD(tMatriz& mat);
#endif