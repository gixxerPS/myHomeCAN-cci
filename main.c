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

#define F_CPU 16000000UL
#define TEST_MODE  0b11111

#include "InitEcu.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "can.h"
#include "CciConfig.h"
#include "Identifier.h"
#include "PowerUnit.h"
#include "InterfaceUnit.h"
#include "TestMode.h"
 
  can_t AliveMsg;
  can_t CommandReceiveMsg;
  can_t DigitInputStateMsg;

  Identifier_t AliveId_t;
  Identifier_t RxIdentifier_t;
  Identifier_t TxIdentifier_t;

  volatile uint8_t test_u8 = 0;

  ISR( TIMER1_OVF_vect ) //ca. 260ms
  {
    static uint8_t inkr_u8 = 0;;
    static uint8_t LedState_u8;
    
    inkr_u8++;
    QuarterSecondCounter_u8++;

    
    // Alive inkrement
    if (!(inkr_u8 % 4))   //ca.1s
    {
      AliveMsg.data[4] ++;
    }
    
    if ( CCiConfig_t.UnitId_u8 != TEST_MODE)
    {
      if ( LedState_u8 == 0)  //Power ON
      {
        SET_STATUS_LED();
        LedState_u8 = 1;
      }
      else
      {
        RESET_STATUS_LED();
        LedState_u8 = 0;
      }  
    }
  }
  
  ISR( TIMER0_COMP_vect)
  {
    static uint8_t inkr_u8 = 0;
      
    TCNT0 = 0;
    
    if ( inkr_u8> 0 )
    {
      if ( (inkr_u8 % T50MS) == 0)
      {
        GlobalTimer.t50ms_u8++;
      }
      if ( (inkr_u8 % T100MS) == 0)
      {
        GlobalTimer.t100ms_u8++;
      }
      if ( (inkr_u8 % T200MS) == 0)
      {
        GlobalTimer.t200ms_u8++;
      }       
      if ( (inkr_u8 % T500MS) == 0)
      {
        GlobalTimer.t500ms_u8++;
      }
      if ( (inkr_u8 % T1000MS) == 0)
      {
        GlobalTimer.t1000ms_u8++;
      } 
      if ( (inkr_u8 % T2000MS) == 0)
      {
        GlobalTimer.t2000ms_u8++;
      }       
    }
      
    if ( inkr_u8 < 200) // 200 * 10ms -> 2s
    {
      inkr_u8++;
    }
    else   // 2s reached
    {
      inkr_u8 = 0; 
    } 
  }

  ISR(INT0_vect)  // CAN Interrupt
  {
  }
  


int main (void)
{	  
	/* Insert system clock initialization code here (sysclk_init()). */
	uint8_t OldAliveCounter_u8 = 255;
  _delay_ms(1000);
  InitTimer();
  InitISR();   // Timer and IO Interrupt
  GetUnitId(); // 0 - 31
  GetFctId();  // Sensor Unit, Power Unit, Interface Unit
  InitI0I();   // depends on via DIP configured function
	_delay_ms(100);
  
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
   
  /* START: Content for Identifier */
  AliveMsg.flags.rtr = 0;
  AliveMsg.flags.extended = 1; //extendet ID
  AliveMsg.length = 8;         //DLC
  AliveMsg.data[7] = VERSION_HIGH;  //Software Version
  AliveMsg.data[6] = VERSION_MID;
  AliveMsg.data[5] = VERSION_LOW;
  /* END: Content for Identifier */

  /* START: Build identifier for Interface unit */
  if (CCiConfig_t.FctId == InterfaceUnit)
  {
    TxIdentifier_t.Number_u8 = 1;  // Interface message is message number 1
    TxIdentifier_t.SrcFct_u8 = CCiConfig_t.FctId; //as configured via DIP
    TxIdentifier_t.SrcId_u8 = CCiConfig_t.UnitId_u8;  //as configured via DIP
    TxIdentifier_t.TargetFct_u8 = Master;  // Master
    TxIdentifier_t.TargetId_u8 = 0;   // there´s only one master :-)
    TxIdentifier_t.Prio_u8 = 0;       // for future use
    
    DigitInputStateMsg.id = BuildIdentifier( TxIdentifier_t); // Build identifier
  }
  

  /* END: Build identifier for interface unit */

  DigitInputStateMsg.flags.rtr = 0;
  DigitInputStateMsg.flags.extended = 1; //extendet ID
  DigitInputStateMsg.length = 8;         //DLC
 

	
	for(;;)
	{ 
    
    /* ------------------------ALIVE--------------------------------*/
  	if (OldAliveCounter_u8 != (uint8_t) AliveMsg.data[4]) // send new Alive message because counter has changed
  	{                                                                                         
    	OldAliveCounter_u8 = AliveMsg.data[4];
    	can_send_message(&AliveMsg);  // Send alive Message
  	}
  	
  	/*-----------------SEND STATES----------------------------------*/
  	if (CCiConfig_t.FctId == InterfaceUnit)
  	{
    	if ( true == GetAllDigitalInputStates()) // Read digital inputs an send message if function return true (changed input state)
    	{
      	SendDigitalInputStates(&DigitInputStateMsg);    	
    	}
  	}

    /*--------------------TEST MODE-----------------------------*/
    if ( CCiConfig_t.UnitId_u8 == TEST_MODE)  // UnitId only checked once at startup
    {             
      if (CCiConfig_t.FctId == InterfaceUnit)
      {
        InputCheck();  // if only one input is active, LED blinks fast. If more than one input is active LED blinks very fast
        OutputCheck(); // if no inputs active, cci switches outputs (1 output / 2 seconds)                    
      }
      else if (CCiConfig_t.FctId == PowerUnit)
      {
        OutputCheck(); //cci switches outputs (1 output / 2 seconds) 
      }        
    }      
  	/*--------------------RECEIVE COMMANDS-----------------------------*/
  	else if ( can_get_message(&CommandReceiveMsg) )    //check for and read new message
  	{
    	RxIdentifier_t = ReadIdentifier( CommandReceiveMsg.id ); //received message identifier for unit command
    	
    	if (( RxIdentifier_t.TargetFct_u8 == CCiConfig_t.FctId ) && ( RxIdentifier_t.TargetId_u8 == CCiConfig_t.UnitId_u8 )) ///check: Message for this unit
    	{
      	switch (RxIdentifier_t.TargetFct_u8)
      	{
        	case PowerUnit:
        	SetPowerUnitOutputs(&CommandReceiveMsg);  // read output command and set outputs
        	break;
        	
        	case InterfaceUnit:
        	SetInterfaceUnitOutputs(&CommandReceiveMsg); // read output command and set outputs
        	break;
        	
        	default:
        	break;
      	}
    	}
  	} 
}

	

	/* Insert application code here, after the board has been initialized. */
}