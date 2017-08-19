/*
 * CciConfig.c
 *
 * Created: 14.03.2017 19:26:30
 *  Author: Mark Roters
 */ 

#include "CciConfig.h"
#include <avr/io.h>
#include <util/delay.h>

void GetUnitId(void)
{
  #define NODE_ID_BITS 0b00011111 

  /* DIP Switches */
  PORTG |= (1<<PG1) | (1<<PG2) | (1<<PG3) | (1<<PG4) | (1<<PG0);  //Pull UPs on
	_delay_ms(10);
  
	CCiConfig_t.UnitId_u8 = (~PING & NODE_ID_BITS);
	//CCiConfig_t.UnitId_u8 = CCiConfig_t.UnitId_u8 >> 3;
			
}
	
void GetFctId(void)
{
	#define FCT_ID_BITS 0b00000111
  
  /* DIP Switches */
  PORTF |= (1<<PF0) | (1<<PF1) | (1<<PF2) ;  // Pull UPs on
  _delay_ms(10);
  
	switch (~PINF & FCT_ID_BITS)
	{
		case SensorUnit:
		CCiConfig_t.FctId = SensorUnit;
		break;
		
		case PowerUnit:
		CCiConfig_t.FctId = PowerUnit;
		break;
		
		case InterfaceUnit:
		CCiConfig_t.FctId = InterfaceUnit;
		break;
		
		default:
		CCiConfig_t.FctId = NotConfigured;
	}	
}