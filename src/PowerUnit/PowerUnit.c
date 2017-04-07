/*
 * PowerUnit.c
 *
 * Created: 03.04.2017 18:57:08
 *  Author: Mark Roters
 */ 
#include "PowerUnit.h"
#include "Identifier.h"
#include <avr/pgmspace.h>


void SetDigitalOutput( DigOut_t* Output_t )
{
  if ( Output_t->State == 1)
  {
    *Output_t->Port |= (1<<Output_t->Number);
  }
  else
  {
	*Output_t->Port &= ~((char)1<<Output_t->Number);  
  }
}
