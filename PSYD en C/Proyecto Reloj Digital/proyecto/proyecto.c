
//Autor Sergio Dominguez Alcala
#include <s3c44b0x.h>
#include <s3cev40.h>
#include <common_types.h>
#include <leds.h>
#include <system.h>
#include <uart.h>
#include <timers.h>
#include <keypad.h>
#include <pbs.h>
#include <lcd.h>
#include <rtc.h>
#include <ts.h>
#include "sensorsEmulator.h"


/*
** Direcciones en donde se encuentran cargados los BMP tras la ejecucion en
** la consola del depurador los comandos:
**   cd <ruta>
**   source load_bmp.txt
*/
#define ARBOL      ((uint8 *)0x0c210000)
#define PADRINO    ((uint8 *)0x0c220000)
#define PICACHU    ((uint8 *)0x0c230000)
#define HARRY      ((uint8 *)0x0c240000)
#define CHAPLIN    ((uint8 *)0x0c250000)
#define PULP       ((uint8 *)0x0c260000)
#define MAPA       ((uint8 *)0x0c270000)

#define QM 12
#define FADD(a,b) ((a)+(b))
#define FSUB(a,b) ((a)-(b))
#define FMUL(a,b,q) (((a)*(b))>>(q))
#define FDIV(a,b,q) (((a)<<(q))/(b))
#define TOFIX(t,d,q) ((t)((d)*(double)(1ULL<<(q))))
typedef int32 fix32;
typedef int16 fix16;
#define PESO_CORPORAL 70.0  // En kilogramos

static void beatHandler( void ) __attribute__ ((interrupt ("IRQ")));
static void stepHandler( void ) __attribute__ ((interrupt ("IRQ")));
void isr_keypad( void ) __attribute__ ((interrupt ("IRQ")));
void isr_pbs( void ) __attribute__ ((interrupt ("IRQ")));
void isr_timer0( void ) __attribute__ ((interrupt ("IRQ")));
void isr_tick( void ) __attribute__ ((interrupt ("IRQ")));
void isr_timer0( void ) __attribute__ ((interrupt ("IRQ")));

/*******************************************************************/
//Flags para las interrupciones

volatile static boolean newBeat = FALSE;
volatile static boolean newStep = FALSE;
volatile boolean flagTimer0 = FALSE;
volatile boolean flagKeypad = FALSE;
volatile boolean flagPbs = FALSE;
volatile boolean flagRtc = FALSE;
/*******************************************************************/

volatile boolean sistemaEncendido = FALSE;
volatile boolean pintarMenuPrincipal = TRUE;
rtc_time_t rtc_time; //Hora general
rtc_time_t rtc_time_aux; //Varible auxiliar que se usa para almacenar el tiempo antes de modificarlo
rtc_time_t rtc_cronometro; //Cronometro, no uso rtc_time_aux para el cronometro porque quiero guardar el valor del cronometro para que el usuario pueda salir del modoCronometro si que se pierda su valor

volatile uint16 segundos_transcurridos,contador_latidos,contador_pasos,total_pasos; //Contador de segundos para actualizar los pasos y latidos

volatile uint16 latidosPorMin, pasosPorMin;


void encendidoSistema(void);
void apagadoSistema(void);
void menuPrincipal(void);
void one_second_loop(void);
void modoCronometro( void );
void modoCambiarHora( void );
void modoFecha( void );
void modoDeporte( void );

uint8 prueba=0;
int main( void )
{
	/*Inits de los drivers*/
	sys_init();
	leds_init();

    timers_init();
    keypad_init();
    pbs_init();

	//Iniciamos el touchpad
	ts_init();
	ts_on();

    lcd_init();
    lcd_clear();
    lcd_on();

	startSensorsEmulator( beatHandler, stepHandler, 60, 60 );     // Arranca el emulador de sensores, instalando beatHandler y stepHandler como RTI de los respectivos sensores
	pbs_open( isr_pbs );
	sistemaEncendido = FALSE;
	pintarMenuPrincipal = TRUE;

	contador_latidos=0;
	contador_pasos=0;
	segundos_transcurridos =0;
	total_pasos =0;
	latidosPorMin=0;
	pasosPorMin =0;
	rtc_cronometro.hour=0;
	rtc_cronometro.min=0;
	rtc_cronometro.sec=0;

	//Inicializacion y configuracion del reloj de la pantalla
	rtc_init();
	flagRtc = FALSE;
	//Ponemos que se genere una interrupcion RTC
	rtc_open( isr_tick, 127);

    while( 1 )
    {

    	/*Programa principal*/
    	menuPrincipal();

    };
    return 0;
}



