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
  uint8_t UnitIdTmp_u8;
                     
  #define NODE_ID_BITS_PORTG 0b00011000 
  #define NODE_ID_BITS_PORTB 0b11100000 

  /* DIP Switches */
  DDRG &= ~((char) 1 << PG3); // configure pin as input
  DDRG &= ~((char) 1 << PG4); // configure pin as input
  DDRB &= ~((char) 1 << PB5); // configure pin as input
  DDRB &= ~((char) 1 << PB6); // configure pin as input
  DDRB &= ~((char) 1 << PB7); // configure pin as input
  
  PORTG |= (1<<PG3) | (1<<PG4);  //Pull UPs on
  PORTB |= (1<<PB5) | (1<<PB6) | (1<<PB7);  //Pull UPs on
	_delay_ms(10);
  
  UnitIdTmp_u8 = ((~PING & (1<<PG3) ) >> 2) + ((~PING & (1<<PG4) ) >> 4);       //2,1
  UnitIdTmp_u8 = UnitIdTmp_u8 + ((~PINB & (1<<PB5) ) >> 1) + ((~PINB & (1<<PB6) ) >> 3) + ((~PINB & (1<<PB7) ) >> 5);  //16,8,4
  
	CCiConfig_t.UnitId_u8 = UnitIdTmp_u8;		

}
	
void GetFctId(void)
{
  uint8_t FctIdtmp_u8;
  
	#define FCT_ID_BITS_PORTA 0b00000001
  #define FCT_ID_BITS_PORTF 0b00000011
  
  DDRF &= ~((char) 1 << PF1); // configure pin as input
  DDRF &= ~((char) 1 << PF0); // configure pin as input
  DDRA &= ~((char) 1 << PA0); // configure pin as input
    
  /* DIP Switches */
  PORTF |= (1<<PF1) | (1<<PF0);  // Pull UPs on
  PORTA |= (1<<PA0); // Pull UPs on
  _delay_ms(10);


if (1)
{
  FctIdtmp_u8 = ((~PINF) & FCT_ID_BITS_PORTF);
  FctIdtmp_u8 |= ((~PINA) & FCT_ID_BITS_PORTA) << 2;
  
  switch (FctIdtmp_u8)
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
}