#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits> // Para pausa()
#ifdef _WIN32	 // Se define automáticamente en Visual Studio
#include <windows.h>
#undef max // Para poder usar max() en pausa()
#endif
#include <fstream>

using namespace std;

//Variables Globales:
char circulito = -89; //Implementacion del carácter "º"

//Constantes:
const int NUM_Jugadores = 4;
const int NUM_Fichas = 4;
const int NUM_Casillas = 68;
const int meta[4] = { 108,208,308,408 };

//Boleanos:
bool verdad[4] = { true,true,true,true };
bool ganar[4] = { false,false,false,false };
bool Jugando = true;
bool debug = false;

//Definiciones de tipos:
typedef enum {
	Amarillo,
	Azul,
	Rojo,
	Verde,
	Gris,
	Ninguno
} tColor;


typedef tColor tTurnos[NUM_Jugadores];

typedef struct {
	int fichas[NUM_Fichas];

}tJugador;

typedef struct {
	tColor calle1[NUM_Casillas];
	tColor calle2[NUM_Casillas];

}tCasillas;

typedef struct
{

	int turnoActual;
	tJugador jugadores[NUM_Jugadores];
	//tJugadores jugadores;
	tCasillas casillas;
	tTurnos turno;
	tColor ColorJugador[NUM_Jugadores];
	int nSeises;
	int dado;
	int puesto;
	int ultimaFichaMovida;
	int proximasTiradas[500];
	int tiradaActual;

}tJuego;

//Declaración de funciones:
void comienzaElJuego();

//(129)Funciones de inicio:
void iniciarTodo(tJuego& juego);//Llama al resto de funciones para iniciar por partes
void intro();//Mensaje de bienvenida
void iniciarIntStruct(tJuego& juego);//Inicializa las variables del struct
void iniciarNumerosAleatorios();//Inicializa sran
void iniciarFichas(tJuego& juego);//Inicializa las fichas a la posicion -1
void iniciarTurnos(tJuego& juego);//Inicializa el orden de turnos aleatorios
void iniciaColores();//Inicializa los colores
void iniciarColorCasillas(tJuego& juego);//Inicializa todas las casillas en color ninguno
void cargar(tJuego& juego);//Carga un archivo externo cuando debug == true
tColor escogercolor(tJuego& juego, int n);//Pregunta al usuario con que color quiere jugar

//(274)Funciones para mostrar:
void mostrar(const tJuego& juego);//Muestra el tablero
void mostrarTurnos(tJuego& juego);//Muestra los turnos para debuging
void mostrarFichas(tJuego& juego);//Muestra las fichas para debuging
void mostrarColorCasillas(tJuego& juego);//Muestra los colores de las casillas para debuging
void mostrarPuedoMover(tJuego& juego, bool sePuedeMover[]);//Muestra al usuario las fichas que puede mover y a donde
void setColor(tColor color);
void tresPuntos();//Animacion que muestra 3 puntos suspensivos cargando
void animacionAleatorio();//Animacion que muestra un dado aleatorio
void pausa();
int cambioMostrar(tColor jug);//Como hemos cambiado las zanatas de las fichas esta funcion arregla el mostrar con nuestro cambio
string colorACadena(tColor color);

//(686)Funciones del dado:
int tirardado();//--Aleatorio
int tirardadousuario(tJuego& juego); //--No Aleatorio

//(707)Funciones para fichas:
int cuantasEn(const int fichas[NUM_Fichas], int casilla);
int primeraEn(const int fichas[NUM_Fichas], int casilla);
int segundaEn(const int fichas[NUM_Fichas], int casilla);
int contadorFichasEn(tJuego& juego, int casilla);//--Cuenta las fichas de todos los jugadores

//(760)Funciones para casillas:
int zanataJugador(tColor jugador);
int salidaJugador(tColor jugador);
bool esSeguro(int casilla);
void reajustarColores(tJuego& juego, int casillaAnterior, int casillaPosterior);//Esta funcion se encarga de reajustar los colores cuando hay 2 fichas en una misma casilla

//(867)Funciones del turno: 
void ejecutarturno(tJuego& juego);//Esta funcion se encarga de ejecutar el turno
void turnoSiguiente(tJuego& juego);//Esta funcion se encarga de cambiar de turno
void procesa5(tJuego& juego, bool pasaTurno);
void procesa6(tJuego& juego, bool& pasaTurno);
void jugar(tJuego& juego);//Esta funcion se encarga de procesar las tiradas normales (dado = 1-4)


