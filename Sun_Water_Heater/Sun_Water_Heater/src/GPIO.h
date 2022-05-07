
#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>

//void Inisialize_IO_Ports();
//void Water_Level_Sensor_Detected();
//void Full_Mode_Reset();
#endif
//o/p &i/p actuator&Sensor
#define Temparture_Sensor D8
#define WaterLevel_Sensor D0        //should be intrrupt input
#define Pump D1
#define Main_valve D3
#define Storage_valve D4
#define Ardoino_on_Off_out_Relay D5
//input Switches
#define Ardoino_on_Off_in_Btn D6
#define Reset_Full_Mode_Button D7
#define Full_Mode_Lamp D14
#define Full_Mode_Reset_Btn D9
//Modes
#define Auto_Mode_Button D10
#define Manual_Mode_Button D11
#define Offline_Online_Mode_Relay D12
#define Auto_Manual_Mode_Relay D13 

// void Inisialize_IO_Ports(){
// pinMode(Temparture_Sensor,INPUT_PULLUP);
// pinMode(WaterLevel_Sensor,INPUT);
// pinMode(Full_Mode_Reset_Btn,INPUT);
// attachInterrupt(digitalPinToInterrupt(WaterLevel_Sensor), Water_Level_Sensor_Detected, RISING);
// attachInterrupt(digitalPinToInterrupt(Ardoino_on_Off_in_Btn),Ardoino_on_Off_in_Btn_Interrupt, RISING);
// attachInterrupt(digitalPinToInterrupt(Full_Mode_Reset_Btn), Full_Mode_Reset, RISING);
// pinMode(Ardoino_on_Off_in_Btn,INPUT);
// pinMode(Reset_Full_Mode_Button,INPUT);
// pinMode(Full_Mode_Lamp, OUTPUT);  
// pinMode(Pump,OUTPUT);
// pinMode(Main_valve,OUTPUT);
// pinMode(Storage_valve,OUTPUT);
// pinMode(Ardoino_on_Off_out_Relay,OUTPUT);
// pinMode(Offline_Online_Mode_Relay,OUTPUT);
// pinMode(Auto_Manual_Mode_Relay,OUTPUT);
// pinMode(Auto_Mode_Button,INPUT);
// attachInterrupt(digitalPinToInterrupt(Auto_Mode_Button), Auto_PushBtn_Interrupt, RISING);
// attachInterrupt(digitalPinToInterrupt(Manual_Mode_Button), Manual_PushBtn_Interrupt, RISING);
// pinMode(Manual_Mode_Button,INPUT);

// }