void funcionalidadComun(){ //Funcion que contiene los calculos que el sistema hace idependiente del modo donde estemos

			if( newBeat )
		    	{
		    		newBeat = FALSE;
		    		led_toggle( LEFT_LED );
		    	}
		    	//Generador de pasos
		    	if( newStep )
		    	{
		    		newStep = FALSE;
		    		led_toggle( RIGHT_LED );
		    	}

		    	if (segundos_transcurridos > 10) {
					// Calcular estimación de latidos por minuto y pasos por minuto
		    		latidosPorMin = contador_latidos * 6;
		    		pasosPorMin = contador_pasos * 6;

					//Restablecer contadores
					contador_pasos=0;
					contador_latidos=0;
					// Restablecer el temporizador
					segundos_transcurridos = 0;
				}
}
int compareMonth(const char* monthStr, const char* month) {
	int i;
	for ( i = 0; i < 3; ++i) {
		if (monthStr[i] != month[i]) {
			return 0;
		}
	}
	return 1;
}
uint8 calcularDiaSemana(uint8 year, uint8 month, uint8 day) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int K = year % 100;
    int J = year / 100;

    int dayOfWeek = (day + 13 * (month + 1) / 5 + K + K / 4 + J / 4 - 2 * J) % 7;
    if (dayOfWeek < 0) {
        dayOfWeek += 7;
    }

    return (dayOfWeek % 7); // Ajusta al rango de 1 a 7
}
void iniciarReloj(){
	const char* compileTime = __TIME__;
	rtc_time.hour = (compileTime[0] - '0') * 10 + (compileTime[1] - '0');
	rtc_time.min = (compileTime[3] - '0') * 10 + (compileTime[4] - '0');
	rtc_time.sec = (compileTime[6] - '0') * 10 + (compileTime[7] - '0');

	const char* compileDate = __DATE__;
	rtc_time.mday = (compileDate[4] - '0') * 10 + (compileDate[5] - '0');
	char monthStr[4];
	monthStr[0] = compileDate[0];
	monthStr[1] = compileDate[1];
	monthStr[2] = compileDate[2];
	monthStr[3] = '\0';

	if (compareMonth(monthStr, "Jan")) rtc_time.mon = 1;
	else if (compareMonth(monthStr, "Feb")) rtc_time.mon = 2;
	else if (compareMonth(monthStr, "Mar")) rtc_time.mon = 3;
	else if (compareMonth(monthStr, "Apr")) rtc_time.mon = 4;
	else if (compareMonth(monthStr, "May")) rtc_time.mon = 5;
	else if (compareMonth(monthStr, "Jun")) rtc_time.mon = 6;
	else if (compareMonth(monthStr, "Jul")) rtc_time.mon = 7;
	else if (compareMonth(monthStr, "Aug")) rtc_time.mon = 8;
	else if (compareMonth(monthStr, "Sep")) rtc_time.mon = 9;
	else if (compareMonth(monthStr, "Oct")) rtc_time.mon = 10;
	else if (compareMonth(monthStr, "Nov")) rtc_time.mon = 11;
	else if (compareMonth(monthStr, "Dec")) rtc_time.mon = 12;
	rtc_time.wday = calcularDiaSemana(rtc_time.year, rtc_time.mon, rtc_time.mday);
	rtc_time.year = (compileDate[9] - '0') * 10 + (compileDate[10] - '0');
	rtc_puttime( &rtc_time );
}
void mostrarDiaSemana(void){

	switch( rtc_time.wday){
		case 1:
			lcd_puts( 30, 45, BLACK,"Domingo");
				break;
		case 2:
			lcd_puts( 30, 45, BLACK,"Lunes");
					break;
		case 3:
			lcd_puts( 30, 45, BLACK,"Martes");
					break;
		case 4:
			lcd_puts( 30, 45, BLACK,"Miercoles");
					break;
		case 5:
			lcd_puts( 30, 45, BLACK,"Jueves");
					break;
		case 6:
			lcd_puts( 30, 45, BLACK,"Viernes");
					break;
		case 7:
			lcd_puts( 30, 45, BLACK,"Sabado");
					break;
		default:
			lcd_puts( 30, 45, BLACK,"Error");
				break;
	}

}
void mostrarRelojPrincipal(void){
	if( flagRtc )
		{
		flagRtc = FALSE;

		rtc_gettime( &rtc_time );

		//Mostrar la hora (16 pixeles el caracter en x2, 8 pixeles de normal)
		lcd_putint_x2(100, 90, BLACK, (int32) rtc_time.hour );
		if(rtc_time.hour < 10){ //Para poner un 0 en el lcd y no sea solo un digito
				lcd_putint_x2(100, 90, BLACK, (int32) 0 );
				lcd_putint_x2(116, 90, BLACK, (int32) rtc_time.hour );
		}
		lcd_putchar_x2(132, 90, BLACK, ':' );
		lcd_putint_x2(148, 90, BLACK, (int32) rtc_time.min );
		if(rtc_time.min < 10){ //Para poner un 0 en el lcd y no sea solo un digito
				lcd_putint_x2(148, 90, BLACK, (int32) 0);
				lcd_putint_x2(164, 90, BLACK, (int32)  rtc_time.min );
		}
		lcd_putchar_x2(180, 90, BLACK, ':' );
		lcd_putint_x2(196, 90, BLACK, (int32) rtc_time.sec );
		if(rtc_time.sec < 10){ //Para poner un 0 en el lcd y no sea solo un digito
				lcd_putint_x2(196, 90, BLACK, (int32) 0 );
				lcd_putint_x2(212, 90, BLACK, (int32) rtc_time.sec );
			}


		};
}
void menuPrincipal( void ){



	//Inicializamos el reloj a una fecha
	iniciarReloj();
	rtc_gettime( &rtc_time );


	uint16 x, y;


	lcd_clear();
	flagPbs = FALSE;
	//Empieza programa menu principal
	//Mientras no se pulse ningun pulsador
	while(!flagPbs){

		//Generador de latidos
		    	if( newBeat )
		    	{
		    		newBeat = FALSE;
		    		led_toggle( LEFT_LED );
		    	}
		    	//Generador de pasos
		    	if( newStep )
		    	{
		    		newStep = FALSE;
		    		led_toggle( RIGHT_LED );
		    	}

			mostrarRelojPrincipal();

		/*-------------Pintamos el menu principal-------------*/

		//Usamos esta variable para que no este constantemente pintando el menu
		if(pintarMenuPrincipal){
			lcd_draw_box( 10, 10, 310, 230, BLACK, 5 );

			//Mostrar dia de la semana
			mostrarDiaSemana();

			//Mostrar la fecha
			lcd_putint( 30, 30, BLACK,(int32) rtc_time.mday );
			if(rtc_time.mday < 10){ //Para poner un 0 en el lcd y no sea solo un digito
					lcd_putint(30, 30, BLACK, (int32) 0 );
					lcd_putint(38, 30, BLACK, (int32) rtc_time.mday );
				}
			lcd_putchar( 46, 30, BLACK, '/' );
			lcd_putint( 54, 30, BLACK,(int32) rtc_time.mon );
			if(rtc_time.mon < 10){ //Para poner un 0 en el lcd y no sea solo un digito
					lcd_putint(54, 30, BLACK, (int32) 0 );
					lcd_putint(62, 30, BLACK, (int32) rtc_time.mon );
				}
			lcd_putchar( 70, 30, BLACK, '/' );
			lcd_putint( 78, 30, BLACK,(int32) rtc_time.year );
			if(rtc_time.year < 10){ //Para poner un 0 en el lcd y no sea solo un digito
				lcd_putint(78, 30, BLACK, (int32) 0 );
				lcd_putint(86, 30, BLACK, (int32) rtc_time.year );
			}


			//Parte izquierda
			//----------------------
			//Mostrar opcion cronometro
			lcd_draw_box(30, 135, 150, 160, BLACK, 3);
			lcd_puts(40, 140, BLACK, "Cronometro");

			//Mostrar opcion cambiar fecha
			lcd_draw_box(30, 165, 150, 190, BLACK, 3);
			lcd_puts(40, 170, BLACK, "Cambiar fecha");

			//Parte derecha
			//----------------------

			//Mostrar opcion cambiar hora
			lcd_draw_box(170, 135, 290, 160, BLACK, 3);
			lcd_puts(180, 140, BLACK, "Cambiar hora");

			//Mostrar opcion contador latidos
			lcd_draw_box(170, 165, 290, 190, BLACK, 3);
			lcd_puts(180, 170, BLACK, "Modo deporte");

			//Hacemos que el programa no vuelva a pintar el menu
			pintarMenuPrincipal = FALSE;
		}

		INT_DISABLE;
		lcd_puts(180, 30, BLACK, "Pasos/min:");
		lcd_putint(270, 30, BLACK, (int32) pasosPorMin);

		lcd_puts(164, 45, BLACK, "Latidos/min:");
		lcd_putint(270, 45, BLACK, (int32) latidosPorMin);
		INT_ENABLE;
		/*-------------Reconocemos pulsaciones del touchpad el menu principal-------------*/
			//Captamos donde ha presionado el usuario
		if(ts_pressed()){
			ts_getpos(&x,&y);
		}


		if( x>30 && y>135 && x<150 && y<160 )
			{
				x=0;
				y = 0;
				modoCronometro();
			}
		else if( x>30 && y>165 && x<150 && y<190 )
			{
				x=0;
				y = 0;
				modoFecha();
			}
		else if( x>170 && y>135 && x<290 && y<160 )
			{
				x=0;
				y = 0;
				modoCambiarHora();
			}
		else if( x>170 && y>165 && x<290 && y<190 )
			{
				x=0;
				y = 0;
				modoDeporte();
			}


	};//Fin while menuPrincipal

}
void mostrarRelojAux(rtc_time_t *rtc_aux){

	lcd_putint_x2(100, 70, BLACK, (int32) rtc_aux->hour );
	if(rtc_aux->hour < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(100, 70, BLACK, (int32) 0 );
		lcd_putint_x2(116, 70, BLACK, (int32) rtc_aux->hour );
	}

	lcd_putchar_x2(132, 70, BLACK, ':' );
	lcd_putint_x2(148, 70, BLACK, (int32) rtc_aux->min );
	if(rtc_aux->min < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(148, 70, BLACK, (int32) 0);
		lcd_putint_x2(164, 70, BLACK, (int32)  rtc_aux->min );
	}

	lcd_putchar_x2(180, 70, BLACK, ':' );
	lcd_putint_x2(196, 70, BLACK, (int32) rtc_aux->sec );
	if(rtc_aux->sec < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(196, 70, BLACK, (int32) 0 );
		lcd_putint_x2(212, 70, BLACK, (int32) rtc_aux->sec );
	}
}
void mostrarFecha(rtc_time_t *rtc_aux){

	lcd_putint_x2(100, 70, BLACK, (int32) rtc_aux->mday );
	if(rtc_aux->mday < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(100, 70, BLACK, (int32) 0 );
		lcd_putint_x2(116, 70, BLACK, (int32) rtc_aux->mday );
	}

	lcd_putchar_x2(132, 70, BLACK, '/' );
	lcd_putint_x2(148, 70, BLACK, (int32) rtc_aux->mon );
	if(rtc_aux->mon < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(148, 70, BLACK, (int32) 0);
		lcd_putint_x2(164, 70, BLACK, (int32)  rtc_aux->mon );
	}

	lcd_putchar_x2(180, 70, BLACK, '/' );
	lcd_putint_x2(196, 70, BLACK, (int32) rtc_aux->year );
	if(rtc_aux->year < 10){ //Para poner un 0 en el lcd y no sea solo un digito
		lcd_putint_x2(196, 70, BLACK, (int32) 0 );
		lcd_putint_x2(212, 70, BLACK, (int32) rtc_aux->year );
	}
}
void modoCronometro( void ){

	boolean volverMenuPrincipal = FALSE;
	boolean pintadoInicial = TRUE;
	boolean crono_on = FALSE;
	boolean crono_reset = FALSE;



	uint16 x, y;
	//Limpiamos el menu principal
	lcd_clear();
	lcd_draw_box( 10, 10, 310, 230, BLACK, 5 );

	while(!volverMenuPrincipal){

		//Aqui pintamos las cosas que no se actualizan
		if(pintadoInicial){

			//Mostrar opcion volver menu principal
			lcd_draw_box(170, 12, 310, 40, BLACK, 3);
			lcd_puts(180, 20, BLACK, "Menu principal");

			// Mostrar opcion cambiar fecha
			lcd_draw_box(95, 165, 225, 190, BLACK, 3);
			lcd_puts(105, 170, BLACK, "Iniciar crono");

			// Mostrar opcion contador pasos
			lcd_draw_box(20, 195, 150, 220, BLACK, 3);
			lcd_puts(30, 200, BLACK, "Detener crono");

			// Mostrar opcion contador modo deporte
			lcd_draw_box(170, 195, 300, 220, BLACK, 3);
			lcd_puts(180, 200, BLACK, "Resetear crono");

			//Mostrar el cronometro inicial (16 pixeles el caracter en x2, 8 pixeles de normal)
			mostrarRelojAux(&rtc_cronometro);

			pintadoInicial = FALSE;
		}


		//Para que no se quede el programa congelado esperando que el usuario presione la pantalla
		if(ts_pressed()){
			ts_getpos(&x,&y);
		}

		if( x>95 && y>165 && x<225 && y<190 )
			{
				x=0;
				y = 0;
				crono_on = TRUE;
				timer0_open_ms( isr_timer0, 1000, TIMER_INTERVAL );
			}
		else if( x>20 && y>195 && x<150 && y<220 )
			{
				x=0;
				y = 0;
				crono_on = FALSE;
				timer0_close();
			}
		else if( x>170 && y>195 && x<300 && y<220 )
			{
				x=0;
				y = 0;
				crono_on = FALSE;
				crono_reset = TRUE;
				timer0_close();
			}
		else if( x>170 && y>12 && x<310 && y<40 )
			{
				x=0;
				y = 0;
				volverMenuPrincipal = TRUE;
				crono_on = FALSE;
				timer0_close();
			}

		if(crono_reset){
			rtc_cronometro.sec = 0;
			rtc_cronometro.min = 0;
			rtc_cronometro.hour= 0;
			mostrarRelojAux(&rtc_cronometro);
			crono_reset = FALSE;
		}
		//Mostrar y actualizar el cronometro
		if( crono_on && flagTimer0)
		{
			//Usar timer0
			flagTimer0 = FALSE;

			rtc_cronometro.sec++;

			if(rtc_cronometro.sec >59){
				rtc_cronometro.sec = 0;
				 rtc_cronometro.min++;
			}
			if(rtc_cronometro.min >59){
				rtc_cronometro.min = 0;
				 rtc_cronometro.hour++;
			}

			//Mostrar el cronometro inicial (16 pixeles el caracter en x2, 8 pixeles de normal)
			mostrarRelojAux(&rtc_cronometro);
		};
	}
	pintarMenuPrincipal = TRUE;
	lcd_clear();

}


