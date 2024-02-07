#include <s3c44b0x.h>
#include <s3cev40.h>
#include <common_types.h>
#include <system.h>
#include "sensorsEmulator.h"

/*******************************************************************/

#define FIFO_SIZE (1024)

typedef struct fifo {
	volatile uint16 head;
	volatile uint16 tail;
	volatile uint16 size;
	uint8 buffer[FIFO_SIZE];
} fifo_t;

static void fifo_init( fifo_t *pfifo );
static void fifo_enqueue( fifo_t *pfifo, uint8 data );
static void fifo_dequeue( fifo_t *pfifo, uint8 *data );
static boolean fifo_is_empty( fifo_t *pfifo );
static boolean fifo_is_full( fifo_t *pfifo );

static fifo_t fifoTX;

static void uart0int_isrTX( void ) __attribute__ ((interrupt ("IRQ")));
static void uart0int_isrRX( void ) __attribute__ ((interrupt ("IRQ")));

static void uart0int_putchar( char ch );
static void uart0int_puts( char *s );
static void uart0int_putnum( uint8 i );
static void uart0int_putMenu( void );

/*******************************************************************/

static volatile uint8 latidosPorMin, pasosPorMin;

static const uint16 cntb[256] =
{
    65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535,
    60000, 54545, 50000, 46154, 42857, 40000, 37500, 35294, 33333, 31579,
    30000, 28571, 27273, 26087, 25000, 24000, 23077, 22222, 21429, 20690,
    20000, 19355, 18750, 18182, 17647, 17143, 16667, 16216, 15789, 15385,
    15000, 14634, 14286, 13953, 13636, 13333, 13043, 12766, 12500, 12245,
    12000, 11765, 11538, 11321, 11111, 10909, 10714, 10526, 10345, 10169,
    10000,  9836,  9677,  9524,  9375,  9231,  9091,  8955,  8824,  8696,
     8571,  8451,  8333,  8219,  8108,  8000,  7895,  7792,  7692,  7595,
     7500,  7407,  7317,  7229,  7143,  7059,  6977,  6897,  6818,  6742,
     6667,  6593,  6522,  6452,  6383,  6316,  6250,  6186,  6122,  6061,
     6000,  5941,  5882,  5825,  5769,  5714,  5660,  5607,  5556,  5505,
     5455,  5405,  5357,  5310,  5263,  5217,  5172,  5128,  5085,  5042,
     5000,  4959,  4918,  4878,  4839,  4800,  4762,  4724,  4688,  4651,
     4615,  4580,  4545,  4511,  4478,  4444,  4412,  4380,  4348,  4317,
     4286,  4255,  4225,  4196,  4167,  4138,  4110,  4082,  4054,  4027,
     4000,  3974,  3947,  3922,  3896,  3871,  3846,  3822,  3797,  3774,
     3750,  3727,  3704,  3681,  3659,  3636,  3614,  3593,  3571,  3550,
     3529,  3509,  3488,  3468,  3448,  3429,  3409,  3390,  3371,  3352,
     3333,  3315,  3297,  3279,  3261,  3243,  3226,  3209,  3191,  3175,
     3158,  3141,  3125,  3109,  3093,  3077,  3061,  3046,  3030,  3015,
     3000,  2985,  2970,  2956,  2941,  2927,  2913,  2899,  2885,  2871,
     2857,  2844,  2830,  2817,  2804,  2791,  2778,  2765,  2752,  2740,
     2727,  2715,  2703,  2691,  2679,  2667,  2655,  2643,  2632,  2620,
     2609,  2597,  2586,  2575,  2564,  2553,  2542,  2532,  2521,  2510,
     2500,  2490,  2479,  2469,  2459,  2449,  2439,  2429,  2419,  2410,
     2400,  2390,  2381,  2372,  2362,  2353
};

/*******************************************************************/


