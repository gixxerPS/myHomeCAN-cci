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

void SetInterfaceUnitOutputs(can_t *msg);
#endif /* INTERFACEUNIT_H_ */