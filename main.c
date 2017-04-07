/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

//#define F_CPU 16000000UL

#include "InitEcu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "can.h"
#include "CciConfig.h"
#include "Identifier.h"
#include "PowerUnit.h"

can_t AliveMsg;


ISR( TIMER1_OVF_vect ) 
{
   // Alive inkrement
	AliveMsg.data[3] +=1;
}

ISR(INT0_vect)
{
  if (DigOutArray_t[0].State == 0)
  {
	DigOutArray_t[0].State = 1;
	SetDigitalOutput( &DigOutArray_t[0] );
  }
  else
  {
	DigOutArray_t[0].State = 0;
	SetDigitalOutput( &DigOutArray_t[0] );  
  }
  can_check_message();
}

int main (void)
{	  
	/* Insert system clock initialization code here (sysclk_init()). */
	Identifier_t AliveId_t;
	uint8_t OldAliveCounter_u8 = 255;
	
    InitTimer();
    InitISR(); //Timer and IO Interrupt
	_delay_ms(10);
	GetUnitId(); //0 - 31
	GetFctId(); //Sensor Unit, Power Unit, Interface Unit
	InitI0I();
	can_init(BITRATE_125_KBPS);
	
	AliveId_t.Number_u8 = 0;
	AliveId_t.SrcFct_u8 = CCiConfig_t.FctId;
	AliveId_t.SrcId_u8 = CCiConfig_t.UnitId_u8;
	AliveId_t.TargetFct_u8 = 0;
	AliveId_t.TargetId_u8 = 0;
	AliveId_t.Prio_u8 = 0;
	
	AliveMsg.id = BuildIdentifier( AliveId_t);
	AliveMsg.flags.rtr = 0;
	AliveMsg.flags.extended = 1;
	AliveMsg.length = 8;
	AliveMsg.data[0] = VERSION_HIGH;
	AliveMsg.data[1] = VERSION_MID;
	AliveMsg.data[2] = VERSION_LOW;


	
	for(;;)
	{
	  if (OldAliveCounter_u8 != (uint8_t) AliveMsg.data[3]) // send new Alive message
	  {
		OldAliveCounter_u8 = AliveMsg.data[3];
		can_send_message(&AliveMsg);		  
	  }
	  
	  _delay_ms(50);
	}
	

	/* Insert application code here, after the board has been initialized. */
}
