 
#ifndef Network_h
#define Network_h
#include "Variables.h"
#include <Arduino.h>
#endif

class Network_Counnection{
public:
void Check_Wifi_Counnection(void);
bool Check_Internet_Avialable(void);
};

class FireBase_Counnection{  
    public:
 bool FB_CO_OK,SD_FA_OK,RD_FP_OK;   
FireBase_Counnection():FB_CO_OK(false),SD_FA_OK(false),RD_FP_OK(false){} 
void Check_FireBase_Counnection(void);
void Send_Date_From_arduino(void);
void Reseive_Date_From_Phone(void);

};


