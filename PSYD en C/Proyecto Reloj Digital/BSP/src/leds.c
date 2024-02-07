#include <s3c44b0x.h>
#include <leds.h>

void leds_init( void )
{
	PCONB &= ~( (1<<9) | (1<<10) );
	led_off(LEFT_LED);
	led_off(RIGHT_LED);
}

void led_on( uint8 led )
{
	if(led == LEFT_LED){
		PDATB &= ~(1<<9);
	} else {
		PDATB &= ~(1<<10);
	}
}

void led_off( uint8 led )
{
	if(led == LEFT_LED){
		PDATB |= (1<<9);
	} else {
		PDATB |= (1<<10);
	}
}

void led_toggle( uint8 led )
{
	if(led == LEFT_LED){
			PDATB ^= (1<<9);
		} else {
			PDATB ^= (1<<10);
		}
}

uint8 led_status( uint8 led )
{
	if(led == LEFT_LED){
		if (PDATB & (1<<9))
			return 0;//apagado
		else{
			return 1;//encendido
		}
	} else {
		if (PDATB & (1<<10))
			return 0;//apagado
		else{
			return 1;//encendido
		}
	}
}
