/*
 * InitEcu.h
 *
 * Created: 14.03.2017 19:15:54
 *  Author: Mark Roters
 */ 


#ifndef INITECU_H_
#define INITECU_H_

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

#endif /* INITECU_H_ */