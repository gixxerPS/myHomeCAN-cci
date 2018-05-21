/*
 * InterfaceUnit.c
 *
 * Created: 03.04.2017 18:57:08
 *  Author: Mark Roters
 */ 
#include "InterfaceUnit.h"
#include "InitEcu.h"
#include "Identifier.h"
#include <avr/pgmspace.h>
#include "can.h"
#include <avr/interrupt.h>

void SetDigitalOutputIU( DigOut_t* Output_t );
bool ReadDigitalInputIU( DigIn_t* Input_t );

void SetDigitalOutputIU( DigOut_t* Output_t )
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

bool ReadDigitalInputIU( DigIn_t* Input_t )
{
  bool SendFlag_b = false;
  bool DebouncedState_b;
 
  /* ---------START: DEBOUNCE AREA-------------*/
  if ( *Input_t->Pin & (char)(1<<Input_t->Number) ) // input is off
  {
     DebouncedState_b = false;          // local flag for further progress
     Input_t->DebounceState_u8 = false; // reset debounce flag
  }
  else // input is on
  {
    if ( Input_t->DebounceState_u8 == false ) // positive trigger
    {
      Input_t->DebounceState_u8 = true;                   // timer starting flag
      Input_t->DebounceTimer_u8 = GlobalTimer.t100ms_u8;   // start debounce timer
      DebouncedState_b = false;                           // local state for further progress
    }  
    else  // debounce state is true
    {
      if (( Input_t->DebounceTimer_u8 != GlobalTimer.t100ms_u8 ) && (Input_t->State == 0)) // debounce input
      {
         DebouncedState_b = true;
      } 
      else if (Input_t->State == 1) // input is already debounced
      {
         DebouncedState_b = true;   
      }    
      else
      {
         DebouncedState_b = false;
      }     
    }    
  }
  /* -------------END: DEBOUNCE AREA -------------------*/

  if ( DebouncedState_b == false ) // debounced Input is off
  {
    if ( Input_t->State == 1)
    {
      SendFlag_b = true;
    }
    Input_t->State = 0;      //if Input is High state OFF because of PullUp Resistor
    Input_t->StateTime05s_u8 = 0; //REset after negativ trigger  
  }
  else // debounced input is ON
  {
    if (Input_t->State == 0)  // positive trigger
    {
      Input_t->StateTime05s_u8 = 0; //REset after positiv trigger
      Input_t->State = 1; 
      Input_t->HalfSecCount_u8 = QuarterSecondCounter_u8 + 2;
      SendFlag_b = true; // Send message because value has changed
    }
    
    if ( (Input_t->HalfSecCount_u8 == QuarterSecondCounter_u8)) // Timer overflow
    {
      Input_t->HalfSecCount_u8 = QuarterSecondCounter_u8 + 2; //reset conditions
      
      if (Input_t->StateTime05s_u8 < 0b111)  // increment 0,5s step if smaller than 3,5s (0b111)
      {
        Input_t->StateTime05s_u8++;        
      }
      SendFlag_b = true; // Send message because duration has changed
    }   
  }  
  
  return SendFlag_b;
}

bool GetAllDigitalInputStates( void )
{
  bool SendFlag_b = false;
  
  for (int i = 0; i< 12; i++)
  {
    SendFlag_b |= ReadDigitalInputIU( &DigInArray_t[i] );  
  }
  
  return SendFlag_b;
}

