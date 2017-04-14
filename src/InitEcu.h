/*
 * InitEcu.h
 *
 * Created: 14.03.2017 19:15:54
 *  Author: Mark Roters
 */ 


#ifndef INITECU_H_
#define INITECU_H_

/* INCLUDES*/
#include <avr/pgmspace.h>
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

void InitI0I(void);
void InitTimer(void);
void InitISR(void);

#define ALL_PORTS_ON 0xff

#define VERSION_LOW    0x1
#define VERSION_MID    0x0
#define VERSION_HIGH   0x0

typedef enum {	DO_01 = 1,
        		    DO_02,
				        DO_03,
				        DO_04,
				        DO_05,
				        DO_06,
				        DO_07,
				        DO_08,
				        DO_09,
				        DO_10,
				        DO_11,
				        DO_12,
				        DO_13,
				        DO_14,
				        DO_15,
				        DO_16,}DigOutNr;
                
typedef enum {	DI_01 = 1,
  DI_02,
  DI_03,
  DI_04,
  DI_05,
  DI_06,
  DI_07,
  DI_08,
  DI_09,
  DI_10,
  DI_11,
  DI_12,}DigInNr;
				
typedef struct DigOut{
	DigOutNr Output;
	uint8_t*  Port;
	uint8_t*  DDReg;
	uint8_t  Number;
	uint8_t  State;
}DigOut_t;

typedef struct DigIn{
  DigInNr Input;
  uint8_t*  Port;
  uint8_t*  DDReg;
  uint8_t  Number;
  uint8_t  State;
}DigIn_t;

DigOut_t  DigOutArray_t[16]; // Digital Outputs  for Power Unit and Interface Unit
DigIn_t   DigInArray_t[12]; // Digital Inputs   for Interface Unit

#endif /* INITECU_H_ */