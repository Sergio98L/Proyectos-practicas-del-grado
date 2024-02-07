
#include <s3c44b0x.h>
#include <s3cev40.h>
#include <rtc.h>

extern void isr_TICK_dummy( void );

void rtc_init( void )
{
	TICNT   = 0x80;
	RTCALM  = 0x0;
	RTCRST  = 0x0;
        
	RTCCON  |= (1<<0);

	BCDYEAR = 0x13;
	BCDMON  = 0x01;
	BCDDAY  = 0x01;
	BCDDATE = 0x02;
	BCDHOUR = 0x00;
	BCDMIN  = 0x00;
	BCDSEC  = 0x00;

	ALMYEAR = 0x00;
	ALMMON  = 0x00;
	ALMDAY  = 0x00;
	ALMHOUR = 0x00;
	ALMMIN  = 0x00;
	ALMSEC  = 0x00;

	RTCCON &= ~(1<<0);
}

void rtc_puttime( rtc_time_t *rtc_time )
{
	RTCCON |= (1<<0);

	BCDYEAR = 	((rtc_time->year/10)<<4)|(rtc_time->year%10);
	BCDMON  = 	((rtc_time->mon/10)<<4)|(rtc_time->mon%10);
	BCDDAY  = 	((rtc_time->mday/10)<<4)|(rtc_time->mday%10);
	BCDDATE = 	((rtc_time->wday/10)<<4)|(rtc_time->wday%10);
	BCDHOUR =	((rtc_time->hour/10)<<4)|(rtc_time->hour%10);
	BCDMIN  =	((rtc_time->min/10)<<4)|(rtc_time->min%10);
	BCDSEC  =	((rtc_time->sec/10)<<4)|(rtc_time->sec%10);

	RTCCON &= ~(1<<0);
}

void rtc_gettime( rtc_time_t *rtc_time )
{
    RTCCON |= (1<<0);

      rtc_time->year = (BCDYEAR & 15) + (BCDYEAR >> 4)*10;
      rtc_time->mon  =  (BCDMON & 15) + (BCDMON>> 4)*10;
      rtc_time->mday = (BCDDAY & 15) + (BCDDAY >> 4)*10;
      rtc_time->wday = (BCDDATE & 15) + (BCDDATE >> 4)*10;
      rtc_time->hour = (BCDHOUR & 15) + (BCDHOUR >> 4)*10;
      rtc_time->min  = (BCDMIN & 15) + (BCDMIN >> 4)*10;
      rtc_time->sec  = (BCDSEC & 15) + (BCDSEC >> 4)*10;
      if( ! rtc_time->sec ){
          rtc_time->year = (BCDYEAR & 15) + (BCDYEAR >> 4)*10;
          rtc_time->mon  =  (BCDMON & 15) + (BCDMON>> 4)*10;
          rtc_time->mday = (BCDDAY & 15) + (BCDDAY >> 4)*10;
          rtc_time->wday = (BCDDATE & 15) + (BCDDATE >> 4)*10;
          rtc_time->hour = (BCDHOUR & 15) + (BCDHOUR >> 4)*10;
          rtc_time->min  = (BCDMIN & 15) + (BCDMIN >> 4)*10;
          rtc_time->sec  = (BCDSEC & 15) + (BCDSEC >> 4)*10;
      }
    RTCCON &= ~(1<<0);
}


void rtc_open( void (*isr)(void), uint8 tick_count )
{
    pISR_TICK = (uint32) isr;
    I_ISPC    = BIT_TICK;
    INTMSK   &= ~(BIT_TICK | BIT_GLOBAL);
    TICNT     = (1<<7)|(tick_count);
}

void rtc_close( void )
{
    TICNT     = 0x00;
    INTMSK   |= BIT_TICK;
    pISR_TICK = (uint32) isr_TICK_dummy;

}