/*--------------------Funciones para el cambio de fecha y hora--------------------*/

//----Funciones auxiliares de los modos cambio fecha y hora----//
void operacionCambioHora(uint8 modo, uint8 seleccionado){
	//seleccionado valores (1-3) siendo 1 hora, 2 minutos, 3 segundos
	//modo (1-2) siendo 1 la suma y 2 la resta

	if(seleccionado ==1){//Cambio segundos
			if(modo ==1){
				rtc_time_aux.hour++;
				if(rtc_time_aux.hour > 24){
					rtc_time_aux.hour = 0;
				}
			}else{
				modo=2; //Por si acaso entra sin pillar bien el valor de modo asi por defecto resta
				if(rtc_time_aux.hour !=0){
					rtc_time_aux.hour--;
				}else{
					rtc_time_aux.hour =24;
				}
			}
	}else if(seleccionado == 2){
		if(modo ==1){
			rtc_time_aux.min++;
			if(rtc_time_aux.min > 59){
				rtc_time_aux.min=0;
			}
		}else{
			modo=2; //Por si acaso entra sin pillar bien el valor de modo asi por defecto resta
			if(rtc_time_aux.min !=0){
				rtc_time_aux.min--;
			}else{
				rtc_time_aux.min =59;
			}
		}
	}
	else if(seleccionado == 3){
		if(modo ==1){
			rtc_time_aux.sec++;
			if(rtc_time_aux.sec > 59){
				rtc_time_aux.sec = 0;
			}
		}else{
			modo=2; //Por si acaso entra sin pillar bien el valor de modo asi por defecto resta
			if(rtc_time_aux.sec !=0){
				rtc_time_aux.sec--;
			}else{
				rtc_time_aux.sec =59;
			}

		}
	}

}
void cambioMesComp(){
	//Comprobamos aqui tambien el dia para que el usuario no pueda poner 30 de febrero 31 de noviembre etc modificando el mes
	if (rtc_time_aux.mon == 2) { // Febrero
		if ((rtc_time_aux.year % 4 == 0 && rtc_time_aux.year % 100 != 0) || rtc_time_aux.year % 400 == 0) {
			// Año bisiesto
			if(rtc_time_aux.mday >29){
				rtc_time_aux.mday =29;
			}
		} else {
			// Año no bisiesto
			if(rtc_time_aux.mday >28){
				rtc_time_aux.mday =28;
			}
		}
	} else if (rtc_time_aux.mon == 4 || rtc_time_aux.mon == 6 || rtc_time_aux.mon == 9 || rtc_time_aux.mon == 11) {
		// Meses con 30 días
		if(rtc_time_aux.mday >30){
			rtc_time_aux.mday =30;
		}
	}
}

