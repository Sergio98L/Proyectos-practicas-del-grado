//Parchis 22 noviembre Ignacio Doménech y Sergio Domínguez
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef enum { Rojo, Verde, Amarillo, Azul } tColor;

tColor escogercolor1(tColor tipo1);
tColor escogercolor2(tColor tipo1, tColor tipo2);

char letra(tColor color);
string colorACadena(tColor color);

int tirardadousuario();//--No aleatorio
int tirardado();//--Aleatorio

bool casillasegura(int Cjugador1);

bool ganajugador1(int Cjugador1, bool NOPartidaAcabada, int primero, string color1);
bool ganajugador2(int Cjugador2, bool NOPartidaAcabada, int segundo, string color2);

void mostrartablero(int Cjugador1, int Cjugador2, int casilla, char letra1, char letra2, bool J1Casa, bool J2Casa);

int main()
{
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------###########################################-----------------------------" << endl;
    cout << "-----------------------------#### Bienvenido la version 1 del parchis ####----------------------------" << endl;
    cout << "------------------------------###########################################-----------------------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << "--------------------------------By Ignacio Domenech y Sergio Dominguez--------------------------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    int nseises = 0; //---Numero de seises seguidos
    int primero = 0; //---Primer jugador
    int segundo = 0; //---Segundo jugador
    int Cjugador1 = 5; //---Casilla jugador1
    int Cjugador2 = 5; //---Casilla jugador2
    int casilla = 0; //---Casilla para representar el tablero
    int salidaj1 = 0; //---Casilla de salida del jugador1
    int salidaj2 = 0; //---Casilla de salida del jugador2
    int victoriaj1 = 0; //---Zanata del jugador1
    int victoriaj2 = 0; //---Zanata del jugador2
    int cant1 = 0; //---Casilla Anterior jugador 1
    int cant2 = 0; //---Casilla Anterior jugador 2
    int Turno = 0; //si es igual a 0 jugador 1, si es igual a 1 jugador 2, si es igual a 2 jugador 3 y si es igual a 3 jugador 4
    int Ndado = 0; //Número de dado




    char letra1; //---Letra correspondiente al color que elija el usuario1
    char letra2; //---Letra correspondiente al color que elija el usuario2

    string color1; //---Color elegido por el usuario1
    string color2; //---Color elegido por el usuario2


    bool NOPartidaAcabada = true;
    bool J1Casa = false; //--False si esta dentro de casa, true si esta fuera
    bool J2Casa = false; //--False si esta dentro de casa, true si esta fuera

    tColor tipo1 = Amarillo;
    tColor tipo2 = Azul;
    tColor color = Amarillo;

    tipo1 = escogercolor1(tipo1);
    tipo2 = escogercolor2(tipo1, tipo2);

    /*----------------------Asignar los valores correspondientes segun el color de la casilla de salida, Zanata y letra.----------------------*/

    if (tipo1 == Amarillo) { salidaj1 = 5; Cjugador1 = 5; victoriaj1 = 68; primero = 3;  /* letra1 = 'M'; color1 = "Amarillo"; */ }
    else if (tipo1 == Rojo) { salidaj1 = 39; Cjugador1 = 39; victoriaj1 = 34; primero = 1;  /* letra1 = 'R'; color1 = "Rojo";*/ }
    else if (tipo1 == Azul) { salidaj1 = 22; Cjugador1 = 22; victoriaj1 = 17; primero = 4;  /* letra1 = 'A'; color1 = "Azul"; */ }
    else if (tipo1 == Verde) { salidaj1 = 56; Cjugador1 = 56; victoriaj1 = 51; primero = 2;   /* letra1 = 'V'; color1 = "Verde";*/ }
    else { cout << "el programa ha fallado con la eleccion de colores" << endl; return 0; }

    if (tipo2 == Amarillo) { salidaj2 = 5; Cjugador2 = 5; victoriaj2 = 68; segundo = 3;   /* letra2 = 'M'; color2 = "Amarillo"; */ }
    else if (tipo2 == Rojo) { salidaj2 = 39; Cjugador2 = 39; victoriaj2 = 34; segundo = 1;  /* letra2 = 'R'; color2 = "Rojo";*/ }
    else if (tipo2 == Azul) { salidaj2 = 22; Cjugador2 = 22; victoriaj2 = 17; segundo = 4;   /* letra2 = 'A'; color2 = "Azul";*/ }
    else if (tipo2 == Verde) { salidaj2 = 56; Cjugador2 = 56; victoriaj2 = 51; segundo = 2;   /* letra2 = 'V';	color2 = "Verde";*/ }
    else { cout << "el programa ha fallado con la eleccion de colores" << endl; return 0; }

    /*---Hemos comentado el caracter y el string porque el ejercicio pide que realicemos una función particular para cada una---*/

    color = tipo1;
    letra1 = letra(color);
    color1 = colorACadena(color);

    color = tipo2;
    letra2 = letra(color);
    color2 = colorACadena(color);


    /*-----------------------------------------------------------------------------------------------------------------------------------------*/

    if (segundo < primero) { Turno = 1; cout << "Empieza el " << color2 << endl; }//---Ver quien empieza
    else { Turno = 0; cout << "Empieza el " << color1 << endl; }


    while (NOPartidaAcabada)  //---Bucle principal de la partida---
    {


        while (Turno == 0 && nseises < 3)//---Turno Jugador 1 
        {
            if (nseises == 0) { cout << "Turno del jugador " << primero << " con color " << color1 << " :" << endl; }
            if (nseises == 1) { cout << "Vuelve a tirar" << endl; }
            if (nseises == 2) { cout << "Vuelve a tirar" << endl; }
            Turno++;
            Ndado = tirardado();//Cambiar variable tirardado por tirardadousuario para elegir la tirada del dado manualmente.

            cant1 = Cjugador1;

            if (J1Casa)
            {
                Cjugador1 = Cjugador1 + Ndado;

                if (cant1 < victoriaj1 && victoriaj1 < Cjugador1)//Comprobamos si la casilla de victoria se encuentra entre la casilla anterior del jugador y la casilla posterior a tirar el dado, esto nos permite saber si el jugador se pasa de la meta.
                {
                    Cjugador1 = Cjugador1 - Ndado;
                    cout << "No has avanzado porque te pasas de la meta " << endl;
                }

                else if (victoriaj1 == Cjugador1) {
                    NOPartidaAcabada = ganajugador1(Cjugador1, NOPartidaAcabada, primero, color1);
                }

                if (Cjugador1 > 67)//---Tablero Circular
                {
                    Cjugador1 = Cjugador1 - 67;
                }

                cout << "Casilla " << color1 << " : " << Cjugador1 << endl;
            }
            if (Ndado == 5 && J1Casa == false) //---Comprobar si sale de casa y mover ficha   
            {

                J1Casa = true;
                cout << "La ficha " << color1 << " ha salido de casa" << endl;

                if (Cjugador1 == Cjugador2) {

                    Cjugador2 = salidaj2;
                    J2Casa = false;
                    Cjugador1 = Cjugador1 + 20;
                    cout << "La ficha " << color1 << " se come a " << color2 << " y avanza 20 casillas " << endl;
                    cout << "Casilla " << color1 << " : " << Cjugador1 << endl;

                }

            }

            if (J1Casa == false) //---Comprobar si esta en casa
            {
                cout << "La ficha " << color1 << " esta en casa" << endl;
            }

            if (Ndado == 6)
            {
                nseises = nseises + 1;
                if (nseises < 3) { Turno--; }
                else { J1Casa = false; Cjugador1 = salidaj1; cout << "vuelves a casa" << endl; }
            }

            casilla = Cjugador1;
            if (Cjugador1 == Cjugador2 && J1Casa && J2Casa)//---Comerse Ficha
            {
                if (casillasegura(casilla))//---Comprobar que jugador 1 esta en casilla segura
                {
                    cout << color1 << " no puede comer " << color2 << " porque esta en una casilla segura por lo que vuelves a la casilla anterior" << endl;
                    Cjugador1 = Cjugador1 - Ndado;
                    cout << "Casilla " << color1 << " : " << Cjugador1 << endl;
                }
                else
                {
                    Cjugador2 = salidaj2;
                    J2Casa = false;
                    Cjugador1 = Cjugador1 + 20;
                    cout << "La ficha " << color1 << " se come a " << color2 << " y avanza 20 casillas " << endl;
                    cout << "Casilla " << color1 << " : " << Cjugador1 << endl;
                }

            }


        }

        mostrartablero(Cjugador1, Cjugador2, casilla, letra1, letra2, J1Casa, J2Casa);
        nseises = 0; //---Como ha acabado el turno le devolvemos el valor 0

        while (Turno == 1 && nseises < 3 && NOPartidaAcabada)//---Turno Jugador 2
        {
            if (nseises == 0) { cout << "Turno del jugador " << segundo << " con color " << color2 << " :" << endl; }
            if (nseises == 1) { cout << "Vuelve a tirar" << endl; }
            if (nseises == 2) { cout << "Vuelve a tirar" << endl; }
            Turno--;
            Ndado = tirardado();//Cambiar variable tirardado por tirardadousuario para elegir la tirada del dado manualmente.

            cant2 = Cjugador2;

            if (J2Casa)
            {
                Cjugador2 = Cjugador2 + Ndado;

                if (cant2 < victoriaj2 && victoriaj2 < Cjugador2) //Comprobamos si la casilla de victoria se encuentra entre la casilla anterior del jugador y la casilla posterior a tirar el dado, esto nos permite saber si el jugador se pasa de la meta.
                {
                    Cjugador2 = Cjugador2 - Ndado;
                    cout << "No has avanzado porque te pasas de la meta " << endl;
                }
                else if (victoriaj2 == Cjugador2) {
                    NOPartidaAcabada = ganajugador2(Cjugador2, NOPartidaAcabada, segundo, color2);
                }

                if (Cjugador2 > 67)//---Finalizar partida rojo
                {
                    Cjugador2 = Cjugador2 - 67;
                }

                cout << "Casilla " << color2 << " : " << Cjugador2 << endl;
            }

            if (Ndado == 5 && J2Casa == false) //---Comprobar si sale de casa y mover ficha   
            {
                J2Casa = true;
                cout << "La ficha " << color2 << " ha salido de casa" << endl;

                if (Cjugador1 == Cjugador2)
                {
                    Cjugador1 = salidaj1;
                    J1Casa = false;
                    Cjugador2 = Cjugador2 + 20;
                    cout << "La ficha " << color2 << " se come a " << color1 << " y avanza 20 casillas " << endl;
                    cout << "Casilla " << color2 << " : " << Cjugador2 << endl;
                }


            }

            if (J2Casa == false) //---Comprobar si esta en casa
            {
                cout << "La ficha " << color2 << " esta en casa" << endl;
            }

            if (Ndado == 6)
            {
                nseises = nseises + 1;
                if (nseises < 3) { Turno++; }
                else { J2Casa = false; Cjugador2 = salidaj2; cout << "vuelves a casa" << endl; }
            }

            casilla = Cjugador2;
            if (Cjugador1 == Cjugador2 && J2Casa && J1Casa)//---Comerse Ficha
            {
                if (casillasegura(casilla))//---Comprobar que jugador 2 esta en casilla segura
                {
                    cout << color2 << " no puede comer " << color1 << " porque esta en una casilla segura por lo que vuelves a la casilla anterior" << endl;
                    Cjugador2 = Cjugador2 - Ndado;
                    cout << "Casilla " << color2 << " : " << Cjugador2 << endl;
                }
                else
                {
                    Cjugador1 = salidaj1;
                    J1Casa = false;
                    Cjugador2 = Cjugador2 + 20;
                    cout << "La ficha " << color2 << " se come a " << color1 << " y avanza 20 casillas " << endl;
                    cout << "Casilla " << color2 << " : " << Cjugador2 << endl;
                }
            }
        }
        mostrartablero(Cjugador1, Cjugador2, casilla, letra1, letra2, J1Casa, J2Casa);
        nseises = 0;//---Como ha acabado el turno le devolvemos el valor 0
    }
}


