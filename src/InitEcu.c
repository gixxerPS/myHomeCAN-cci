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
    case InterfaceUnit:
	  //Outputs
	  DigOutArray_t[0].Output = DO_01;
	  DigOutArray_t[0].Number = PC0;
	  DigOutArray_t[0].Port = &PORTC;
	  DigOutArray_t[0].DDReg = &DDRC;
	  
	  DigOutArray_t[1].Output = DO_02;
	  DigOutArray_t[1].Number = PC1;
	  DigOutArray_t[1].Port = &PORTC;
	  DigOutArray_t[1].DDReg = &DDRC;

	  DigOutArray_t[2].Output = DO_03;
	  DigOutArray_t[2].Number = PC2;
	  DigOutArray_t[2].Port = &PORTC;
	  DigOutArray_t[2].DDReg = &DDRC;
	  
	  DigOutArray_t[3].Output = DO_04;
	  DigOutArray_t[3].Number = PC3;
	  DigOutArray_t[3].Port = &PORTC;
	  DigOutArray_t[3].DDReg = &DDRC;
    
	  DigOutArray_t[4].Output = DO_05;
	  DigOutArray_t[4].Number = PE7;
	  DigOutArray_t[4].Port = &PORTE;
	  DigOutArray_t[4].DDReg = &DDRE;
	  
	  DigOutArray_t[5].Output = DO_06;
	  DigOutArray_t[5].Number = PE6;
	  DigOutArray_t[5].Port = &PORTE;
	  DigOutArray_t[5].DDReg = &DDRE;

	  DigOutArray_t[6].Output = DO_07;
	  DigOutArray_t[6].Number = PE5;
	  DigOutArray_t[6].Port = &PORTE;
	  DigOutArray_t[6].DDReg = &DDRE;
	  
	  DigOutArray_t[7].Output = DO_08;
	  DigOutArray_t[7].Number = PE4;
	  DigOutArray_t[7].Port = &PORTE;
	  DigOutArray_t[7].DDReg = &DDRE;
	  
	  DigOutArray_t[8].Output = DO_09;
	  DigOutArray_t[8].Number = PE3;
	  DigOutArray_t[8].Port = &PORTE;
	  DigOutArray_t[8].DDReg = &DDRE;
	  
	  DigOutArray_t[9].Output = DO_10;
	  DigOutArray_t[9].Number = PE2;
	  DigOutArray_t[9].Port = &PORTE;
	  DigOutArray_t[9].DDReg = &DDRE;
	  
	  DigOutArray_t[10].Output = DO_11;
	  DigOutArray_t[10].Number = PE1;
	  DigOutArray_t[10].Port = &PORTE;
	  DigOutArray_t[10].DDReg = &DDRE;
	  
	  DigOutArray_t[11].Output = DO_12;
	  DigOutArray_t[11].Number = PE0;
	  DigOutArray_t[11].Port = &PORTE;
	  DigOutArray_t[11].DDReg = &DDRE;
	  
    /*--------------- Further outputs only for Power Unit --------*/
    
    DigOutArray_t[12].Output = DO_13;
	  DigOutArray_t[12].Number = PD4; 
	  DigOutArray_t[12].Port = &PORTD;
	  DigOutArray_t[12].DDReg = &DDRD;
	  
	  DigOutArray_t[13].Output = DO_14;
	  DigOutArray_t[13].Number = PD5;
	  DigOutArray_t[13].Port = &PORTD;
	  DigOutArray_t[13].DDReg = &DDRD;
	  
	  DigOutArray_t[14].Output = DO_15;
	  DigOutArray_t[14].Number = PD6;
	  DigOutArray_t[14].Port = &PORTD;
	  DigOutArray_t[14].DDReg = &DDRD;
	  
	  DigOutArray_t[15].Output = DO_16;
	  DigOutArray_t[15].Number = PD7;
	  DigOutArray_t[15].Port = &PORTD;
	  DigOutArray_t[15].DDReg = &DDRD;
	  
	  //Init Outputs
    if (CCiConfig_t.FctId == PowerUnit) //16 Outputs for Power Unit
    { 
      for (uint8_t i = 0; i< DO_16; i++)
	    {
	      *DigOutArray_t[i].DDReg |= (1<<DigOutArray_t[i].Number);
	    }
    }    
    if (CCiConfig_t.FctId == PowerUnit) break;    // Further commands only for Interface unit
    
    
    if (CCiConfig_t.FctId == InterfaceUnit)  //12 outputs for interface unit
    { 
      for (uint8_t i = 0; i< DO_12; i++)
	    {
	      *DigOutArray_t[i].DDReg |= (1<<DigOutArray_t[i].Number);
	    }
    }
    
    //Inputs
	  DigInArray_t[0].Input = DI_01;
	  DigInArray_t[0].Number = PC4; 
	  DigInArray_t[0].Port = &PORTC;
    DigInArray_t[0].Pin = &PINC;
	  DigInArray_t[0].DDReg = &DDRC;
	  
	  DigInArray_t[1].Input = DI_02;
	  DigInArray_t[1].Number = PC5;
	  DigInArray_t[1].Port = &PORTC;
    DigInArray_t[1].Pin = &PINC;
	  DigInArray_t[1].DDReg = &DDRC;
	  
	  DigInArray_t[2].Input = DI_03;
	  DigInArray_t[2].Number = PC6;
	  DigInArray_t[2].Port = &PORTC;
    DigInArray_t[2].Pin = &PINC;
	  DigInArray_t[2].DDReg = &DDRC;
	  
	  DigInArray_t[3].Input = DI_04;
	  DigInArray_t[3].Number = PC7;
	  DigInArray_t[3].Port = &PORTC;
    DigInArray_t[3].Pin = &PINC;
	  DigInArray_t[3].DDReg = &DDRC;
	  
	  DigInArray_t[4].Input = DI_05;
	  DigInArray_t[4].Number = PA0;
	  DigInArray_t[4].Port = &PORTA;
    DigInArray_t[4].Pin = &PINA;
	  DigInArray_t[4].DDReg = &DDRA;
	  
	  DigInArray_t[5].Input = DI_06;
	  DigInArray_t[5].Number = PA1;
	  DigInArray_t[5].Port = &PORTA;
    DigInArray_t[5].Pin = &PINA;
	  DigInArray_t[5].DDReg = &DDRA;

	  DigInArray_t[6].Input = DI_07;
	  DigInArray_t[6].Number = PA2;
	  DigInArray_t[6].Port = &PORTA;
    DigInArray_t[6].Pin = &PINA;
	  DigInArray_t[6].DDReg = &DDRA;
	  
	  DigInArray_t[7].Input = DI_08;
	  DigInArray_t[7].Number = PA3;
	  DigInArray_t[7].Port = &PORTA;
    DigInArray_t[7].Pin = &PINA;
	  DigInArray_t[7].DDReg = &DDRA;
	  
	  DigInArray_t[8].Input = DI_09;
	  DigInArray_t[8].Number = PA4;
	  DigInArray_t[8].Port = &PORTA;
    DigInArray_t[8].Pin = &PINA;
	  DigInArray_t[8].DDReg = &DDRA;
	  
	  DigInArray_t[9].Input = DI_10;
	  DigInArray_t[9].Number = PA5;
	  DigInArray_t[9].Port = &PORTA;
    DigInArray_t[9].Pin = &PINC;
	  DigInArray_t[9].DDReg = &DDRA;
	  
	  DigInArray_t[10].Input = DI_11;
	  DigInArray_t[10].Number = PA6;
	  DigInArray_t[10].Port = &PORTA;
    DigInArray_t[10].Pin = &PINA;
	  DigInArray_t[10].DDReg = &DDRA;
	  
	  DigInArray_t[11].Input = DI_12;
	  DigInArray_t[11].Number = PA7;
	  DigInArray_t[11].Port = &PORTA;
    DigInArray_t[11].Pin = &PINA;
	  DigInArray_t[11].DDReg = &DDRA;
    
    if (CCiConfig_t.FctId == InterfaceUnit)  //12 inputs for interface unit
    {
      for (uint8_t i = 0; i< DI_12; i++)
      {
        *DigInArray_t[i].DDReg &= ~((char) 1 << DigInArray_t[i].Number); // configure pin as input
        *DigInArray_t[i].Port |= (1<<DigInArray_t[i].Number); // Set Pull Up      
      }
    }
    
    break; 
	  
    default:
	  break;	
    
    
  }

 /* STATUS LED */
  DDRB |= (1 << STATUS_LED);
  return;	
}


void InitTimer(void)
{
  // Timer1 (16bit) overflow interrupt used for alive handling
  // Timer0 (8Bit) overflow interrupt used for test mode
  
  //Timer1
  TCCR1B |= ( 1<<CS11 )|( 1<<CS10 );  // counter1,Prescaler auf 256 (ca. 260ms per overflow)
  //Timer 0
  TCCR0 |= (1<<CS02)|( 1<<CS01 )|( 1<<CS00 );  // counter0,Prescaler auf 1024 (ca. 60Hz Overflow)
  OCR0 = 156; // 1 / 16MHz * 156 (otuput compare interrupt) * 1024 (Prescaler Timer 0) -> 10ms
  TCNT0 = 0; // Reset timer inital
  
  TIMSK |= ( 1<<TOIE1 ) | ( 1<< OCIE0 ); // enable counter1 overflow interrupt	and Timer 0 output compare	
}

void InitISR(void)
{
//  GICR = 1<<INT0;					// Enable INT0
//  MCUCR = 1<<ISC01 | 0<<ISC00;	// Trigger INT0 on falling edge
  sei();                 // Interrupts global aktivieren	
}