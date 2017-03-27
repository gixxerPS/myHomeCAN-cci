/*
 * InitEcu.c
 *
 * Created: 14.03.2017 19:15:18
 *  Author: Mark Roters
 */ 
#include <avr/io.h>
#include "InitEcu.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void InitI0I(void)
{
  DDRD |= (1<<PD7); //LED Ausgang
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