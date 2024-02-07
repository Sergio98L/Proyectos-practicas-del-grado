
#include <s3c44b0x.h>
#include <s3cev40.h>
#include <timers.h>
#include <adc.h>
#include <lcd.h>
#include <ts.h>

#define PX_ERROR    (5)

static uint16 Vxmin = 0;
static uint16 Vxmax = 0;
static uint16 Vymin = 0;
static uint16 Vymax = 0;

static uint8 state;

extern void isr_TS_dummy( void );

static void ts_scan( uint16 *Vx, uint16 *Vy );
static void ts_calibrate( void );
static void ts_sample2coord( uint16 Vx, uint16 Vy, uint16 *x, uint16 *y );

void ts_init( void )
{
	timers_init();
	lcd_init();
	adc_init();
	PDATE = (0xb<<4);
	sw_delay_ms( 1 );
	ts_on();
	ts_calibrate();
	ts_off();
}

void ts_on( void )
{
    adc_on();
    state=ON;
}

void ts_off( void )
{
    adc_off();
    state=OFF;
}

uint8 ts_status( void )
{
    return state;
}

uint8 ts_pressed( void )
{
    return !(PDATG & (1<<2));
}

static void ts_calibrate( void )
{
	uint16 x, y;
	lcd_on();
	do {
		lcd_clear();
		lcd_puts_x2(70,10,15, "CALIBRACION");
		sw_delay_ms(1000);
		lcd_clear();
		lcd_puts_x2(85,10,15, "PRESIONA");
		lcd_draw_box(0,0,5,5,15,4);
		while( !ts_pressed() );
		sw_delay_ms( TS_DOWN_DELAY );
		ts_scan( &Vxmin, &Vymax );
		while( ts_pressed());
		sw_delay_ms( TS_UP_DELAY );
		lcd_clear();
		lcd_puts_x2(85,10,15, "PRESIONA");
		lcd_draw_box(314,234,319,239,15,4);

		while( !ts_pressed() );
		sw_delay_ms( TS_DOWN_DELAY );
		ts_scan( &Vxmax, &Vymin );
		while( ts_pressed() );
		sw_delay_ms( TS_UP_DELAY );
		lcd_puts_x2(85,10,15, "PRESIONA");
		lcd_draw_box(160,120,165,125,15,4);
		ts_getpos( &x, &y );
    } while( (x > LCD_WIDTH/2+PX_ERROR) || (x < LCD_WIDTH/2-PX_ERROR) || (y > LCD_HEIGHT/2+PX_ERROR) || (y < LCD_HEIGHT/2-PX_ERROR) );
    lcd_clear();
}

void ts_getpos( uint16 *x, uint16 *y )
{
	uint16 Vx, Vy;
	    while( !ts_pressed() );
	    sw_delay_ms( TS_DOWN_DELAY );

	    ts_scan(&Vx, &Vy);
	    ts_sample2coord(Vx,Vy,x,y);

	    while ( ts_pressed() );
	    sw_delay_ms( TS_UP_DELAY );
}

void ts_getpostime( uint16 *x, uint16 *y, uint16 *ms )
{
	 while( !ts_pressed() );
	    timer3_start();
	    sw_delay_ms( TS_DOWN_DELAY );

	    uint16 Vx, Vy;
	    ts_scan(&Vx, &Vy);
	    ts_sample2coord(Vx,Vy,x,y);

	    while ( ts_pressed() );
		*ms=timer3_stop()/10;
	    sw_delay_ms( TS_UP_DELAY );
}

uint8 ts_timeout_getpos( uint16 *x, uint16 *y, uint16 ms )
{
	timer3_start_timeout(ms*10);

		while( !ts_pressed() && !timer3_timeout() );
		if (timer3_timeout( )) return TS_TIMEOUT;
		sw_delay_ms( TS_DOWN_DELAY );

	    uint16 Vx, Vy;
	    ts_scan(&Vx, &Vy);
	    ts_sample2coord(Vx,Vy,x,y);

		while ( ts_pressed() && !timer3_timeout() );
		if (timer3_timeout( )) return TS_TIMEOUT;
		sw_delay_ms( TS_UP_DELAY );
}

static void ts_scan( uint16 *Vx, uint16 *Vy )
{
	PDATE = (0x6<<4);
	*Vx = adc_getSample( ADC_AIN1 );

	PDATE = (0x9<<4);
	*Vy = adc_getSample( ADC_AIN0 );

	PDATE = (0xb<<4);
	sw_delay_ms( 1 );
}

static void ts_sample2coord( uint16 Vx, uint16 Vy, uint16 *x, uint16 *y )
{
	if( Vx < Vxmin )
	        *x = 0;
	    else if( Vx > Vxmax )
	        *x = LCD_WIDTH-1;
	    else
	        *x = LCD_WIDTH*(Vx-Vxmin) / (Vxmax-Vxmin);

	    if( Vy < Vymin )
	         *y = 0;
		else if( Vy > Vymax )
			*y = LCD_HEIGHT-1;
		else
	        *y = LCD_HEIGHT-(LCD_HEIGHT*(Vy-Vymin) / (Vymax-Vymin));
}

void ts_open( void (*isr)(void) )
{
	pISR_TS  = isr;
	I_ISPC	 = BIT_TS;
	INTMSK	&= ~(BIT_GLOBAL|BIT_TS);
}

void ts_close( void )
{
	INTMSK	|= BIT_TS;
	pISR_TS = isr_TS_dummy;
}