/*-------------------------------------------------------------------------------------------------------------------
----------------------------------------------------FUNCIONES--------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------*/



tColor escogercolor1(tColor tipo1)
{
    int f1 = 0;

    while (f1 == 0) {
        int a = 0;
        cout << "1 = Rojo, 2 = Verde, 3 = Amarillo y 4 = Azul" << endl;
        cout << "Usuario 1 escoge un color: ";
        cin >> a;
        tColor tipo1 = tColor(a - 1);
        if (a > 4) { cout << "el color no es valido vuelve a intentarlo" << endl; }
        else {
            f1++;
            return tipo1;
        }
    }
}



tColor escogercolor2(tColor tipo1, tColor tipo2)
{
    int f2 = 0;
    while (f2 == 0) {
        int a = 0;
        cout << "Usuario 2 escoge un color: ";
        cin >> a;
        tColor tipo2 = tColor(a - 1);
        if (tipo1 == tipo2) {
            cout << "este color lo ha escogido otro jugador" << endl;
        }
        else if (a > 4)
        {
            cout << "el color no es valido vuelve a intentarlo" << endl;;
        }
        else {
            f2++;
            return tipo2;
        }
    }
}
char letra(tColor color) {
    if (color == Rojo) { return 'R'; }
    if (color == Amarillo) { return 'M'; }
    if (color == Azul) { return 'A'; }
    if (color == Verde) { return 'V'; }

}

