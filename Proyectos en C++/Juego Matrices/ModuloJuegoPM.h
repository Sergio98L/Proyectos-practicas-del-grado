#include "ModuloMatriz.h"
#ifndef Juego_H
#define Juego_H

typedef struct {
	tMatriz mat, sol;
	int max_acciones;
	string modo;
}tJuegoPM;

bool	cargar(tJuegoPM& jpm);
int		menu();
void	mainJuegoPM();
bool	iniciar(tJuegoPM& jpm, string modo);
bool accion(tJuegoPM& jpm);
bool jugar(tJuegoPM& jpm);
void mostrar(tJuegoPM const& jpm);
#endif
