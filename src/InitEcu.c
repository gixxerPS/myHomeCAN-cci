/*
 * InitEcu.c
 *
 * Created: 14.03.2017 19:15:18
 *  Author: Mark Roters
 */ 
#include <avr/io.h>
#include <avr/wdt.h>
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
   	  DigOutArray_t[0].Number = PC3;
   	  DigOutArray_t[0].Port = &PORTC;
      DigOutArray_t[0].Pin = &PINC;
   	  DigOutArray_t[0].DDReg = &DDRC;
   	  
   	  DigOutArray_t[1].Output = DO_02;
   	  DigOutArray_t[1].Number = PC2;
   	  DigOutArray_t[1].Port = &PORTC;
      DigOutArray_t[1].Pin = &PINC;
   	  DigOutArray_t[1].DDReg = &DDRC;

   	  DigOutArray_t[2].Output = DO_03;
   	  DigOutArray_t[2].Number = PC1;
   	  DigOutArray_t[2].Port = &PORTC;
      DigOutArray_t[2].Pin = &PINC; 
   	  DigOutArray_t[2].DDReg = &DDRC;
   	  
   	  DigOutArray_t[3].Output = DO_04;
   	  DigOutArray_t[3].Number = PC0;
   	  DigOutArray_t[3].Port = &PORTC;
      DigOutArray_t[3].Pin = &PINC; 
   	  DigOutArray_t[3].DDReg = &DDRC;
   	  
   	  DigOutArray_t[4].Output = DO_05;
   	  DigOutArray_t[4].Number = PG1;
   	  DigOutArray_t[4].Port = &PORTG;
      DigOutArray_t[4].Pin = &PING; 
   	  DigOutArray_t[4].DDReg = &DDRG;
   	  
   	  DigOutArray_t[5].Output = DO_06;
   	  DigOutArray_t[5].Number = PG0;
   	  DigOutArray_t[5].Port = &PORTG;
      DigOutArray_t[5].Pin = &PING; 
   	  DigOutArray_t[5].DDReg = &DDRG;

   	  DigOutArray_t[6].Output = DO_07;
   	  DigOutArray_t[6].Number = PD1;
   	  DigOutArray_t[6].Port = &PORTD;
      DigOutArray_t[6].Pin = &PIND; 
   	  DigOutArray_t[6].DDReg = &DDRD;
   	  
   	  DigOutArray_t[7].Output = DO_08;
   	  DigOutArray_t[7].Number = PD0;
   	  DigOutArray_t[7].Port = &PORTD;
      DigOutArray_t[7].Pin = &PIND; 
   	  DigOutArray_t[7].DDReg = &DDRD;
   	  
   	  DigOutArray_t[8].Output = DO_09;
   	  DigOutArray_t[8].Number = PE7;
   	  DigOutArray_t[8].Port = &PORTE;
      DigOutArray_t[8].Pin = &PINE;
   	  DigOutArray_t[8].DDReg = &DDRE;
   	  
   	  DigOutArray_t[9].Output = DO_10;
   	  DigOutArray_t[9].Number = PE6;
   	  DigOutArray_t[9].Port = &PORTE;
      DigOutArray_t[9].Pin = &PINE;
   	  DigOutArray_t[9].DDReg = &DDRE;
   	  
   	  DigOutArray_t[10].Output = DO_11;
   	  DigOutArray_t[10].Number = PE5;
   	  DigOutArray_t[10].Port = &PORTE;
      DigOutArray_t[10].Pin = &PINE; 
   	  DigOutArray_t[10].DDReg = &DDRE;
   	  
   	  DigOutArray_t[11].Output = DO_12;
   	  DigOutArray_t[11].Number = PE4;
   	  DigOutArray_t[11].Port = &PORTE;
      DigOutArray_t[11].Pin = &PINE; 
   	  DigOutArray_t[11].DDReg = &DDRE;
   	  
   	  DigOutArray_t[12].Output = DO_13;
   	  DigOutArray_t[12].Number = PE3;
   	  DigOutArray_t[12].Port = &PORTE;
      DigOutArray_t[12].Pin = &PINE;
   	  DigOutArray_t[12].DDReg = &DDRE;
   	  
   	  DigOutArray_t[13].Output = DO_14;
   	  DigOutArray_t[13].Number = PE2;
   	  DigOutArray_t[13].Port = &PORTE;
      DigOutArray_t[13].Pin = &PINE; 
   	  DigOutArray_t[13].DDReg = &DDRE;
   	  
   	  DigOutArray_t[14].Output = DO_15;
   	  DigOutArray_t[14].Number = PE1;
   	  DigOutArray_t[14].Port = &PORTE;
      DigOutArray_t[14].Pin = &PINE; 
   	  DigOutArray_t[14].DDReg = &DDRE;
   	  
   	  DigOutArray_t[15].Output = DO_16;
   	  DigOutArray_t[15].Number = PE0;
   	  DigOutArray_t[15].Port = &PORTE;
      DigOutArray_t[15].Pin = &PINE; 
   	  DigOutArray_t[15].DDReg = &DDRE;
        
  	  //Init Outputs
    	for (uint8_t i = 0; i< DO_16; i++)
    	{
       *DigOutArray_t[i].DDReg |= (1<<DigOutArray_t[i].Number);
    	}

      break;
    
    case InterfaceUnit:
  	  //Outputs
  	  DigOutArray_t[0].Output = DO_01;
  	  DigOutArray_t[0].Number = PD0;
  	  DigOutArray_t[0].Port = &PORTD;
      DigOutArray_t[0].Pin = &PIND;
  	  DigOutArray_t[0].DDReg = &DDRD;
  	  
  	  DigOutArray_t[1].Output = DO_02;
  	  DigOutArray_t[1].Number = PD1;
  	  DigOutArray_t[1].Port = &PORTD;
      DigOutArray_t[1].Pin = &PIND;
  	  DigOutArray_t[1].DDReg = &DDRD;

  	  DigOutArray_t[2].Output = DO_03;
  	  DigOutArray_t[2].Number = PG0;
  	  DigOutArray_t[2].Port = &PORTG;
      DigOutArray_t[2].Pin = &PING;
  	  DigOutArray_t[2].DDReg = &DDRG;
  	  
  	  DigOutArray_t[3].Output = DO_04;
  	  DigOutArray_t[3].Number = PG1;
  	  DigOutArray_t[3].Port = &PORTG;
      DigOutArray_t[3].Pin = &PING;
  	  DigOutArray_t[3].DDReg = &DDRG;
  	  
  	  DigOutArray_t[4].Output = DO_05;
  	  DigOutArray_t[4].Number = PC0;
  	  DigOutArray_t[4].Port = &PORTC;
      DigOutArray_t[4].Pin = &PINC;
  	  DigOutArray_t[4].DDReg = &DDRC;
  	  
  	  DigOutArray_t[5].Output = DO_06;
  	  DigOutArray_t[5].Number = PC1;
  	  DigOutArray_t[5].Port = &PORTC;
      DigOutArray_t[5].Pin = &PINC;
  	  DigOutArray_t[5].DDReg = &DDRC;

  	  DigOutArray_t[6].Output = DO_07;
  	  DigOutArray_t[6].Number = PC2;
  	  DigOutArray_t[6].Port = &PORTC;
      DigOutArray_t[6].Pin = &PINC;
  	  DigOutArray_t[6].DDReg = &DDRC;
  	  
  	  DigOutArray_t[7].Output = DO_08;
  	  DigOutArray_t[7].Number = PC3;
  	  DigOutArray_t[7].Port = &PORTC;
      DigOutArray_t[7].Pin = &PINC;
  	  DigOutArray_t[7].DDReg = &DDRC;
  	  
  	  DigOutArray_t[8].Output = DO_09;
  	  DigOutArray_t[8].Number = PE4;
  	  DigOutArray_t[8].Port = &PORTE;
      DigOutArray_t[8].Pin = &PINE;
  	  DigOutArray_t[8].DDReg = &DDRE;
  	  
  	  DigOutArray_t[9].Output = DO_10;
  	  DigOutArray_t[9].Number = PE5;
  	  DigOutArray_t[9].Port = &PORTE;
      DigOutArray_t[9].Pin = &PINE;
  	  DigOutArray_t[9].DDReg = &DDRE;
  	  
  	  DigOutArray_t[10].Output = DO_11;
  	  DigOutArray_t[10].Number = PE6;
  	  DigOutArray_t[10].Port = &PORTE;
      DigOutArray_t[10].Pin = &PINE;
  	  DigOutArray_t[10].DDReg = &DDRE;
  	  
  	  DigOutArray_t[11].Output = DO_12;
  	  DigOutArray_t[11].Number = PE7;
  	  DigOutArray_t[11].Port = &PORTE;
      DigOutArray_t[11].Pin = &PINE;
  	  DigOutArray_t[11].DDReg = &DDRE;

  	  for (uint8_t i = 0; i< DO_12; i++)
  	  {
    	  *DigOutArray_t[i].DDReg |= (1<<DigOutArray_t[i].Number);
  	  }
  	  
  	  //Inputs
  	  DigInArray_t[0].Input = DI_01;
  	  DigInArray_t[0].Number = PA7;
  	  DigInArray_t[0].Port = &PORTA;
  	  DigInArray_t[0].Pin = &PINA;
  	  DigInArray_t[0].DDReg = &DDRA;
  	  
  	  DigInArray_t[1].Input = DI_02;
  	  DigInArray_t[1].Number = PG2;
  	  DigInArray_t[1].Port = &PORTG;
  	  DigInArray_t[1].Pin = &PING;
  	  DigInArray_t[1].DDReg = &DDRG;
  	  
  	  DigInArray_t[2].Input = DI_03;
  	  DigInArray_t[2].Number = PC7;
  	  DigInArray_t[2].Port = &PORTC;
  	  DigInArray_t[2].Pin = &PINC;
  	  DigInArray_t[2].DDReg = &DDRC;
  	  
  	  DigInArray_t[3].Input = DI_04;
  	  DigInArray_t[3].Number = PC6;
  	  DigInArray_t[3].Port = &PORTC;
  	  DigInArray_t[3].Pin = &PINC;
  	  DigInArray_t[3].DDReg = &DDRC;
  	  
  	  DigInArray_t[4].Input = DI_05;
  	  DigInArray_t[4].Number = PC5;
  	  DigInArray_t[4].Port = &PORTC;
  	  DigInArray_t[4].Pin = &PINC;
  	  DigInArray_t[4].DDReg = &DDRC;
  	  
  	  DigInArray_t[5].Input = DI_06;
  	  DigInArray_t[5].Number = PC4;
  	  DigInArray_t[5].Port = &PORTC;
  	  DigInArray_t[5].Pin = &PINC;
  	  DigInArray_t[5].DDReg = &DDRC;

  	  DigInArray_t[6].Input = DI_07;
  	  DigInArray_t[6].Number = PA1;
  	  DigInArray_t[6].Port = &PORTA;
  	  DigInArray_t[6].Pin = &PINA;
  	  DigInArray_t[6].DDReg = &DDRA;
  	  
  	  DigInArray_t[7].Input = DI_08;
  	  DigInArray_t[7].Number = PA2;
  	  DigInArray_t[7].Port = &PORTA;
  	  DigInArray_t[7].Pin = &PINA;
  	  DigInArray_t[7].DDReg = &DDRA;
  	  
  	  DigInArray_t[8].Input = DI_09;
  	  DigInArray_t[8].Number = PA3;
  	  DigInArray_t[8].Port = &PORTA;
  	  DigInArray_t[8].Pin = &PINA;
  	  DigInArray_t[8].DDReg = &DDRA;
  	  
  	  DigInArray_t[9].Input = DI_10;
  	  DigInArray_t[9].Number = PA4;
  	  DigInArray_t[9].Port = &PORTA;
  	  DigInArray_t[9].Pin = &PINA;
  	  DigInArray_t[9].DDReg = &DDRA;
  	  
  	  DigInArray_t[10].Input = DI_11;
  	  DigInArray_t[10].Number = PA5;
  	  DigInArray_t[10].Port = &PORTA;
  	  DigInArray_t[10].Pin = &PINA;
  	  DigInArray_t[10].DDReg = &DDRA;
  	  
  	  DigInArray_t[11].Input = DI_12;
  	  DigInArray_t[11].Number = PA6;
  	  DigInArray_t[11].Port = &PORTA;
  	  DigInArray_t[11].Pin = &PINA;
  	  DigInArray_t[11].DDReg = &DDRA;
    
      for (uint8_t i = 0; i< DI_12; i++)
      {
        *DigInArray_t[i].DDReg &= ~((char) 1 << DigInArray_t[i].Number); // configure pin as input
        *DigInArray_t[i].Port |= (1<<DigInArray_t[i].Number); // Set Pull Up      
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
  TCCR1B = ( 1<<CS11 )|( 1<<CS10 );  // counter1,Prescaler auf 256 (ca. 260ms per overflow)
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

void InitWD(void)
{
  WDTCR = (1<<WDE) | (1<<WDP1) | (1<<WDP2); //timeout 1,04s and Watchdog enabled
}