void startSensorsEmulator( void (*isrBeat)(void), void (*isrStep)(void), uint8 beatPerMin, uint8 stepPerMin )
{

	latidosPorMin = beatPerMin;
	pasosPorMin   = stepPerMin;

    CLKCON |= (1<<10) | (1<<8) | (1<<7) | (1 << 3);            // Activa GPIO, UART0, BDMA y TIMER

	PCONE = (PCONE & ~(0xf<<2)) | (2<<4) | (2<<2); 	           // PE[2] = RxD0, PE[1] = TxD0
	PUPE  |= (1<<2) | (1<<1);						           // Pull-up disable

	UFCON0 = 0;	                                               // FIFOs desactivadas, para activarlas UFCON0 = 1
	UMCON0 = 0;	                                               // Control de flujo manual
	ULCON0 = (0 << 6) | (0 << 3) | (0 << 2) | (3);   		   // normal (no infrarojos), sin paridad, 1 bit de stop, 8 bits de datos
	UBRDIV0 = 34;                                              // 115200 baudios asumiendo 64MHz
	UCON0 = (0 << 9) | (0 << 8)| (1 << 2) | (1);			   // Tx pulso, Rx pulso, Tx int/polling, Rx int/polling

	fifo_init( &fifoTX );

	pISR_URXD0 = (uint32) uart0int_isrRX;	 			       // Instala la rutina de tratamiento de recepción
	pISR_UTXD0 = (uint32) uart0int_isrTX;	 			       // Instala la rutina de tratamiento de transmisión
	I_ISPC	   = (BIT_URXD0 | BIT_UTXD0);		               // Borra los bits de interrupción pendiente
	INTMSK    &= ~( BIT_GLOBAL | BIT_URXD0 | BIT_UTXD0 );	   // Desenmascara globalmente las interrupciones y específicamente las interrupciones RX y Tx del UART0


	TCFG0 = (TCFG0 & ~(0xff << 8)) | (199 << 8);               // T3-T2 PRESCALER = 199 (1/(199+1))
    TCFG1 = (TCFG1 & ~(0xf << 12)) | (4 << 12);                // T3 DIVISOR = 32 (1/32)
    TCFG1 = (TCFG1 & ~(0xf << 8))  | (4 << 8);                 // T2 DIVISOR = 32 (1/32)
    
    INTMSK |= ( BIT_TIMER3 | BIT_TIMER2 );                     // Enmascara la interrupcion por fin de T3 y T2

    pISR_TIMER3 = (uint32) isrBeat;                            // Instala la funcion isr como RTI por fin de cuenta de T3
    pISR_TIMER2 = (uint32) isrStep;                            // Instala la funcion isr como RTI por fin de cuenta de T2

    TCNTB3  = cntb[latidosPorMin];                             // Carga T3
    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 17);   // Modo interval, carga TCNT3, stop T3
    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 16);   // Modo interval, no carga TCNT3, start T3

    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2

    I_ISPC  = BIT_TIMER3 | BIT_TIMER2;                         // Borra el bit de interrupción pendiente por fin de T3 y por fin de T2
    INTMSK &= ~( BIT_GLOBAL | BIT_TIMER3 | BIT_TIMER2 );       // Desenmascara la interrupción por fin del T4, fin T5 y las interrupciones globales


	uart0int_puts( "\n\n" );
	uart0int_puts( "-------------------------------------\n" );
	uart0int_puts( "Emulador de latidos y pasos arrancado\n" );
	uart0int_puts( "  - Latidos por minuto: 28-255\n" );
	uart0int_puts( "  - Pasos por minuto:   0/10-200\n" );
	uart0int_puts( "-------------------------------------\n" );
	uart0int_putMenu();
}

/*******************************************************************/

void uart0int_putchar( char ch )
{
	if( fifo_is_empty( &fifoTX ) )
	{
		while( !(UTRSTAT0 & (1 << 1)) );	// Espera por si todavía está transmitiendo el último byte enviado
		UTXH0 = ch;							// Envía el byte, cuando termine la transmisión se genera la primera interrupción
	}
	else
	{
		while( fifo_is_full( &fifoTX ) );
		fifo_enqueue( &fifoTX, (uint8) ch );
	}
}

void uart0int_isrTX( void )
{
    I_ISPC = BIT_UTXD0;
	if( !fifo_is_empty( &fifoTX ) )
		fifo_dequeue( &fifoTX, (uint8 *) &UTXH0 );
}

void uart0int_puts( char *s )
{
    while( *s )
		uart0int_putchar( *s++ );
}

void uart0int_putnum( uint8 i )
{
	char buf[3 + 1];
	char *p = buf + 3;

	*p = '\0';

    do {
        *--p = '0' + (i % 10);
		i /= 10;
	} while( i );

    uart0int_puts( p );
}

void uart0int_putMenu( void )
{
	uart0int_puts( "\n" );
	uart0int_puts( "Latidos por minuto: " );
	uart0int_putnum( latidosPorMin );
	uart0int_puts( " / Pasos por minuto: " );
	uart0int_putnum( pasosPorMin );
	uart0int_putchar( '\n' );
	uart0int_puts( "  1 - Incrementar latidos  (+1) \n" );
	uart0int_puts( "  2 - Incrementar latidos (+10) \n" );
	uart0int_puts( "  3 - Decrementar latidos  (-1) \n" );
	uart0int_puts( "  4 - Decrementar latidos (-10) \n" );
	uart0int_puts( "  d - Detenerse \n" );
	uart0int_puts( "  a - Comenzar a andar \n" );
	uart0int_puts( "  5 - Incrementar pasos    (+1) \n" );
	uart0int_puts( "  6 - Incrementar pasos   (+10) \n" );
	uart0int_puts( "  7 - Decrementar pasos    (-1) \n" );
	uart0int_puts( "  8 - Decrementar pasos   (-10) \n" );
}

