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

can_t AliveMsg;
char AliveCounter_u8 = 0;	


ISR( TIMER1_OVF_vect ) 
{
   // Nachricht verschicken
	AliveMsg.data[2] = (char)AliveCounter_u8;
	can_send_message(&AliveMsg);
	AliveCounter_u8 +=1;
}

ISR(INT0_vect)
{
  if (PORTD & ((char)1<<PD7)) {
    PORTD &= ~((char)1<<PIND7); // set LED OFF
  }
  else
  {
    PORTD |= (1<<PD7); // set LED ON
  }
  can_check_message();
  can_get_message( &AliveMsg);
}

int main (void)
{	  
	/* Insert system clock initialization code here (sysclk_init()). */
    InitI0I();
    InitTimer();
    InitISR();
	_delay_ms(10);
	GetNodeId();
	GetFctId();
	can_init(BITRATE_125_KBPS);
	

	AliveMsg.id = CCiConfig_t.FctId | (CCiConfig_t.NodeId_u8<<3);
	AliveMsg.flags.rtr = 0;
	AliveMsg.flags.extended = 0;
	
	AliveMsg.length = 3;
	AliveMsg.data[0] = CCiConfig_t.FctId;
	AliveMsg.data[1] = CCiConfig_t.NodeId_u8;
	AliveMsg.data[2] = (char)AliveCounter_u8;


	
	for(;;)
	{
		_delay_ms(500);
	}
	

	/* Insert application code here, after the board has been initialized. */
}
