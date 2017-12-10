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

#define SET_STATUS_LED() (PORTB |= (1<<STATUS_LED))
#define RESET_STATUS_LED() (PORTB &= ~((char)1<<STATUS_LED))

#define ALL_PORTS_ON 0xff
#define NUMBER_IU_INPUTS  12
#define NUMBER_IU_OUTPUTS 12
#define NUMBER_PU_OUTPUTS  16

#define VERSION_LOW    0x1
#define VERSION_MID    0x0
#define VERSION_HIGH   0x0

#define T2000MS  200
#define T1000MS  100
#define  T500MS   50
#define  T200MS   20
#define  T100MS   10
#define   T50MS    5

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
  uint8_t*  Pin;
  uint8_t*  DDReg;
  uint8_t  Number;
  uint8_t  State;
  uint8_t  StateTime05s_u8;  //0b001 = 0,5s; 0b010 = 1s; 0b011 = 1,5s... 0b111 = 3s
  uint8_t  HalfSecCount_u8;
}DigIn_t;

typedef struct
{
  uint8_t t50ms_u8;
  uint8_t t100ms_u8;
  uint8_t t200ms_u8;
  uint8_t t500ms_u8;
  uint8_t t1000ms_u8;
  uint8_t t2000ms_u8;
} Timer_t;

DigOut_t  DigOutArray_t[16]; // Digital Outputs  for Power Unit and Interface Unit
DigIn_t   DigInArray_t[12]; // Digital Inputs   for Interface Unit
Timer_t GlobalTimer;  // Timer for global purposes

#endif /* INITECU_H_ */