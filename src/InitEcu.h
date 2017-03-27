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

#endif /* INITECU_H_ */