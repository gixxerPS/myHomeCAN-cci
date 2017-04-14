/*
 * PowerUnit.c
 *
 * Created: 03.04.2017 18:57:08
 *  Author: Mark Roters
 */ 
#include "PowerUnit.h"
#include "Identifier.h"
#include <avr/pgmspace.h>
#include "can.h"


void SetDigitalOutput( DigOut_t* Output_t )
{
  if ( Output_t->State == 1)  //Power ON
  {
    *Output_t->Port |= (1<<Output_t->Number);      //select Port
  }
  else
  {
	  *Output_t->Port &= ~((char)1<<Output_t->Number);  //Power OFF
  }
}

void SetPowerUnitOutputs(can_t *msg)
{
  // the upper 16bits are necessary for Power Unit
  (msg->data[7] & 0b10000000) ? ( DigOutArray_t[0].State = 1 ): ( DigOutArray_t[0].State = 0); // Check Bit for A1
  SetDigitalOutput( &DigOutArray_t[0] ); // Output A1
  
  (msg->data[7] & 0b01000000) ? ( DigOutArray_t[1].State = 1 ): ( DigOutArray_t[1].State = 0); // Check Bit for A2
  SetDigitalOutput( &DigOutArray_t[1] ); // Output A2

  (msg->data[7] & 0b00100000) ? ( DigOutArray_t[2].State = 1 ): ( DigOutArray_t[2].State = 0); // Check Bit for A3
  SetDigitalOutput( &DigOutArray_t[2] ); // Output A3
  
  (msg->data[7] & 0b00010000) ? ( DigOutArray_t[3].State = 1 ): ( DigOutArray_t[3].State = 0); // Check Bit for A4
  SetDigitalOutput( &DigOutArray_t[3] ); // Output A4

  (msg->data[7] & 0b00001000) ? ( DigOutArray_t[4].State = 1 ): ( DigOutArray_t[4].State = 0); // Check Bit for A5  
  SetDigitalOutput( &DigOutArray_t[4] ); // Output A5
  
  (msg->data[7] & 0b00000100) ? ( DigOutArray_t[5].State = 1 ): ( DigOutArray_t[5].State = 0); // Check Bit for A6  
  SetDigitalOutput( &DigOutArray_t[5] ); // Output A6

  (msg->data[7] & 0b00000010) ? ( DigOutArray_t[6].State = 1 ): ( DigOutArray_t[6].State = 0); // Check Bit for A7 
  SetDigitalOutput( &DigOutArray_t[6] ); // Output A7
  
  (msg->data[7] & 0b00000001) ? ( DigOutArray_t[7].State = 1 ): ( DigOutArray_t[7].State = 0); // Check Bit for A8 
  SetDigitalOutput( &DigOutArray_t[7] ); // Output A8
  
  (msg->data[6] & 0b10000000) ? ( DigOutArray_t[8].State = 1 ): ( DigOutArray_t[8].State = 0); // Check Bit for A9
  SetDigitalOutput( &DigOutArray_t[8] ); // Output A9
  
  (msg->data[6] & 0b01000000) ? ( DigOutArray_t[9].State = 1 ): ( DigOutArray_t[9].State = 0); // Check Bit for A10
  SetDigitalOutput( &DigOutArray_t[9] ); // Output A10

  (msg->data[6] & 0b00100000) ? ( DigOutArray_t[10].State = 1 ): ( DigOutArray_t[10].State = 0); // Check Bit for A11
  SetDigitalOutput( &DigOutArray_t[10] ); // Output A11
  
  (msg->data[6] & 0b00010000) ? ( DigOutArray_t[11].State = 1 ): ( DigOutArray_t[11].State = 0); // Check Bit for A12
  SetDigitalOutput( &DigOutArray_t[11] ); // Output A12

  (msg->data[6] & 0b00001000) ? ( DigOutArray_t[12].State = 1 ): ( DigOutArray_t[12].State = 0); // Check Bit for A13 
  SetDigitalOutput( &DigOutArray_t[12] ); // Output A13
  
  (msg->data[6] & 0b00000100) ? ( DigOutArray_t[13].State = 1 ): ( DigOutArray_t[13].State = 0); // Check Bit for A14 
  SetDigitalOutput( &DigOutArray_t[13] ); // Output A14

  (msg->data[6] & 0b00000010) ? ( DigOutArray_t[14].State = 1 ): ( DigOutArray_t[14].State = 0); // Check Bit for A15
  SetDigitalOutput( &DigOutArray_t[14] ); // Output A15
  
  (msg->data[6] & 0b00000001) ? ( DigOutArray_t[15].State = 1 ): ( DigOutArray_t[15].State = 0); // Check Bit for A16 
  SetDigitalOutput( &DigOutArray_t[15] ); // Output A16
}