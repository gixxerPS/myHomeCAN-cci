#include "TestMode.h"
#include "CciConfig.h"
#include "InitEcu.h"
#include "InterfaceUnit.h"
#include <avr/io.h>
#include <util/delay.h>

uint8_t GetNumOfActiveInputs_u8(void);

void InputCheck()
{
	static uint8_t TempGlobalTimer_u8 = 0;

  if (( TempGlobalTimer_u8 != GlobalTimer.t200ms_u8) && (GetNumOfActiveInputs_u8() == 1))    // only one input active
  {
    TempGlobalTimer_u8 = GlobalTimer.t200ms_u8;  // blink 2,5Hz if only one input active
                                                     
    if (TempGlobalTimer_u8 % 2)
    {
      SET_STATUS_LED();
    }
    else
    {
      RESET_STATUS_LED();
    }
  }
  else if (GetNumOfActiveInputs_u8() > 1) // more than one input active
  {
    TempGlobalTimer_u8 = GlobalTimer.t50ms_u8;   //blink fast if more than one input active
        
    if (TempGlobalTimer_u8 % 2)
    {
      SET_STATUS_LED();
    }
    else
    {
      RESET_STATUS_LED();
    }
  }    
}

void OutputCheck()
{
  static uint8_t TempGlobalTimer_u8 = 0;
  static uint8_t i = 0;  
  
  if (( TempGlobalTimer_u8 != GlobalTimer.t500ms_u8) && (GetNumOfActiveInputs_u8() == 0))    // no input active
  {
    TempGlobalTimer_u8 = GlobalTimer.t500ms_u8;  // blink 0,5Hz if only one input active
    
    if ( TempGlobalTimer_u8 % 2) // change every 2 seconds
    {
      SET_STATUS_LED();
      if ( i< NUMBER_PU_OUTPUTS )
      {
        if ( i > 0 ) 
        {
          DigOutArray_t[i-1].State = 0; // clear last output
          SetDigitalOutputPU( &DigOutArray_t[i-1] );
        }
        
        DigOutArray_t[i].State = 1; // set output
        SetDigitalOutputPU( &DigOutArray_t[i] );
        
        i++;         
      }
      else // last output reached
      {
        i = 0;
        DigOutArray_t[NUMBER_PU_OUTPUTS-1].State = 0;     // clear last output
        SetDigitalOutputPU( &DigOutArray_t[NUMBER_PU_OUTPUTS-1] );
      }
    } 
    else
    {
      RESET_STATUS_LED();
    }   
  }
}

uint8_t GetNumOfActiveInputs_u8(void)
{
	uint8_t NumOfActiveInputs_u8 = 0;
	
	GetAllDigitalInputStates();
	
	for (int i= 0; i < NUMBER_IU_INPUTS; i++)
	{
  	if (DigInArray_t[i].State != 0)
  	{
    	NumOfActiveInputs_u8++;
  	}
	}
  
  return NumOfActiveInputs_u8;  
}