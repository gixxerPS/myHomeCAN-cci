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

void SetDigitalOutputPU( DigOut_t* Output_t );

void SetDigitalOutputPU( DigOut_t* Output_t )
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
  SetDigitalOutputPU( &DigOutArray_t[0] ); // Output A1
  
  (msg->data[7] & 0b01000000) ? ( DigOutArray_t[1].State = 1 ): ( DigOutArray_t[1].State = 0); // Check Bit for A2
  SetDigitalOutputPU( &DigOutArray_t[1] ); // Output A2

  (msg->data[7] & 0b00100000) ? ( DigOutArray_t[2].State = 1 ): ( DigOutArray_t[2].State = 0); // Check Bit for A3
  SetDigitalOutputPU( &DigOutArray_t[2] ); // Output A3
  
  (msg->data[7] & 0b00010000) ? ( DigOutArray_t[3].State = 1 ): ( DigOutArray_t[3].State = 0); // Check Bit for A4
  SetDigitalOutputPU( &DigOutArray_t[3] ); // Output A4

  (msg->data[7] & 0b00001000) ? ( DigOutArray_t[4].State = 1 ): ( DigOutArray_t[4].State = 0); // Check Bit for A5  
  SetDigitalOutputPU( &DigOutArray_t[4] ); // Output A5
  
  (msg->data[7] & 0b00000100) ? ( DigOutArray_t[5].State = 1 ): ( DigOutArray_t[5].State = 0); // Check Bit for A6  
  SetDigitalOutputPU( &DigOutArray_t[5] ); // Output A6

  (msg->data[7] & 0b00000010) ? ( DigOutArray_t[6].State = 1 ): ( DigOutArray_t[6].State = 0); // Check Bit for A7 
  SetDigitalOutputPU( &DigOutArray_t[6] ); // Output A7
  
  (msg->data[7] & 0b00000001) ? ( DigOutArray_t[7].State = 1 ): ( DigOutArray_t[7].State = 0); // Check Bit for A8 
  SetDigitalOutputPU( &DigOutArray_t[7] ); // Output A8
  
  (msg->data[6] & 0b10000000) ? ( DigOutArray_t[8].State = 1 ): ( DigOutArray_t[8].State = 0); // Check Bit for A9
  SetDigitalOutputPU( &DigOutArray_t[8] ); // Output A9
  
  (msg->data[6] & 0b01000000) ? ( DigOutArray_t[9].State = 1 ): ( DigOutArray_t[9].State = 0); // Check Bit for A10
  SetDigitalOutputPU( &DigOutArray_t[9] ); // Output A10

  (msg->data[6] & 0b00100000) ? ( DigOutArray_t[10].State = 1 ): ( DigOutArray_t[10].State = 0); // Check Bit for A11
  SetDigitalOutputPU( &DigOutArray_t[10] ); // Output A11
  
  (msg->data[6] & 0b00010000) ? ( DigOutArray_t[11].State = 1 ): ( DigOutArray_t[11].State = 0); // Check Bit for A12
  SetDigitalOutputPU( &DigOutArray_t[11] ); // Output A12

  (msg->data[6] & 0b00001000) ? ( DigOutArray_t[12].State = 1 ): ( DigOutArray_t[12].State = 0); // Check Bit for A13 
  SetDigitalOutputPU( &DigOutArray_t[12] ); // Output A13
  
  (msg->data[6] & 0b00000100) ? ( DigOutArray_t[13].State = 1 ): ( DigOutArray_t[13].State = 0); // Check Bit for A14 
  SetDigitalOutputPU( &DigOutArray_t[13] ); // Output A14

  (msg->data[6] & 0b00000010) ? ( DigOutArray_t[14].State = 1 ): ( DigOutArray_t[14].State = 0); // Check Bit for A15
  SetDigitalOutputPU( &DigOutArray_t[14] ); // Output A15
  
  (msg->data[6] & 0b00000001) ? ( DigOutArray_t[15].State = 1 ): ( DigOutArray_t[15].State = 0); // Check Bit for A16 
  SetDigitalOutputPU( &DigOutArray_t[15] ); // Output A16
}

void SendDigitalOutputStatesPU(can_t *msg)
{
  for ( int i = 5; i<=7; i++) // clear data bytes
  {
    msg->data[i] = 0;
  }
  
  (*DigOutArray_t[0].Pin & (1<<DigOutArray_t[0].Number)) ? ( msg->data[7] |= 0b10000000 ): (0);// Set Bit for A1 if ouptut state is high
  (*DigOutArray_t[1].Pin & (1<<DigOutArray_t[1].Number)) ? ( msg->data[7] |= 0b01000000 ): (0);// Set Bit for A2 if ouptut state is high
  (*DigOutArray_t[2].Pin & (1<<DigOutArray_t[2].Number)) ? ( msg->data[7] |= 0b00100000 ): (0);// Set Bit for A3 if ouptut state is high
  (*DigOutArray_t[3].Pin & (1<<DigOutArray_t[3].Number)) ? ( msg->data[7] |= 0b00010000 ): (0);// Set Bit for A4 if ouptut state is high
  (*DigOutArray_t[4].Pin & (1<<DigOutArray_t[4].Number)) ? ( msg->data[7] |= 0b00001000 ): (0);// Set Bit for A5 if ouptut state is high
  (*DigOutArray_t[5].Pin & (1<<DigOutArray_t[5].Number)) ? ( msg->data[7] |= 0b00000100 ): (0);// Set Bit for A6 if ouptut state is high
  (*DigOutArray_t[6].Pin & (1<<DigOutArray_t[6].Number)) ? ( msg->data[7] |= 0b00000010 ): (0);// Set Bit for A7 if ouptut state is high
  (*DigOutArray_t[7].Pin & (1<<DigOutArray_t[7].Number)) ? ( msg->data[7] |= 0b00000001 ): (0);// Set Bit for A8 if ouptut state is high
  (*DigOutArray_t[8].Pin & (1<<DigOutArray_t[8].Number)) ? ( msg->data[6] |= 0b10000000 ): (0);// Set Bit for A9 if ouptut state is high
  (*DigOutArray_t[9].Pin & (1<<DigOutArray_t[9].Number)) ? ( msg->data[6] |= 0b01000000 ): (0);// Set Bit for A10 if ouptut state is high
  (*DigOutArray_t[10].Pin & (1<<DigOutArray_t[10].Number)) ? ( msg->data[6] |= 0b00100000 ): (0);// Set Bit for A11 if ouptut state is high
  (*DigOutArray_t[11].Pin & (1<<DigOutArray_t[11].Number)) ? ( msg->data[6] |= 0b00010000 ): (0);// Set Bit for A12 if ouptut state is high
  (*DigOutArray_t[12].Pin & (1<<DigOutArray_t[12].Number)) ? ( msg->data[6] |= 0b00001000 ): (0);// Set Bit for A9 if ouptut state is high
  (*DigOutArray_t[13].Pin & (1<<DigOutArray_t[13].Number)) ? ( msg->data[6] |= 0b00000100 ): (0);// Set Bit for A10 if ouptut state is high
  (*DigOutArray_t[14].Pin & (1<<DigOutArray_t[14].Number)) ? ( msg->data[6] |= 0b00000010 ): (0);// Set Bit for A11 if ouptut state is high
  (*DigOutArray_t[15].Pin & (1<<DigOutArray_t[15].Number)) ? ( msg->data[6] |= 0b00000001 ): (0);// Set Bit for A12 if ouptut state is high
  can_send_message(msg);
}