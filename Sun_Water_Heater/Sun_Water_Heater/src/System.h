#ifndef SYSTEM_H
#define  SYSTEM_H
#include "OneWire.h"
#include "DallasTemperature.h"
#include "GPIO.h"
#include "Variables.h"



 #endif


class Auto_Mode{

public:
    bool Start_Auto_Mode(void);
    float Reading_Temp_Sensor(void);
    bool Run_pump_Auto(bool);
    bool Main_Valve(bool);
    bool Storage_Valve(bool);
    String temparture_Sensor_Now;


};
class Manual_Mode{

public:
    bool Start_Manual_Mode(void);
    


};

class Offline_Mode:public Manual_Mode,public Auto_Mode{

public:
    void run(){
        digitalWrite(Offline_Online_Mode_Relay, LOW);
    }

   

};
class Online_Mode:public Manual_Mode,public Auto_Mode{

public:
   void run(){
        digitalWrite(Offline_Online_Mode_Relay, HIGH);
    }

};


class initialize {
public:
void Inisialize_IO_Ports();

};