//(998)Funciones relacionadas con el movimiento de fichas:
void mover(tJuego& juego, bool sePuedeMover[]);//Esta funcion se encarga de pedir al usuario que ficha quiere mover y moverla
void puedeMover(tJuego& juego, bool sePuedeMover[]);//Esta funcion se encarga de comprobar que fichas del jugador se pueden mover
void saleFicha(tJuego& juego, int cuantasEnSalida);//Esta funcion se encarga de sacar la ficha de casa
void comerFicha(tJuego& juego, bool sePuedeMover[], int fichaParaMover, int i, int f);//Esta funcion se encarga de comer la ficha
void premio(tJuego& juego, bool sePuedeMover[], int fichaParaMover);//Esta funcion se encarga de si hay premio
void entrarZanata(tJuego& juego, int fichaParaMover, int casillaAnterior, int casillaPosterior);//Esta funcion se encarga de gestionar la entrada a zanata de una ficha
int puente(tJuego& juego, int proximaCasilla, int FICHA);//Esta funcion se encarga de comprobar donde hay puentes
void abrirPuente(tJuego& juego);//Esta funcion se encarga de abrir puentes cuando es obligatorio abrirlos



int main()
{
	system("cls");
	comienzaElJuego();
	return 0;
}
void comienzaElJuego()
{

	tJuego juego;
	iniciarTodo(juego);
	mostrar(juego);
	while (Jugando)
	{
		ejecutarturno(juego);

	}
}

