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
can_t CommandReceiveMsg;

volatile uint8_t test_u8 = 0;

ISR( TIMER1_OVF_vect ) 
{
   // Alive inkrement
	AliveMsg.data[3] +=1;
}

ISR(INT0_vect)  // CAN Interrupt
{




    

}

int main (void)
{	  
	/* Insert system clock initialization code here (sysclk_init()). */
	Identifier_t AliveId_t;
  Identifier_t RxIdentifier_t;
	uint8_t OldAliveCounter_u8 = 255;
	
  InitTimer();
  InitISR();   // Timer and IO Interrupt
	_delay_ms(10);
	GetUnitId(); // 0 - 31
	GetFctId();  // Sensor Unit, Power Unit, Interface Unit
	InitI0I();   // depends on via DIP configured function
	can_init(BITRATE_125_KBPS);
	
/* START: Build Identifier for Alive message*/
	AliveId_t.Number_u8 = 0;  // Alive message is message number 0
	AliveId_t.SrcFct_u8 = CCiConfig_t.FctId; //as configured via DIP
	AliveId_t.SrcId_u8 = CCiConfig_t.UnitId_u8;  //as configured via DIP
	AliveId_t.TargetFct_u8 = 0;  // Broadcast
	AliveId_t.TargetId_u8 = 0;   // Broadcast
	AliveId_t.Prio_u8 = 0;       // for future use
	
	AliveMsg.id = BuildIdentifier( AliveId_t);
/* END: Build Identifier for Alive message*/

	AliveMsg.flags.rtr = 0;
	AliveMsg.flags.extended = 1; //extendet ID
	AliveMsg.length = 8;         //DLC
	AliveMsg.data[0] = VERSION_HIGH;  //Software Version
	AliveMsg.data[1] = VERSION_MID;
	AliveMsg.data[2] = VERSION_LOW;


	
	for(;;)
	{
	  if (OldAliveCounter_u8 != (uint8_t) AliveMsg.data[3]) // send new Alive message
	  {
		  OldAliveCounter_u8 = AliveMsg.data[3];
		  can_send_message(&AliveMsg);  // Send alive Message		  
	  }


    if ( can_get_message(&CommandReceiveMsg) )    //check for and read new message
    {
      RxIdentifier_t = ReadIdentifier( CommandReceiveMsg.id ); //received message identifier for unit command
      
      if (( RxIdentifier_t.TargetFct_u8 == CCiConfig_t.FctId ) && ( RxIdentifier_t.TargetId_u8 == CCiConfig_t.UnitId_u8 )) ///check: Message for this unit
      {
        switch (RxIdentifier_t.TargetFct_u8)
        {
          case PowerUnit:
          SetPowerUnitOutputs(&CommandReceiveMsg);  // read output command and set outputs
          break;
                 
          default:
          break;
        }
      }
    }   
  }

	

	/* Insert application code here, after the board has been initialized. */
}
