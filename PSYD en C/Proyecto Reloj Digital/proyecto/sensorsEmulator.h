/*-------------------------------------------------------------------
**
**  Fichero:
**    sensorsEmulator.h  27/6/2023
**
**    (c) J.M. Mendias
**    Programaci�n de Sistemas y Dispositivos
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las definiciones de los prototipos de las funciones
**    de dos generadores de interrupciones de periodicidad variable
**    que emulen el tren de pulsos generado por sensores que
**    detectan el pulso y los pasos efectuados al caminar
**
**  Notas de dise�o:
**    - Este emulador hace uso en exclusividad del TIMER3, TIMER3 y UART0
** 
**-----------------------------------------------------------------*/

#ifndef __SENSORSEMULATOR_H__
#define __SENSORSEMULATOR_H__

#include <common_types.h>

#define BIT_BEATEMULATOR BIT_TIMER3
#define BIT_STEPEMULATOR BIT_TIMER2

/*
** Instala la funci�n isrBeat e isrStep como RTI de interrupciones generadas por
** el emulador de sensores y arranca su funcionalidad.
**
** Tras ejecutar esta funci�n, se generan periodicamente interrupciones a frecuencias
** dadas que deben ser servidas por la RTI indicadas.
**
** Las frecuencias de interrupcion puede modificarse independientementne en tiempo
** de ejecuci�n interactuando con un menu accesible por la UART0
*/
void startSensorsEmulator( void (*isrBeat)(void), void (*isrStep)(void), uint8 beatPerMin, uint8 stepPerMin );

#endif 