//Funciones de inicio:
void iniciarTodo(tJuego& juego)
{


	intro();
	for (int n = 0; n < NUM_Jugadores; n++)
	{
		juego.ColorJugador[n] = escogercolor(juego, n);
	}
	iniciarIntStruct(juego);
	iniciarNumerosAleatorios();
	iniciarFichas(juego);
	iniciarTurnos(juego);
	iniciaColores();
	iniciarColorCasillas(juego);
	//mostrarFichas(juego);
	//mostrarColorCasillas(juego);
	//mostrarTurnos(juego);
	tColor jugadorTurno = juego.turno[0];
	if (debug) {
		cargar(juego);
	}

}
void intro()
{
	cout << "\x1B[97;107m" << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------" << "\x1B[32;42m" << "                                           " << "\x1B[97;107m" << "-----------------------------" << endl;
	cout << "-----------------------------" << "\x1B[32;42m" << "    " << "\x1B[34;107m" << " Bienvenido la version 3 del parchis " << "\x1B[32;42m" << "    " << "\x1B[97;107m" << "----------------------------" << endl;
	cout << "------------------------------" << "\x1B[32;42m" << "                                           " << "\x1B[97;107m" << " ----------------------------" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << "--------------------------------" << "\x1B[34;107m" << "By Ignacio Domenech y Sergio Dominguez" << "\x1B[97;107m" << "--------------------------------" << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	cout << endl;
	setColor(Ninguno);

	//" << "\x1B[34;107m" << "x" << "\x1B[97;107m" << "
}
void iniciarIntStruct(tJuego& juego) {
	juego.proximasTiradas[0] = 0;
	juego.turnoActual = 0;
	juego.nSeises = 0;
	juego.dado = 0;
	juego.puesto = 0;
	juego.ultimaFichaMovida = 0;
	juego.tiradaActual = 0;
}
void iniciarNumerosAleatorios() { srand(time(NULL)); }
void iniciarFichas(tJuego& juego)
{
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		for (int f = 0; f < NUM_Fichas; f++)
		{
			juego.jugadores[i].fichas[f] = -1;
		}
	}
}
void iniciarTurnos(tJuego& juego)
{
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		bool Novalido = true;
		int num;
		while (Novalido)
		{
			Novalido = false;
			num = rand() % ((NUM_Jugadores)-0);
			for (int a = 0; a < i; a++)
			{
				int aux = juego.turno[a];
				if (aux == num)
				{
					Novalido = true;
				}
			}
		}
		juego.turno[i] = (tColor(num));
	}
}
void iniciaColores()
{
#ifdef _WIN32
	for (DWORD stream : {STD_OUTPUT_HANDLE, STD_ERROR_HANDLE})
	{
		DWORD mode;
		HANDLE handle = GetStdHandle(stream);

		if (GetConsoleMode(handle, &mode))
		{
			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(handle, mode);
		}
	}
#endif
}
void iniciarColorCasillas(tJuego& juego)
{
	for (int i = 0; i < NUM_Casillas; i++)
	{
		juego.casillas.calle1[i] = Ninguno;
		juego.casillas.calle2[i] = Ninguno;
	}
}
void cargar(tJuego& juego)
{
	ifstream archivo;
	int jugador, casilla;
	bool seguirleyendo = true;

	archivo.open("Prueba5.txt"); //poner aqui la ruta del archivo
	if (archivo.is_open())
	{
		for (int i = 0; i < NUM_Jugadores; i++)
			for (int f = 0; f < NUM_Fichas; f++)
			{
				archivo >> casilla;
				juego.jugadores[i].fichas[f] = casilla;
				if ((casilla >= 0) && (casilla < NUM_Casillas))
					if (juego.casillas.calle1[casilla] == Ninguno)
						juego.casillas.calle1[casilla] = tColor(i);
					else
						juego.casillas.calle2[casilla] = tColor(i);
			}
		archivo >> jugador;
		for (int i = 0; i < 500 && seguirleyendo; i++) {
			int aux;
			archivo >> aux;
			if (aux == -1) {
				juego.proximasTiradas[i] = 0;
				seguirleyendo = false;
			}
			else {
				juego.proximasTiradas[i] = aux;
			}
		}
		tColor jugadorTurno = tColor(jugador);
		archivo.close();
	}
}
tColor escogercolor(tJuego& juego, int n)
{
	int aux = 0;

	while (aux == 0)
	{
		int a = 0;
		bool ColorRepetido = false;
		cout << "1 = Amarillo, 2 = Azul, 3 = Rojo y 4 = Verde" << endl;
		cout << "Usuario " << n + 1 << " escoge un color: ";
		cin >> a;
		tColor ColorEscogido = tColor(a - 1);
		for (int i = 0; i < NUM_Jugadores; i++)
		{
			if (ColorEscogido == juego.ColorJugador[i])
			{
				ColorRepetido = true;
			}
		}
		if (ColorRepetido == true)
		{
			cout << "Este color lo ha escogido otro jugador" << endl;
		}
		else if (a < 0 || a > 4)
		{
			cout << "El color no es valido vuelve a intentarlo" << endl;
		}
		else
		{
			aux++;
			return ColorEscogido;
		}
	}
}
//Funciones para mostrar:
void mostrar(const tJuego& juego)
{
	Sleep(1000);
	int casilla, ficha;
	tColor jug;

	cout << "\x1b[2J\x1b[H"; // Se situa en la esquina superior izquierda
	setColor(Gris);
	cout << endl;

	// Filas con la numeraci�n de las casillas...
	for (int i = 0; i < NUM_Casillas; i++)
		cout << i / 10;
	cout << endl;
	for (int i = 0; i < NUM_Casillas; i++)
		cout << i % 10;
	cout << endl;

	// Borde superior...
	for (int i = 0; i < NUM_Casillas; i++)
		cout << '>';
	cout << endl;

	// Primera fila de posiciones de fichas...
	for (int i = 0; i < NUM_Casillas; i++)
	{
		setColor(juego.casillas.calle2[i]);
		if (juego.casillas.calle2[i] != Ninguno)
		{
			if (juego.casillas.calle2[i] != juego.casillas.calle1[i]) {
				cout << primeraEn(juego.jugadores[juego.casillas.calle2[i]].fichas, i) + 1;
			}
			else {
				cout << segundaEn(juego.jugadores[juego.casillas.calle2[i]].fichas, i) + 1;
			}
		}
		else
			cout << ' ';
		setColor(Gris);
	}
	cout << endl;

	// "Mediana"
	for (int i = 0; i < NUM_Casillas; i++)
		if (esSeguro(i))
			cout << 'o';
		else
			cout << '-';
	cout << endl;

	// Segunda fila de posiciones de fichas...
	for (int i = 0; i < NUM_Casillas; i++)
	{
		setColor(juego.casillas.calle1[i]);
		if (juego.casillas.calle1[i] != Ninguno)
			cout << primeraEn(juego.jugadores[juego.casillas.calle1[i]].fichas, i) + 1;
		else
			cout << ' ';
		setColor(Gris);
	}
	cout << endl;

	jug = Amarillo;
	// Borde inferior...
	for (int i = 0; i < NUM_Casillas; i++)
	{
		if (i == 0) { i = 68; }
		if (i == zanataJugador(jug))
		{
			setColor(jug);
			cout << "V";
			setColor(Gris);
			if (i == 68) { i = 0; }
		}
		else if (i == salidaJugador(jug))
		{
			setColor(jug);
			cout << "^";
			setColor(Gris);
			jug = tColor(int(jug) + 1);
		}
		else
			cout << '>';

	}
	cout << endl;
	// Metas y casas...

	for (int i = 0; i < NUM_Fichas; i++)
	{
		casilla = 0;
		jug = Amarillo;
		setColor(jug);
		while (casilla < NUM_Casillas)
		{
			int aux[4];
			for (int x = 0; x < 4; x++)
			{
				aux[x] = juego.jugadores[jug].fichas[x] - cambioMostrar(jug);
			}
			if (casilla == 0) { casilla = 68; }
			if (casilla == zanataJugador(jug))
			{
				ficha = primeraEn(juego.jugadores[jug].fichas, 101 + i);
				if (ficha != -1)
				{
					cout << ficha + 1;
					if (cuantasEn(juego.jugadores[jug].fichas, 101 + i) > 1)
					{
						ficha = segundaEn(juego.jugadores[jug].fichas, 101 + i);
						if (ficha != -1)
						{
							cout << ficha + 1;
						}
						else
							cout << "V";
					}
					else
						cout << "V";
				}
				else
					cout << "VV";
				if (casilla == 68) { casilla = 0; }
				casilla++;
			}
			else if (casilla == salidaJugador(jug))
			{
				if (juego.jugadores[jug].fichas[i] == -1) // En casa
					cout << i + 1;
				else
					cout << "^";
				jug = tColor(int(jug) + 1);
				setColor(jug);
			}
			else
				cout << ' ';
			casilla++;
		}
		cout << endl;
	}

	// Resto de metas...
	for (int i = 105; i <= 107; i++)
	{
		casilla = 0;
		jug = Amarillo;
		setColor(jug);
		while (casilla < NUM_Casillas)
		{
			int aux[4];
			for (int x = 0; x < 4; x++)
			{
				aux[x] = juego.jugadores[jug].fichas[x] - cambioMostrar(jug);
			}
			if (casilla == 0) { casilla = 68; }
			if (casilla == zanataJugador(jug))
			{
				ficha = primeraEn(juego.jugadores[jug].fichas, i);
				if (ficha != -1)
				{
					cout << ficha + 1;
					if (cuantasEn(juego.jugadores[jug].fichas, i) > 1)
					{
						ficha = segundaEn(juego.jugadores[jug].fichas, i);
						if (ficha != -1)
						{
							cout << ficha + 1;
						}
						else
							cout << "V";
					}
					else
						cout << "V";
				}
				else
					cout << "VV";
				if (casilla == 68) { casilla = 0; }
				casilla++;
				jug = tColor(int(jug) + 1);
				setColor(jug);
			}
			else
				cout << ' ';

			casilla++;
		}
		cout << endl;
	}

	casilla = 0;
	jug = Amarillo;
	setColor(jug);
	while (casilla < NUM_Casillas)
	{
		int aux[4];
		for (int x = 0; x < 4; x++)
		{
			aux[x] = juego.jugadores[jug].fichas[x] - cambioMostrar(jug);
		}
		cout << ((aux[0] == 108) ? '1' : '.');
		cout << ((aux[1] == 108) ? '2' : '.');
		jug = tColor(int(jug) + 1);
		setColor(jug);
		cout << "               ";
		casilla += 17;
	}
	cout << endl;
	casilla = 0;
	jug = Amarillo;
	setColor(jug);
	while (casilla < NUM_Casillas)
	{
		int aux[4];
		for (int x = 0; x < 4; x++)
		{
			aux[x] = juego.jugadores[jug].fichas[x] - cambioMostrar(jug);
		}
		cout << ((aux[2] == 108) ? '3' : '.');
		cout << ((aux[3] == 108) ? '4' : '.');
		jug = tColor(int(jug) + 1);
		setColor(jug);
		cout << "               ";
		casilla += 17;
	}
	cout << endl
		<< endl;
	setColor(Gris);
}
void mostrarTurnos(tJuego& juego)
{
	for (int f = 0; f < NUM_Fichas; f++)
	{
		cout << juego.turno[f];
	}
	cout << endl;
}
void mostrarFichas(tJuego& juego)
{
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		for (int f = 0; f < NUM_Fichas; f++)
		{
			cout << juego.jugadores[i].fichas[f] << '\t';
		}
		cout << endl;
	}
}
void mostrarColorCasillas(tJuego& juego)
{
	cout << "4=Gris" << endl;
	for (int i = 0; i < NUM_Casillas; i++)
	{
		cout << juego.casillas.calle1[i];
	}
	cout << " => calle1" << endl;
	for (int i = 0; i < NUM_Casillas; i++)
	{
		cout << juego.casillas.calle2[i];
	}
	cout << " => calle2" << endl;
}
void mostrarPuedoMover(tJuego& juego, bool sePuedeMover[])
{
	for (int i = 0; i < NUM_Fichas; i++)
	{
		if (sePuedeMover[i] == true)
		{
			int aquiVa = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + juego.dado;
			if (aquiVa >= 68 && aquiVa < 100) { aquiVa = aquiVa - 68; }
			if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] <= zanataJugador(juego.turno[juego.turnoActual]) && aquiVa > zanataJugador(juego.turno[juego.turnoActual])) {
				aquiVa = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + meta[juego.turno[juego.turnoActual]] - zanataJugador(juego.turno[juego.turnoActual]) - 8 + juego.dado;
			}
			cout << "La ficha " << i + 1 << " que esta en la casilla " << juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] << " va a " << aquiVa << endl;
		}
	}
}
void setColor(tColor color)
{
	switch (color)
	{
	case Azul:
		cout << "\x1b[94;107m";
		break;
	case Verde:
		cout << "\x1b[92;107m";
		break;
	case Rojo:
		cout << "\x1b[31;107m";
		break;
	case Amarillo:
		cout << "\x1b[33;107m";
		break;

	case Gris:
	case Ninguno:
		cout << "\x1b[90;107m";
		break;
	}
}
void tresPuntos()
{

	cout << ".";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << "\b\b\b   ";
	Sleep(100);
	cout << "\b\b\b.";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << "\b\b\b   ";
	Sleep(100);
	cout << "\b\b\b.";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << endl;

}
void animacionAleatorio()
{
	int num;
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(80);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(180);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(200);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(240);
	cout << "\b";
	num = 1 + rand() % (7 - 1);
	cout << num;
	Sleep(320);
	cout << "\b";


}
void pausa()
{
	cout << "Pulsa Intro para tirar el dado:";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int cambioMostrar(tColor jug)
{
	int aux = 0;
	aux = meta[jug] - 108;
	return aux;
}
string colorACadena(tColor color)
{
	if (color == Rojo)
	{
		return "Rojo";
	}
	if (color == Amarillo)
	{
		return "Amarillo";
	}
	if (color == Azul)
	{
		return "Azul";
	}
	if (color == Verde)
	{
		return "Verde";
	}
}
//Funciones del dado:
int tirardado() //---Tirada Dado aleatorio
{
	int num;
	num = 1 + rand() % (7 - 1);
	pausa();
	cout << "Has sacado un ";
	animacionAleatorio();
	cout << num << endl;
	Sleep(1000);
	return num;
}
int tirardadousuario(tJuego& juego) //---Elegir dado
{
	int num;

	cout << "Usuario " << juego.ColorJugador[juego.turno[juego.turnoActual]] + 1 << " introduce la tirada del dado: ";
	cin >> num;

	return num;
}
//Funciones para fichas:
int cuantasEn(const int fichas[NUM_Fichas], int casilla)
{
	int num = 0;

	for (int i = 0; i < NUM_Fichas; i++)
		if (fichas[i] == casilla)
			num++;

	return num;
}
int primeraEn(const int fichas[NUM_Fichas], int casilla)
{
	int result = -1;
	for (int i = 0; i < NUM_Fichas; i++)
	{
		if (fichas[i] == casilla)
		{
			result = i;
		}
	}
	return result;
}
int segundaEn(const int fichas[NUM_Fichas], int casilla)
{
	int result = -1;
	for (int i = NUM_Fichas - 1; i >= 0; i--)
	{
		if (fichas[i] == casilla)
		{
			result = i;
		}
	}
	return result;
}
int contadorFichasEn(tJuego& juego, int casilla)
{
	int num = 0;

	for (int f = 0; f < NUM_Fichas; f++)
	{
		for (int i = 0; i < NUM_Jugadores; i++)
		{
			if (juego.jugadores[i].fichas[f] == casilla)
			{
				num++;
			}
		}
	}

	return num;
}
//Funciones para casillas:
int zanataJugador(tColor jugador)
{
	switch (jugador)
	{
	case 0:
		return 68;
		break;

	case 1:
		return 17;
		break;

	case 2:
		return 34;
		break;

	case 3:
		return 51;
		break;

	default:
		return 0;
	}
}
int salidaJugador(tColor jugador)
{
	switch (jugador)
	{
	case 0:
		return 5;
		break;
	case 1:
		return 22;
		break;
	case 2:
		return 39;
		break;
	case 3:
		return 56;
		break;
	default:
		return 0;
	}
}
bool esSeguro(int casilla)
{
	switch (casilla % 17) //--Los multiplos de 17 a partir de 0 5 y 12 son casillas seguras
	{
	case 0:
		return true;
		break;
	case 5:
		return true;
		break;
	case 12:
		return true;
		break;
	default:
		return false;
	}
}
void reajustarColores(tJuego& juego, int casillaAnterior, int casillaPosterior)
{
	int antes = 0;
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		antes = antes + cuantasEn(juego.jugadores[i].fichas, casillaAnterior);
	}
	if (antes == 1) {
		if (casillaAnterior < 100) {

			if (juego.casillas.calle2[casillaAnterior] != (juego.turno[juego.turnoActual]))
			{
				juego.casillas.calle1[casillaAnterior] = juego.casillas.calle2[casillaAnterior];
				juego.casillas.calle2[casillaAnterior] = Ninguno;
			}
			else
			{
				juego.casillas.calle2[casillaAnterior] = Ninguno;
			}

		}
	}
	else
	{
		if (casillaAnterior < 100) { juego.casillas.calle1[casillaAnterior] = Ninguno; }
	}
	int despues = 0;
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		despues = despues + cuantasEn(juego.jugadores[i].fichas, casillaPosterior);
	}
	if (despues > 1)
	{
		if (casillaPosterior < 100) {
			juego.casillas.calle2[casillaPosterior] = juego.turno[juego.turnoActual];
		}
	}
	else
	{
		if (casillaPosterior < 100) {
			juego.casillas.calle1[casillaPosterior] = juego.turno[juego.turnoActual];
		}
	}

}
//Funciones del turno: 
void ejecutarturno(tJuego& juego)
{
	//mostrarFichas(juego);
	bool pasaTurno = false;

	cout << "Turno del " << colorACadena(juego.turno[juego.turnoActual]) << endl;
	while (pasaTurno == false)
	{
		pasaTurno = true;

		if (juego.proximasTiradas[juego.tiradaActual] == 0) {
			//juego.dado = tirardado();
			juego.dado = tirardadousuario(juego);
		}
		else {
			juego.dado = juego.proximasTiradas[juego.tiradaActual];
			juego.proximasTiradas[juego.tiradaActual] = 0;
			juego.tiradaActual++;
		}

		switch (juego.dado)
		{
		case 0:
			exit(1);
			break;
		case 5:
			procesa5(juego, pasaTurno);
			break;
		case 6:
			procesa6(juego, pasaTurno);
			break;
		default:
			jugar(juego);
		}
		if (juego.nSeises > 2)
		{
			mostrar(juego);
			cout << "Pierdes Turno" << endl;
			Sleep(300);
		}
		else if (pasaTurno == false)
		{
			mostrar(juego);
			cout << "El " << colorACadena(juego.turno[juego.turnoActual]) << " vuelve a tirar" << endl;
		}
		else { mostrar(juego); }

	}
	if (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, meta[juego.turno[juego.turnoActual]]) > 3) { ganar[juego.turnoActual] = true; juego.puesto++; cout << "El jugador " << colorACadena(juego.turno[juego.turnoActual]) << " ha ganado y ha quedado " << juego.puesto << circulito << endl; }
	turnoSiguiente(juego);

}
void turnoSiguiente(tJuego& juego)
{
	juego.turnoActual++;
	if (juego.puesto == 4) { Jugando = false; }
	else if (juego.turnoActual > (NUM_Fichas - 1))
	{
		juego.turnoActual = 0;
	}
	while (ganar[juego.turnoActual] && Jugando) { juego.turnoActual++; }
	if (juego.turnoActual > (NUM_Fichas - 1))
	{
		juego.turnoActual = 0;
	}

	if (Jugando) {
		cout << "Pasando al siguiente turno";
		tresPuntos();
	}
	else {
		cout << "La partida ha finalizado" << endl;
	}

}
void procesa5(tJuego& juego, bool pasaTurno)
{
	//mostrarFichas(juego);
	int cuantasEnCasa = cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, -1);
	int casilla = salidaJugador(juego.turno[juego.turnoActual]);
	int cuantasEnSalida = cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, casilla);

	if (cuantasEnCasa > 0 && cuantasEnSalida < 2)
	{
		saleFicha(juego, cuantasEnSalida);
	}
	else
	{
		jugar(juego);
	}
}
void procesa6(tJuego& juego, bool& pasaTurno)
{
	pasaTurno = false;
	juego.nSeises = juego.nSeises + 1;

	if (juego.nSeises > 2 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[juego.ultimaFichaMovida] != -1)
	{
		pasaTurno = true;

		int casillaAnterior = juego.jugadores[juego.turno[juego.turnoActual]].fichas[juego.ultimaFichaMovida];
		int casillaPosterior = -1;
		juego.jugadores[juego.turno[juego.turnoActual]].fichas[juego.ultimaFichaMovida] = -1;
		reajustarColores(juego, casillaAnterior, casillaPosterior);


		cout << "Ultima Ficha a Casa" << endl;
	}
	else
	{
		int cuantasEnCasa = cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, -1);
		if (cuantasEnCasa == 0)
		{
			juego.dado = 7;
		}
		if ((cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, juego.jugadores[juego.turno[juego.turnoActual]].fichas[0]) > 1 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[0] != -1) || (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, juego.jugadores[juego.turno[juego.turnoActual]].fichas[1]) > 1 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[1] != -1) || (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, juego.jugadores[juego.turno[juego.turnoActual]].fichas[2]) > 1 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[2] != -1) || (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, 4) > 1 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[3] != -1))
		{
			abrirPuente(juego);
		}
		else
		{
			jugar(juego);
		}
	}
}
void jugar(tJuego& juego)
{
	bool sePuedeMover[NUM_Jugadores];
	puedeMover(juego, sePuedeMover);
	if (sePuedeMover[0] == false && sePuedeMover[1] == false && sePuedeMover[2] == false && sePuedeMover[3] == false)
	{
		cout << "No puedes mover ninguna ficha" << endl;
		Sleep(500);
	}
	else
	{
		mover(juego, sePuedeMover);
	}
}
//Funciones relacionadas con el movimiento de fichas:
void mover(tJuego& juego, bool sePuedeMover[])
{
	int casillaAnterior;
	int casillaPosterior;
	bool valido = false;
	int fichaParaMover;
	while (valido == false)
	{
		mostrarPuedoMover(juego, sePuedeMover);
		cout << "Que ficha quieres mover? ";
		cin >> fichaParaMover;
		fichaParaMover--;
		if (fichaParaMover > 3)
		{
			valido = false;
		}
		else
		{
			valido = sePuedeMover[fichaParaMover];
		}
		if (valido == false)
		{
			cout << "Ficha no valida" << endl;
		}
	}
	casillaAnterior = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover];
	juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] + juego.dado;
	casillaPosterior = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover];
	entrarZanata(juego, fichaParaMover, casillaAnterior, casillaPosterior);
	if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] > 67 && juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] < 100)
	{
		juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] - 68;
	}
	casillaPosterior = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover];
	reajustarColores(juego, casillaAnterior, casillaPosterior);
	cout << "Moviendo ficha";
	Sleep(100);
	tresPuntos();
	cout << "Movimiento realizado" << endl;
	Sleep(500);
	premio(juego, sePuedeMover, fichaParaMover);
	juego.ultimaFichaMovida = fichaParaMover;
}
void puedeMover(tJuego& juego, bool sePuedeMover[])
{
	for (int i = 0; i < NUM_Fichas; i++)
	{
		sePuedeMover[i] = true;
		int proximaCasilla = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + juego.dado;
		if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] == -1 || meta[juego.turno[juego.turnoActual]] < proximaCasilla || (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] < puente(juego, proximaCasilla, i) && puente(juego, proximaCasilla, i) <= proximaCasilla))
		{
			sePuedeMover[i] = false;
		}
	}
}
void saleFicha(tJuego& juego, int cuantasEnSalida)
{
	int aux = segundaEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, -1);
	cout << "Sale la ficha " << aux + 1 << endl;
	juego.jugadores[juego.turno[juego.turnoActual]].fichas[aux] = salidaJugador(juego.turno[juego.turnoActual]);
	premio(juego, verdad, aux);
	cuantasEnSalida = contadorFichasEn(juego, salidaJugador(juego.turno[juego.turnoActual]));
	if (juego.casillas.calle1[salidaJugador(juego.turno[juego.turnoActual])] != Ninguno)
	{
		juego.casillas.calle2[salidaJugador(juego.turno[juego.turnoActual])] = Ninguno;
	}
	else
	{
		juego.casillas.calle1[salidaJugador(juego.turno[juego.turnoActual])] = juego.turno[juego.turnoActual];
	}
	if (cuantasEnSalida > 1)
	{
		juego.casillas.calle2[salidaJugador(juego.turno[juego.turnoActual])] = juego.turno[juego.turnoActual];
	}
	else
	{
		juego.casillas.calle1[salidaJugador(juego.turno[juego.turnoActual])] = juego.turno[juego.turnoActual];
	}

	//mostrarFichas(juego);

}
void comerFicha(tJuego& juego, bool sePuedeMover[], int fichaParaMover, int i, int f)
{
	juego.dado = 20;
	int casillaAnterior = juego.jugadores[i].fichas[f];
	juego.jugadores[i].fichas[f] = -1;

	juego.casillas.calle1[juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover]] = juego.casillas.calle2[juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover]];
	juego.casillas.calle2[juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover]] = Ninguno;

	jugar(juego);
}
void premio(tJuego& juego, bool sePuedeMover[], int fichaParaMover)
{

	if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] == meta[juego.turno[juego.turnoActual]])
	{
		mostrar(juego);
		juego.dado = 10;
		jugar(juego);
		if (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, meta[juego.turno[juego.turnoActual]]) == 4) { /*ganarPartida();*/ }
	}
	for (int i = 0; i < NUM_Jugadores; i++)
	{
		if (i != juego.turno[juego.turnoActual])
		{
			for (int f = 0; f < NUM_Fichas; f++)
			{
				if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] == juego.jugadores[i].fichas[f])
				{
					if (esSeguro(juego.jugadores[i].fichas[f]) == false || (salidaJugador(juego.turno[juego.turnoActual])) && contadorFichasEn(juego, salidaJugador(juego.turno[juego.turnoActual])) > 2)
					{
						comerFicha(juego, sePuedeMover, fichaParaMover, i, f);
						mostrar(juego);
					}
				}
			}
		}
	}
}
void entrarZanata(tJuego& juego, int fichaParaMover, int casillaAnterior, int casillaPosterior)
{
	if (casillaAnterior <= zanataJugador(juego.turno[juego.turnoActual]) && casillaPosterior > zanataJugador(juego.turno[juego.turnoActual]))
	{
		juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] = juego.jugadores[juego.turno[juego.turnoActual]].fichas[fichaParaMover] + meta[juego.turno[juego.turnoActual]] - zanataJugador(juego.turno[juego.turnoActual]) - 8;
	}
}
int puente(tJuego& juego, int proximaCasilla, int FICHA)
{
	int aux = 0;
	bool daLaVuelta = false;

	if (proximaCasilla > 100) {
		return 30000;
	}

	if (proximaCasilla > 68)
	{
		aux = proximaCasilla - 68;
		proximaCasilla = 68;
		daLaVuelta = true;
	}
	for (int i = juego.jugadores[juego.turno[juego.turnoActual]].fichas[FICHA] + 1; i <= proximaCasilla; i++)
	{
		if (contadorFichasEn(juego, i) == 2) { return i; }
	}


	if (daLaVuelta)
	{
		for (int i = 0; i <= aux; i++)
		{
			if (contadorFichasEn(juego, i) == 2) { return i + 68; }
		}
	}
	return 300000;
}
void abrirPuente(tJuego& juego)
{
	int puente1 = 0;
	int puente2 = 0;
	for (int i = 0; i < 68; i++)
	{
		if (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, i) == 2) { puente2 = i; }
	}
	for (int i = 0; i < puente2; i++)
	{
		if (cuantasEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, i) == 2) { puente1 = i; }
	}
	if (puente1 != 0)
	{
		int mayorIndicePuente1 = 0;
		int mayorIndicePuente2 = 0;
		bool sePuedeAbrir[4] = { false,false,false,false };
		mayorIndicePuente1 = primeraEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, puente1);
		mayorIndicePuente2 = primeraEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, puente2);
		sePuedeAbrir[mayorIndicePuente1] = true;
		sePuedeAbrir[mayorIndicePuente2] = true;
		int i = mayorIndicePuente1;
		int proximaCasilla = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + juego.dado;
		int primerpuente = puente(juego, proximaCasilla, i);
		if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] == -1 || meta[juego.turno[juego.turnoActual]] < proximaCasilla || (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] < primerpuente && primerpuente <= proximaCasilla))
		{
			sePuedeAbrir[mayorIndicePuente1] = false;
		}
		i = mayorIndicePuente2;
		proximaCasilla = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + juego.dado;
		primerpuente = puente(juego, proximaCasilla, i);
		if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] == -1 || meta[juego.turno[juego.turnoActual]] < proximaCasilla || (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] < primerpuente && primerpuente <= proximaCasilla))
		{
			sePuedeAbrir[mayorIndicePuente2] = false;
		}

		if (sePuedeAbrir[mayorIndicePuente1] == false && sePuedeAbrir[mayorIndicePuente2] == false)
		{
			cout << "No puedes abrir ningun puente" << endl;
			Sleep(500);
			jugar(juego);
		}
		else
		{
			mover(juego, sePuedeAbrir);
		}
	}
	else
	{
		int mayorIndicePuente1 = 0;
		bool sePuedeAbrir[4] = { false,false,false,false };
		mayorIndicePuente1 = primeraEn(juego.jugadores[juego.turno[juego.turnoActual]].fichas, puente2);
		sePuedeAbrir[mayorIndicePuente1] = true;

		int i = mayorIndicePuente1;
		int proximaCasilla = juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] + juego.dado;
		int primerpuente = puente(juego, proximaCasilla, i);
		if (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] == -1 || meta[juego.turno[juego.turnoActual]] < proximaCasilla || (juego.jugadores[juego.turno[juego.turnoActual]].fichas[i] < primerpuente && primerpuente <= proximaCasilla))
		{
			sePuedeAbrir[mayorIndicePuente1] = false;
		}

		if (sePuedeAbrir[mayorIndicePuente1] == false)
		{
			cout << "No puedes abrir ningun puente" << endl;
			Sleep(500);
			jugar(juego);
		}
		else
		{
			mover(juego, sePuedeAbrir);
		}


	}

}

