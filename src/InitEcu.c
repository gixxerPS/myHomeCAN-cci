/*
 * InitEcu.c
 *
 * Created: 14.03.2017 19:15:18
 *  Author: Mark Roters
 */ 
#include <avr/io.h>
#include "InitEcu.h"
#include "CciConfig.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void InitI0I(void)
{

  switch (CCiConfig_t.FctId)
  {
    case PowerUnit:
	  //Outputs
	  DigOutArray_t[0].Output = DO_01;
	  DigOutArray_t[0].Number = PD7; 
	  DigOutArray_t[0].Port = &PORTD;
	  DigOutArray_t[0].DDReg = &DDRD;
	  
	  DigOutArray_t[1].Output = DO_02;
	  DigOutArray_t[1].Number = PD7;
	  DigOutArray_t[1].Port = &PORTD;
	  DigOutArray_t[1].DDReg = &DDRD;
	  
	  DigOutArray_t[2].Output = DO_03;
	  DigOutArray_t[2].Number = PD7;
	  DigOutArray_t[2].Port = &PORTD;
	  DigOutArray_t[2].DDReg = &DDRD;
	  
	  DigOutArray_t[3].Output = DO_04;
	  DigOutArray_t[3].Number = PD7;
	  DigOutArray_t[3].Port = &PORTD;
	  DigOutArray_t[3].DDReg = &DDRD;
	  
	  DigOutArray_t[4].Output = DO_05;
	  DigOutArray_t[4].Number = PD7;
	  DigOutArray_t[4].Port = &PORTD;
	  DigOutArray_t[4].DDReg = &DDRD;
	  
	  DigOutArray_t[5].Output = DO_06;
	  DigOutArray_t[5].Number = PD7;
	  DigOutArray_t[5].Port = &PORTD;
	  DigOutArray_t[5].DDReg = &DDRD;

	  DigOutArray_t[6].Output = DO_07;
	  DigOutArray_t[6].Number = PD7;
	  DigOutArray_t[6].Port = &PORTD;
	  DigOutArray_t[6].DDReg = &DDRD;
	  
	  DigOutArray_t[7].Output = DO_08;
	  DigOutArray_t[7].Number = PD7;
	  DigOutArray_t[7].Port = &PORTD;
	  DigOutArray_t[7].DDReg = &DDRD;
	  
	  DigOutArray_t[8].Output = DO_09;
	  DigOutArray_t[8].Number = PD7;
	  DigOutArray_t[8].Port = &PORTD;
	  DigOutArray_t[8].DDReg = &DDRD;
	  
	  DigOutArray_t[9].Output = DO_10;
	  DigOutArray_t[9].Number = PD7;
	  DigOutArray_t[9].Port = &PORTD;
	  DigOutArray_t[9].DDReg = &DDRD;
	  
	  DigOutArray_t[10].Output = DO_11;
	  DigOutArray_t[10].Number = PD7;
	  DigOutArray_t[10].Port = &PORTD;
	  DigOutArray_t[10].DDReg = &DDRD;
	  
	  DigOutArray_t[11].Output = DO_12;
	  DigOutArray_t[11].Number = PD7;
	  DigOutArray_t[11].Port = &PORTD;
	  DigOutArray_t[11].DDReg = &DDRD;
	  
	  DigOutArray_t[12].Output = DO_13;
	  DigOutArray_t[12].Number = PD7;
	  DigOutArray_t[12].Port = &PORTD;
	  DigOutArray_t[12].DDReg = &DDRD;
	  
	  DigOutArray_t[13].Output = DO_14;
	  DigOutArray_t[13].Number = PD7;
	  DigOutArray_t[13].Port = &PORTD;
	  DigOutArray_t[13].DDReg = &DDRD;

	  DigOutArray_t[14].Output = DO_15;
	  DigOutArray_t[14].Number = PD7;
	  DigOutArray_t[14].Port = &PORTD;
	  DigOutArray_t[14].DDReg = &DDRD;
	  
	  DigOutArray_t[15].Output = DO_16;
	  DigOutArray_t[15].Number = PD7;
	  DigOutArray_t[15].Port = &PORTD;
	  DigOutArray_t[15].DDReg = &DDRD;
	  
	  //Init Outputs
      for (uint8_t i = 0; i< DO_16; i++)
	  {
	    *DigOutArray_t[i].DDReg |= (1<<DigOutArray_t[i].Number);
	  }
	  
      break;	
	  
	case InterfaceUnit:
	  //Inputs

      break;
	  
    default:
	  break;	
  }


	  
  DDRD &= ~((char)1<<PIND2); // Interrupt PIn as Input
  
  DDRA = 0; // ALL Inputs (DIP switches)
  PORTA = ALL_PORTS_ON; //All Pull UPs on  	
}


void InitTimer(void)
{
  TCCR1B |= ( 1<<CS12 )|( 0<<CS10 );  // counter0,Prescaler auf 1024
  TIMSK |= ( 1<<TOIE1 ); // enable counter0 overflow interrupt		
}

void InitISR(void)
{
  GICR = 1<<INT0;					// Enable INT0
  MCUCR = 1<<ISC01 | 0<<ISC00;	// Trigger INT0 on falling edge
  sei();                 // Interrupts global aktivieren	
}