void operacionCambioFecha(uint8 modo, uint8 seleccionado){
	//seleccionado valores (1-3) siendo 1 dia, 2 mes, 3 año
	//modo (1-2) siendo 1 la suma y 2 la resta

	if(seleccionado ==1){//dia
			if(modo ==1){
				rtc_time_aux.wday++;
				if(rtc_time_aux.wday >7){
					rtc_time_aux.wday = 1;
				}

				if (rtc_time_aux.mon == 2) { // Febrero
					if ((rtc_time_aux.year % 4 == 0 && rtc_time_aux.year % 100 != 0) || rtc_time_aux.year % 400 == 0) {
						// Año bisiesto
						rtc_time_aux.mday++;
						if(rtc_time_aux.mday >29){
							rtc_time_aux.mday =1;
						}
					} else {
						// Año no bisiesto
						rtc_time_aux.mday++;
						if(rtc_time_aux.mday >28){
							rtc_time_aux.mday =1;
						}
					}
				} else if (rtc_time_aux.mon == 4 || rtc_time_aux.mon == 6 || rtc_time_aux.mon == 9 || rtc_time_aux.mon == 11) {
					// Meses con 30 días
					rtc_time_aux.mday++;
					if(rtc_time_aux.mday >30){
						rtc_time_aux.mday =1;
					}

				} else {
					// Meses con 31 días
					rtc_time_aux.mday++;
					if(rtc_time_aux.mday >31){
						rtc_time_aux.mday =1;
					}
				}
			}else{
				modo=2;
				rtc_time_aux.wday--;
				if(rtc_time_aux.wday <1){
					rtc_time_aux.wday = 7;
				}

				if (rtc_time_aux.mon == 2) { // Febrero
					if ((rtc_time_aux.year % 4 == 0 && rtc_time_aux.year % 100 != 0) || rtc_time_aux.year % 400 == 0) {
						// Año bisiesto
						if(rtc_time_aux.mday !=1){
							rtc_time_aux.mday--;
						}else{
							rtc_time_aux.mday =29;
						}
					} else {
						// Año no bisiesto
						if(rtc_time_aux.mday !=1){
							rtc_time_aux.mday--;
						}else{
							rtc_time_aux.mday =28;
						}
					}
				} else if (rtc_time_aux.mon == 4 || rtc_time_aux.mon == 6 || rtc_time_aux.mon == 9 || rtc_time_aux.mon == 11) {
					// Meses con 30 días
					if(rtc_time_aux.mday !=1){
						rtc_time_aux.mday--;
					}else{
						rtc_time_aux.mday =30;
					}

				} else {
					if(rtc_time_aux.mday !=1){
						rtc_time_aux.mday--;
					}else{
						rtc_time_aux.mday =31;
					}
				}
			}
	}else if(seleccionado == 2){//mes
		if(modo ==1){
			rtc_time_aux.mon++;
			if(rtc_time_aux.mon > 12){
				rtc_time_aux.mon = 1;
			}
			cambioMesComp();
			rtc_time_aux.wday = calcularDiaSemana(rtc_time_aux.year,rtc_time_aux.mon,rtc_time_aux.mday);
		}else{
			modo=2; //Por si acaso entra sin pillar bien el valor de modo asi por defecto resta
			if(rtc_time_aux.mon !=1){
				rtc_time_aux.mon--;
			}else{
				rtc_time_aux.mon =12;
			}
			cambioMesComp();
			rtc_time_aux.wday = calcularDiaSemana(rtc_time_aux.year,rtc_time_aux.mon,rtc_time_aux.mday);
		}
	}
	else if(seleccionado == 3){//año
		if(modo ==1){
			rtc_time_aux.year++;
			if(rtc_time_aux.year > 99){
				rtc_time_aux.year = 0;
			}
			//Cada año que pasa cambia el dia de la semana, por ejemplo el 3/1/24 es miercoles pero el 3/1/23 es jueves
			rtc_time_aux.wday++;
			if(rtc_time_aux.wday >7){
				rtc_time_aux.wday = 1;
			}
		}else{
			modo=2; //Por si acaso entra sin pillar bien el valor de modo asi por defecto resta
			if(rtc_time_aux.year !=0){
				rtc_time_aux.year--;
			}else{
				rtc_time_aux.year =99;
			}
			//Cada año que se retrocede cambia el dia de la semana, por ejemplo el 3/1/23 es martes pero el 3/1/24 es miercoles
			rtc_time_aux.wday--;
			if(rtc_time_aux.wday <1){
				rtc_time_aux.wday = 7;
			}

		}
	}

}
void cambiarDatosReloj(uint8 seleccionado, boolean fecha){
	//seleccionado valores (1-3) siendo 1 hora, 2 minutos, 3 segundos
	//El metodo que voy a usar es que mientras el usuario pulse los cuadrados de + y - no salga de esta funcion, si pulsa en otro lado se sale de la funcion
	boolean salir = FALSE;
	boolean pulsado = FALSE;

	uint8 modo=1; //modo (1-2) siendo 1 la suma y 2 la resta
	uint16 x, y;

	while(!salir){
		if(ts_pressed()){
			ts_getpos(&x,&y);
			pulsado = TRUE; //Uso la variable pulsado porque no quiero parar la ejecucion del sistema para que no se pare el reloj principal asi solo se sale cuando se pulsa fuera de + o -
		}

		if( x>210 && y>109 && x<246 && y<150 )
			{
			//Boton mas
			x=0;
			y = 0;
			modo =1;
			if(!fecha){
				operacionCambioHora(modo,seleccionado);
			}else{
				operacionCambioFecha(modo,seleccionado);
			}


			//Actualizamos y mostramos la nueva hora
			rtc_puttime(&rtc_time_aux);
			if(!fecha){
				mostrarRelojAux(&rtc_time_aux);
			}else{
				mostrarFecha(&rtc_time_aux);
			}

			pulsado = FALSE;

			}else if( x>210 && y>165 && x<246 && y<204)
			{
			//Boton menos
			x=0;
			y = 0;
			modo =2;
			if(!fecha){
				operacionCambioHora(modo,seleccionado);
			}else{
				operacionCambioFecha(modo,seleccionado);
			}

			//Actualizamos el reloj del sistema y mostramos la nueva hora
			rtc_puttime(&rtc_time_aux);
			if(!fecha){
				mostrarRelojAux(&rtc_time_aux);
			}else{
				mostrarFecha(&rtc_time_aux);
			}

			pulsado = FALSE;

			}
		else{
			if(pulsado){ //Si ha pulsado fuera de los botones + y - se sale y vuelve a modoCambiarHora()
				salir = TRUE;
			}
		}
	}

	//Actualizamos el tiempo del sistema

}

