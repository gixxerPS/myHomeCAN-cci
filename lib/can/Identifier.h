/*
 * Identifier.h
 *
 * Created: 03.04.2017 17:48:56
 *  Author: Mark Roters
 */ 


#ifndef IDENTIFIER_H_
#define IDENTIFIER_H_

#include <avr/pgmspace.h>
#include "CciConfig.h"

typedef struct Identifier{
 FunctionID SrcFct_u8;
 uint8_t SrcId_u8;
 FunctionID TargetFct_u8;
 uint8_t TargetId_u8;
 uint8_t Number_u8;
 uint8_t Prio_u8;
}Identifier_t;
  
uint32_t BuildIdentifier( Identifier_t Ident_t);
Identifier_t ReadIdentifier( uint32_t RxIndentifier_u32 );


#endif /* IDENTIFIER_H_ */