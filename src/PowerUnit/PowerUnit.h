/*
 * PowerUnit.h
 *
 * Created: 03.04.2017 18:57:21
 *  Author: Mark Roters
 */ 


#ifndef POWERUNIT_H_
#define POWERUNIT_H_

#include <avr/pgmspace.h>
#include "InitEcu.h"
#include "can.h"

void SetPowerUnitOutputs(can_t *msg);
#endif /* POWERUNIT_H_ */