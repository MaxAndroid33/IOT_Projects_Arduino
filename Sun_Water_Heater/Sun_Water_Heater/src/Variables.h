#ifndef VARIABLES_H
#define VARIABLES_H 
#include <Arduino.h>
//#include <stdio.h>

extern unsigned long sendDataPrevMillis ;
extern bool signupOK ;
extern int count ;
extern int intValue;
extern float temparture_Sensor_Value;
extern bool WaterLevel_Sensor_Value;
extern bool Pump_Value;
extern bool Main_valve_Value;
extern bool Storage_valve_Value;
extern bool Ardoino_on_Off_out_Relay_Value;
extern bool Auto_Mode_Button_Value;
extern bool Manual_Mode_Button_Value;
extern bool Full_Mode_Lamp_Value;
extern bool Auto_Manual_Mode_Relay_Value;
extern bool offline_Mode_Statu;
extern bool online_Mode_Statu;

#endif