void uart0int_isrRX( void )
{
    I_ISPC = BIT_URXD0;
	switch( URXH0 )
	{
		case '1':
			latidosPorMin = ( latidosPorMin < 255 ? latidosPorMin+1 : latidosPorMin );
		    TCNTB3  = cntb[latidosPorMin];                             // Carga T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 17);   // Modo interval, carga TCNT3, stop T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 16);   // Modo interval, no carga TCNT3, start T3
			uart0int_putMenu();
			break;
		case '2':
			latidosPorMin = ( latidosPorMin <= 245 ? latidosPorMin+10 : latidosPorMin );
		    TCNTB3  = cntb[latidosPorMin];                             // Carga T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 17);   // Modo interval, carga TCNT3, stop T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 16);   // Modo interval, no carga TCNT3, start T3
			uart0int_putMenu();
			break;
		case '3':
			latidosPorMin = ( latidosPorMin > 28 ? latidosPorMin-1 : latidosPorMin );
		    TCNTB3  = cntb[latidosPorMin];                             // Carga T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 17);   // Modo interval, carga TCNT3, stop T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 16);   // Modo interval, no carga TCNT3, start T3
		    uart0int_putMenu();
			break;
		case '4':
			latidosPorMin = ( latidosPorMin >= 38 ? latidosPorMin-10 : latidosPorMin );
		    TCNTB3  = cntb[latidosPorMin];                             // Carga T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 17);   // Modo interval, carga TCNT3, stop T3
		    TCON    = (TCON & ~(0xf << 16)) | (1 << 19) | (1 << 16);   // Modo interval, no carga TCNT3, start T3
			uart0int_putMenu();
			break;
		case 'd':
		case 'D':
			pasosPorMin = 0;
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
			INTMSK |= BIT_TIMER2;
		    uart0int_putMenu();
			break;
		case 'a':
		case 'A':
			pasosPorMin = 10;
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
		    INTMSK &= ~BIT_TIMER2;
			uart0int_putMenu();
			break;
		case '5':
			pasosPorMin = ( pasosPorMin != 0 && pasosPorMin < 200 ? pasosPorMin+1 : pasosPorMin );
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
			uart0int_putMenu();
			break;
		case '6':
			pasosPorMin = ( pasosPorMin != 0 && pasosPorMin <= 190 ? pasosPorMin+10 : pasosPorMin );
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
		    uart0int_putMenu();
			break;
		case '7':
			pasosPorMin = ( pasosPorMin != 0 && pasosPorMin > 10 ? pasosPorMin-1 : pasosPorMin );
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
			uart0int_putMenu();
			break;
		case '8':
			pasosPorMin = ( pasosPorMin != 0 && pasosPorMin >= 20 ? pasosPorMin-10 : pasosPorMin );
		    TCNTB2  = cntb[pasosPorMin];                               // Carga T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 13);   // Modo interval, carga TCNT2, stop T2
		    TCON    = (TCON & ~(0xf << 12)) | (1 << 15) | (1 << 12);   // Modo interval, no carga TCNT2, start T2
			uart0int_putMenu();
			break;
	    case '\n':
			break;
		default:
			uart0int_putMenu();
			break;
	}

}

/*******************************************************************/

void fifo_init( fifo_t *pfifo )
{
	pfifo->head = 0;
	pfifo->tail = 0;
	pfifo->size = 0;
}

void fifo_enqueue( fifo_t *pfifo, uint8 data )
{
	pfifo->buffer[pfifo->tail++] = data;
	if( pfifo->tail == FIFO_SIZE )
		pfifo->tail = 0;
	INT_DISABLE;
	pfifo->size++;
	INT_ENABLE;
}

void fifo_dequeue( fifo_t *pfifo, uint8 *data )
{
	*data = pfifo->buffer[pfifo->head++];
	if( pfifo->head == FIFO_SIZE )
		pfifo->head = 0;
	INT_DISABLE;
	pfifo->size--;
	INT_ENABLE;
}

boolean fifo_is_empty( fifo_t *pfifo )
{
	return (pfifo->size == 0);
}

boolean fifo_is_full( fifo_t *pfifo )
{
	return (pfifo->size == FIFO_SIZE-1);
}

/*******************************************************************/