void SetInterfaceUnitOutputs(can_t *msg)
{
  // the upper 16bits are necessary for Power Unit
  (msg->data[7] & 0b10000000) ? ( DigOutArray_t[0].State = 1 ): ( DigOutArray_t[0].State = 0); // Check Bit for A1
  SetDigitalOutputIU( &DigOutArray_t[0] ); // Output A1
  
  (msg->data[7] & 0b01000000) ? ( DigOutArray_t[1].State = 1 ): ( DigOutArray_t[1].State = 0); // Check Bit for A2
  SetDigitalOutputIU( &DigOutArray_t[1] ); // Output A2

  (msg->data[7] & 0b00100000) ? ( DigOutArray_t[2].State = 1 ): ( DigOutArray_t[2].State = 0); // Check Bit for A3
  SetDigitalOutputIU( &DigOutArray_t[2] ); // Output A3
  
  (msg->data[7] & 0b00010000) ? ( DigOutArray_t[3].State = 1 ): ( DigOutArray_t[3].State = 0); // Check Bit for A4
  SetDigitalOutputIU( &DigOutArray_t[3] ); // Output A4

  (msg->data[7] & 0b00001000) ? ( DigOutArray_t[4].State = 1 ): ( DigOutArray_t[4].State = 0); // Check Bit for A5  
  SetDigitalOutputIU( &DigOutArray_t[4] ); // Output A5
  
  (msg->data[7] & 0b00000100) ? ( DigOutArray_t[5].State = 1 ): ( DigOutArray_t[5].State = 0); // Check Bit for A6  
  SetDigitalOutputIU( &DigOutArray_t[5] ); // Output A6

  (msg->data[7] & 0b00000010) ? ( DigOutArray_t[6].State = 1 ): ( DigOutArray_t[6].State = 0); // Check Bit for A7 
  SetDigitalOutputIU( &DigOutArray_t[6] ); // Output A7
  
  (msg->data[7] & 0b00000001) ? ( DigOutArray_t[7].State = 1 ): ( DigOutArray_t[7].State = 0); // Check Bit for A8 
  SetDigitalOutputIU( &DigOutArray_t[7] ); // Output A8
  
  (msg->data[6] & 0b10000000) ? ( DigOutArray_t[8].State = 1 ): ( DigOutArray_t[8].State = 0); // Check Bit for A9
  SetDigitalOutputIU( &DigOutArray_t[8] ); // Output A9
  
  (msg->data[6] & 0b01000000) ? ( DigOutArray_t[9].State = 1 ): ( DigOutArray_t[9].State = 0); // Check Bit for A10
  SetDigitalOutputIU( &DigOutArray_t[9] ); // Output A10

  (msg->data[6] & 0b00100000) ? ( DigOutArray_t[10].State = 1 ): ( DigOutArray_t[10].State = 0); // Check Bit for A11
  SetDigitalOutputIU( &DigOutArray_t[10] ); // Output A11
  
  (msg->data[6] & 0b00010000) ? ( DigOutArray_t[11].State = 1 ): ( DigOutArray_t[11].State = 0); // Check Bit for A12
  SetDigitalOutputIU( &DigOutArray_t[11] ); // Output A12
}

void SendDigitalInputStates( can_t *msg)
{
  for ( int i = 0; i<7; i++) // clear data bytes
  {
    msg->data[i] = 0;   
  }
  
  //Inputs states
  msg->data[7] = (DigInArray_t[0].State << 7) | (DigInArray_t[1].State << 6) | (DigInArray_t[2].State << 5) | (DigInArray_t[3].State << 4) | (DigInArray_t[4].State << 3) | (DigInArray_t[5].State << 2) | (DigInArray_t[6].State << 1) | (DigInArray_t[7].State << 0);
  msg->data[6] = (DigInArray_t[8].State << 7) | (DigInArray_t[9].State << 6) |(DigInArray_t[10].State << 5) | (DigInArray_t[11].State << 4);
  
  //State duration
  msg->data[6] |= (DigInArray_t[0].StateTime05s_u8 << 1);
  msg->data[6] |= (DigInArray_t[1].StateTime05s_u8 >> 2);
  
  msg->data[5] |= (DigInArray_t[1].StateTime05s_u8 << 6);
  msg->data[5] |= (DigInArray_t[2].StateTime05s_u8 << 3);
  msg->data[5] |= (DigInArray_t[3].StateTime05s_u8 << 0);
  
  msg->data[4] |= (DigInArray_t[4].StateTime05s_u8 << 5);
  msg->data[4] |= (DigInArray_t[5].StateTime05s_u8 << 2);
  msg->data[4] |= (DigInArray_t[6].StateTime05s_u8 >> 1);
  
  msg->data[3] |= (DigInArray_t[6].StateTime05s_u8 << 7);
  msg->data[3] |= (DigInArray_t[7].StateTime05s_u8 << 4);
  msg->data[3] |= (DigInArray_t[8].StateTime05s_u8 << 1);
  msg->data[3] |= (DigInArray_t[9].StateTime05s_u8 >> 2);
  
  msg->data[2] |= (DigInArray_t[9].StateTime05s_u8 << 6);
  msg->data[2] |= (DigInArray_t[10].StateTime05s_u8 << 3);
  msg->data[2] |= (DigInArray_t[11].StateTime05s_u8 << 0);

  can_send_message(msg);
}