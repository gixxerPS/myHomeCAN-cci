/*
 * Identifier.c
 *
 * Created: 03.04.2017 17:48:31
 *  Author: Mark Roters
 */ 
#include "Identifier.h"
#include "CciConfig.h"

uint32_t BuildIdentifier( Identifier_t Ident_t)
{
	#define LENGTH_SRC_ID      5u
	#define LENGTH_TARGET_ID   5u
	#define LENGTH_SRC_FCT     3u
	#define LENGTH_TARGET_FCT  3u
	#define LENGTH_NUMBER      3u
	#define LENGTH_PRIO        4u
	#define LENGTH_EMPTY       6u
	  
	static uint32_t Identifier_u32 = 0;
	
	Identifier_u32 = (uint32_t)Ident_t.Number_u8 | (uint32_t)((uint32_t)Ident_t.TargetId_u8 << LENGTH_NUMBER);
	Identifier_u32 = Identifier_u32 | (uint32_t)((uint32_t)Ident_t.TargetFct_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID ));
	Identifier_u32 = Identifier_u32 | (uint32_t)((uint32_t)Ident_t.SrcId_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT));
	Identifier_u32 = Identifier_u32 | (uint32_t)((uint32_t)Ident_t.SrcFct_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT + LENGTH_SRC_ID));
	Identifier_u32 = Identifier_u32 | (uint32_t)((uint32_t)Ident_t.Prio_u8 << (LENGTH_NUMBER + LENGTH_TARGET_ID + LENGTH_TARGET_FCT + LENGTH_SRC_ID + LENGTH_SRC_FCT));
	
	return Identifier_u32;
}