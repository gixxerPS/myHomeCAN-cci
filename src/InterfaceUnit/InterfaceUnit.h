/*
 * InterfaceUnit.h
 *
 * Created: 03.04.2017 18:57:21
 *  Author: Mark Roters
 */ 


#ifndef INTERFACEUNIT_H_
#define INTERFACEUNIT_H_

#include <avr/pgmspace.h>
#include "InitEcu.h"
#include "can.h"

uint8_t QuarterSecondCounter_u8;

void SetInterfaceUnitOutputs(can_t *msg);
void SendDigitalInputStates(can_t *msg);
bool GetAllDigitalInputStates( void );
#endif /* INTERFACEUNIT_H_ */