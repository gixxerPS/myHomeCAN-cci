/*
 * CciConfig.h
 *
 * Created: 14.03.2017 19:25:20
 *  Author: Mark Roters
 */ 


#ifndef CCICONFIG_H_
#define CCICONFIG_H_

/* INCLUDES*/
#include <avr/pgmspace.h>
#include <avr/io.h>

/*TYPEDEFS*/
  typedef enum {Unknowm, SensorUnit = 6, PowerUnit = 5, InterfaceUnit = 3, NotConfigured = 255 }FunctionID;
	
  typedef struct Config{
    FunctionID FctId;
    char NodeId_u8;
  }Config_t;
  
  Config_t CCiConfig_t;

/*DECLARATIONS*/
  void GetNodeId(void);
  void GetFctId(void);

#endif /* CCICONFIG_H_ */