string colorACadena(tColor color) {
    if (color == Rojo) { return "Rojo"; }
    if (color == Amarillo) { return "Amarillo"; }
    if (color == Azul) { return "Azul"; }
    if (color == Verde) { return "Verde"; }

}


int tirardadousuario()//---Elegir dado
{
    int num;
    cout << "Introduce la tirada del dado: ";
    cin >> num;

    return num;
}

int tirardado()//---Tirada Dado aleatorio
{
    int num;
    num = 1 + rand() % (7 - 1);
    cout << "has sacado un " << num << endl;

    return num;
}

void mostrartablero(int Cjugador1, int Cjugador2, int casilla, char letra1, char letra2, bool J1Casa, bool J2Casa)
{
    for (int i = 0; i < 68; i++) { cout << i / 10; }
    cout << endl;
    for (int i = 0; i < 68; i++) { cout << i % 10; }
    cout << endl;
    for (int casilla = 0; casilla < 68; casilla++) {
        if (casillasegura(casilla) == true) { cout << 'O'; }
        else { cout << '-'; }
    }
    cout << endl;
    for (int i = 0; i < 68; i++) {
        if (i == Cjugador1 && J1Casa) { cout << letra1; }
        else { cout << ' '; }
    }
    cout << endl;
    for (int casilla = 0; casilla < 68; casilla++) {
        if (casillasegura(casilla) == true) { cout << 'O'; }
        else { cout << '-'; }
    }
    cout << endl;
    for (int i = 0; i < 68; i++) {
        if (i == Cjugador2 && J2Casa) { cout << letra2; }
        else { cout << ' '; }
    }
    cout << endl;
}

bool ganajugador2(int Cjugador2, bool NOPartidaAcabada, int segundo, string color2)
{
    cout << endl;
    cout << "!!!!!El jugador " << segundo << " con color " << color2 << " ha ganado la partida!!!!!" << endl;
    NOPartidaAcabada = false;
    return NOPartidaAcabada;
}

bool ganajugador1(int Cjugador1, bool NOPartidaAcabada, int primero, string color1)
{
    cout << endl;
    cout << "!!!!!El jugador " << primero << " con color " << color1 << " ha ganado la partida!!!!!" << endl;
    NOPartidaAcabada = false;
    return NOPartidaAcabada;
}
bool casillasegura(int casilla)
{
    switch (casilla % 17)//--Los multiplos de 17 a partir de 0 5 y 12 son casillas seguras
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