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
  typedef enum {Unknown,Master = 0b001,SensorUnit = 0b010, PowerUnit = 0b011, InterfaceUnit = 0b100, NotConfigured = 0b111 }FunctionID;
  typedef enum {SwitchSensorUnit = 6, SwitchPowerUnit = 5, SwitchInterfaceUnit = 3, SwitchNotConfigured = 255 }DipSwitchFctID;
	
  typedef struct Config{
    FunctionID FctId;
    char UnitId_u8;
  }Config_t;
  
  Config_t CCiConfig_t;

/*DECLARATIONS*/
  void GetUnitId(void);
  void GetFctId(void);

#endif /* CCICONFIG_H_ */