//----Funciones principales de los modos cambio fecha y hora----//
void modoCambiarHora( void ){
	boolean volverMenuPrincipal = FALSE;
	boolean pintadoInicial = TRUE;

	rtc_gettime( &rtc_time_aux ); //Guardamos el tiempo con la que hemos entrado a la opcion

	uint16 x, y;

	//Limpiamos el menu principal
	lcd_clear();
	lcd_draw_box( 10, 10, 310, 230, BLACK, 5 );

	while(!volverMenuPrincipal){

		//Aqui pintamos las cosas que no se actualizan
		if(pintadoInicial){

			//Mostrar opcion cambiar fecha
			lcd_draw_box(170, 12, 310, 40, BLACK, 3);
			lcd_puts(180, 20, BLACK, "Menu principal");

			//Mostrar opcion cambiar hora
			lcd_draw_box(30, 115, 170, 140, BLACK, 3);
			lcd_puts(40, 120, BLACK, "Cambiar hora");

			//Mostrar opcion cambiar minutos
			lcd_draw_box(30, 145, 170, 170, BLACK, 3);
			lcd_puts(40, 150, BLACK, "Cambiar minutos");

			//Mostrar opcion contador segundos
			lcd_draw_box(30, 175, 170, 200, BLACK, 3);
			lcd_puts(40, 180, BLACK, "Cambiar segundos");

			// Boton +
			lcd_draw_box(210, 109, 246, 150, BLACK, 3);
			lcd_puts_x2(220, 115, BLACK, "+");

			// Boton -
			lcd_draw_box(210, 165, 246, 204, BLACK, 3);
			lcd_puts_x2(221, 169, BLACK, "-");

			//Pintamos el reloj inicial
			mostrarRelojAux(&rtc_time_aux);

			pintadoInicial = FALSE;
		}


		//Para que no se quede el programa congelado esperando que el usuario presione la pantalla
		if(ts_pressed()){
			ts_getpos(&x,&y);
		}

		if( x>30 && y>115 && x<170 && y<140 )
			{
			//CambiarHora
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando hora" );
				cambiarDatosReloj(1,FALSE);
				lcd_puts( 30, 30, BLACK,"              " );
			}
		else if( x>30 && y>145 && x<170 && y<170 )
			{
			//CambiarMinutos
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando minutos" );
				cambiarDatosReloj(2,FALSE);
				lcd_puts( 30, 30, BLACK,"                 " );

			}
		else if( x>30 && y>175 && x<170 && y<200 )
			{
			//CambiarSegundos
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando segs" );
				cambiarDatosReloj(3,FALSE);
				lcd_puts( 30, 30, BLACK,"              " );
			}
		else if( x>170 && y>12 && x<310 && y<40 )
			{
			//Volver menu principal
				x=0;
				y = 0;
				volverMenuPrincipal = TRUE;
			}
		}
		pintarMenuPrincipal = TRUE;
		lcd_clear();
}
void modoFecha( void ){
	boolean volverMenuPrincipal = FALSE;
	boolean pintadoInicial = TRUE;

	rtc_gettime( &rtc_time_aux ); //Guardamos el tiempo con la que hemos entrado a la opcion

	uint16 x, y;

	//Limpiamos el menu principal
	lcd_clear();
	lcd_draw_box( 10, 10, 310, 230, BLACK, 5 );

	while(!volverMenuPrincipal){

		//Aqui pintamos las cosas que no se actualizan
		if(pintadoInicial){

			//Mostrar opcion cambiar fecha
			lcd_draw_box(170, 12, 310, 40, BLACK, 3);
			lcd_puts(180, 20, BLACK, "Menu principal");

			//Mostrar opcion cambiar hora
			lcd_draw_box(30, 115, 170, 140, BLACK, 3);
			lcd_puts(40, 120, BLACK, "Cambiar dia");

			//Mostrar opcion cambiar minutos
			lcd_draw_box(30, 145, 170, 170, BLACK, 3);
			lcd_puts(40, 150, BLACK, "Cambiar mes");

			//Mostrar opcion contador segundos
			lcd_draw_box(30, 175, 170, 200, BLACK, 3);
			lcd_puts(40, 180, BLACK, "Cambiar año");

			// Boton +
			lcd_draw_box(210, 109, 246, 150, BLACK, 3);
			lcd_puts_x2(220, 115, BLACK, "+");

			// Boton -
			lcd_draw_box(210, 165, 246, 204, BLACK, 3);
			lcd_puts_x2(221, 169, BLACK, "-");

			//Pintamos el reloj inicial
			mostrarFecha(&rtc_time_aux);

			pintadoInicial = FALSE;
		}


		//Para que no se quede el programa congelado esperando que el usuario presione la pantalla
		if(ts_pressed()){
			ts_getpos(&x,&y);
		}

		if( x>30 && y>115 && x<170 && y<140 )
			{
			//CambiarHora
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando dia" );
				cambiarDatosReloj(1,TRUE);
				lcd_puts( 30, 30, BLACK,"              " );
			}
		else if( x>30 && y>145 && x<170 && y<170 )
			{
			//CambiarMinutos
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando mes" );
				cambiarDatosReloj(2,TRUE);
				lcd_puts( 30, 30, BLACK,"                 " );

			}
		else if( x>30 && y>175 && x<170 && y<200 )
			{
			//CambiarSegundos
				x=0;
				y = 0;
				lcd_puts( 30, 30, BLACK,"Cambiando año" );
				cambiarDatosReloj(3,TRUE);
				lcd_puts( 30, 30, BLACK,"              " );
			}
		else if( x>170 && y>12 && x<310 && y<40 )
			{
			//Volver menu principal
				x=0;
				y = 0;
				volverMenuPrincipal = TRUE;
			}
		}
	pintarMenuPrincipal = TRUE;
	lcd_clear();
}
/*--------------------Funciones para el modo Deporte--------------------*/
char* invertirCadena(char* str) {
    // Calcular la longitud de la cadena manualmente
    int longitud = 0;
    while (str[longitud] != '\0') {
        longitud++;
    }

    int i, j;

    for (i = 0, j = longitud - 1; i < j; i++, j--) {
        // Intercambiar caracteres de extremo opuesto
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    return str;

}
void lcd_putKm_x2(uint16 x, uint16 y, uint8 color, fix32 f) {
    char buf[16];
    char *p = buf;
    boolean negativo = FALSE;

    // Manejar el caso de números negativos
    if (f < 0) {
        f *= -1;
        negativo = TRUE;
    }

    // Convertir parte entera a cadena con al menos dos dígitos inicializados a 0
    int32 i = f >> QM;

    // Añadir los dígitos de la parte entera al buffer
    if (i == 0) {
        *p++ = '0';
        *p++ = '0';
    } else {
        *p++ = '0' + (i / 10);
        *p++ = '0' + (i % 10);
    }

    // Añadir punto decimal
    *p++ = '.';

    // Convertir parte decimal a cadena con tres dígitos
    fix32 parte_decimal = f & ((1 << QM) - 1);
    int j;
    for (j = 0; j < 3; ++j) {
        parte_decimal *= 10;
        int digit = parte_decimal >> QM;  // Ajuste aquí al cambiar la definición de TOFIX
        *p++ = '0' + digit;
        parte_decimal &= ((1 << QM) - 1);
    }

    // Añadir terminador nulo
    *p = '\0';

    // Manejar el caso de números negativos
    if (negativo) {
        *--p = '-';
    }

    lcd_puts_x2(x, y, color, buf);
}
void lcd_putCal_x2(uint16 x, uint16 y, uint8 color, fix32 f) {
    char buf[16];
    char *p = buf;
    boolean negativo = FALSE;

    // Manejar el caso de números negativos
    if (f < 0) {
        f *= -1;
        negativo = TRUE;
    }

    // Convertir parte entera a cadena con al menos tres dígitos inicializados a 0
    int32 i = f >> QM;

    // Añadir los dígitos de la parte entera al buffer
    *p++ = '0' + (i / 100);  // Asegurar que haya al menos tres dígitos
    *p++ = '0' + ((i / 10) % 10);
    *p++ = '0' + (i % 10);

    // Añadir punto decimal
    *p++ = '.';

    // Convertir parte decimal a cadena con tres dígitos
    fix32 parte_decimal = f & ((1 << QM) - 1);
    int j;
    for (j = 0; j < 3; ++j) {
        parte_decimal *= 10;
        int digit = parte_decimal >> QM;  // Ajuste aquí al cambiar la definición de TOFIX
        *p++ = '0' + digit;
        parte_decimal &= ((1 << QM) - 1);
    }

    // Añadir terminador nulo
    *p = '\0';

    // Manejar el caso de números negativos
    if (negativo) {
        *--p = '-';
    }

    lcd_puts_x2(x, y, color, buf);
}


void muestraKilometros() {
    INT_DISABLE;
    uint16 pasosAux = total_pasos;
    INT_ENABLE;

    const fix16 metro_por_paso = TOFIX(fix16, 0.7023, QM); // Un paso son 0,7 metros

    fix32 kilometros = FDIV(FMUL(metro_por_paso, pasosAux, QM), 1000, QM);

    // Convertir PESO_CORPORAL y FACTOR_CALORIAS a fix32
    const fix16 peso_corporal = TOFIX(fix16, PESO_CORPORAL, QM);
    const fix16 factor_calorias = TOFIX(fix16, 0.200, QM);

    // Calcular las calorías quemadas
    fix32 calorias_quemadas = FDIV(FMUL(kilometros, peso_corporal, QM), factor_calorias, QM);

    lcd_puts(38, 50, BLACK, "kilometros");
    // Mostrar el resultado en la pantalla LCD
    lcd_putKm_x2(38,65, BLACK, kilometros);

    lcd_puts(160,50, BLACK, "Calorias quemadas");
    lcd_putCal_x2(160, 65, BLACK, calorias_quemadas);
}


void modoDeporte( void ){
		boolean volverMenuPrincipal = FALSE;
		boolean pintadoInicial = TRUE;
		uint16 x, y;

		//Limpiamos el menu principal
		lcd_clear();
		lcd_draw_box( 10, 10, 310, 230, BLACK, 5 );


		while(!volverMenuPrincipal){

			//Aqui pintamos las cosas que no se actualizan
			if(pintadoInicial){

				//Mostrar opcion cambiar fecha
				lcd_draw_box(170, 12, 310, 40, BLACK, 3);
				lcd_puts(180, 20, BLACK, "Menu principal");

			}

			INT_DISABLE;
			lcd_puts(30, 115, BLACK, "Pasos totales:");
			lcd_putint(145, 115, BLACK, (int32) total_pasos);

			lcd_puts(30, 140, BLACK, "Pasos por minuto:");
			lcd_putint(170, 140, BLACK, (int32) pasosPorMin);

			lcd_puts(30, 165, BLACK, "Latidos por minuto:");
			lcd_putint(190, 165, BLACK, (int32) latidosPorMin);
			INT_ENABLE;

			// Mostrar opcion contador pasos




			muestraKilometros();

			//Para que no se quede el programa congelado esperando que el usuario presione la pantalla
			if(ts_pressed()){
				ts_getpos(&x,&y);
			}

			if( x>170 && y>12 && x<310 && y<40 )
				{
					x=0;
					y = 0;
					volverMenuPrincipal = TRUE;

				}



			}
			pintarMenuPrincipal = TRUE;
			lcd_clear();
}


void one_second_loop( void )
{
    uint32 i;

    for( i=591436; i; i-- );
}

/*--------------------Funciones para las interrupciones--------------------*/
void beatHandler( void )
{
    newBeat = TRUE;
    I_ISPC  = BIT_BEATEMULATOR;
    contador_latidos++;
}

void stepHandler( void )
{
    newStep = TRUE;
    I_ISPC  = BIT_STEPEMULATOR;
    contador_pasos++;
    total_pasos++;
}
void isr_tick( void )
{
    flagRtc = TRUE;
    I_ISPC = BIT_TICK;
    segundos_transcurridos++;
    funcionalidadComun();
}

void isr_timer0( void )
{
    flagTimer0 = TRUE;
    I_ISPC = BIT_TIMER0;
}

void isr_keypad( void )
{
    flagKeypad = TRUE;
    I_ISPC = BIT_KEYPAD;
}

void isr_pbs( void )
{
	EXTINTPND = BIT_RIGHTPB | BIT_LEFTPB;
    flagPbs = TRUE;
    I_ISPC = BIT_PB;
}

