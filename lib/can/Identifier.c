/*
 * Identifier.c
 *
 * Created: 03.04.2017 17:48:31
 *  Author: Mark Roters
 */ 
#include "Identifier.h"
#include "CciConfig.h"

#define LENGTH_SRC_ID      5u
#define LENGTH_TARGET_ID   5u
#define LENGTH_SRC_FCT     3u
#define LENGTH_TARGET_FCT  3u
#define LENGTH_NUMBER      3u
#define LENGTH_PRIO        4u

#define POSITION_NUMBER     0u
#define POSITION_TARGET_ID  ( POSITION_NUMBER + LENGTH_NUMBER )
#define POSITION_TARGET_FCT ( POSITION_TARGET_ID + LENGTH_TARGET_ID )
#define POSITION_SRC_ID     ( POSITION_TARGET_FCT + LENGTH_TARGET_FCT )
#define POSITION_SRC_FCT    ( POSITION_SRC_ID + LENGTH_SRC_ID )
#define POSITION_PRIO       ( POSITION_SRC_FCT + LENGTH_SRC_FCT )

uint32_t BuildIdentifier( Identifier_t Ident_t)
{
	static uint32_t Identifier_u32 = 0;
	
	Identifier_u32 |= (uint32_t)Ident_t.Number_u8 | (uint32_t)((uint32_t)Ident_t.TargetId_u8 << LENGTH_NUMBER);                                         // Target or Destination ID of message and Message Number
	Identifier_u32 |= (uint32_t)((uint32_t)Ident_t.TargetFct_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID ));                                                // Target Function
	Identifier_u32 |= (uint32_t)((uint32_t)Ident_t.SrcId_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT));                                 // Soruce ID
	Identifier_u32 |= (uint32_t)((uint32_t)Ident_t.SrcFct_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT + LENGTH_SRC_ID));                // Soruce Function
	Identifier_u32 |= (uint32_t)((uint32_t)Ident_t.Prio_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT + LENGTH_SRC_ID + LENGTH_SRC_FCT)); // Priority
	
	return Identifier_u32;
}


Identifier_t ReadIdentifier( uint32_t RxIndentifier_u32 )
{
  Identifier_t TempIdent_t;
  
  TempIdent_t.Number_u8 = (uint8_t)(RxIndentifier_u32 & (uint32_t)0b111);
  TempIdent_t.TargetId_u8 = (uint8_t)((RxIndentifier_u32 >> POSITION_TARGET_ID) & (uint32_t)0b11111);
  TempIdent_t.TargetFct_u8 = (uint8_t)((RxIndentifier_u32 >> POSITION_TARGET_FCT) & (uint32_t)0b111);
  TempIdent_t.SrcId_u8 = (uint8_t)((RxIndentifier_u32 >> POSITION_SRC_ID) & (uint32_t)0b11111);
  TempIdent_t.SrcFct_u8 = (uint8_t)((RxIndentifier_u32 >> POSITION_SRC_FCT) & (uint32_t)0b111);
  TempIdent_t.Prio_u8 = (uint8_t)((RxIndentifier_u32 >> POSITION_PRIO) & (uint32_t)0b1111);

  return TempIdent_t;
} 
