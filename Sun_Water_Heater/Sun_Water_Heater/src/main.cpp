
#include <Arduino.h>
//#include "GPIO.h"
#include "Network.h"
#include "System.h"
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int count = 0;
int intValue;
float temparture_Sensor_Value;
bool WaterLevel_Sensor_Value;
bool Pump_Value;
bool Main_valve_Value;
bool Storage_valve_Value;
bool Ardoino_on_Off_out_Relay_Value;
bool Auto_Mode_Button_Value;
bool Manual_Mode_Button_Value;
bool Full_Mode_Lamp_Value;
bool Auto_Manual_Mode_Relay_Value;
bool offline_Mode_Statu;
bool online_Mode_Statu;



void Send_Reseive_Data(bool, bool);
Network_Counnection NET;
FireBase_Counnection Data;
Offline_Mode offline;
Online_Mode online;
initialize initial;

void setup()
{
  Serial.begin(115200);

   NET.Check_Wifi_Counnection();
  // // while(!Data.FB_CO_OK){Data.Check_FireBase_Counnection();}
   Data.Check_FireBase_Counnection();
  // Data.FB_CO_OK=false;          //reset the Check FireBase_Counnection to default
  initial.Inisialize_IO_Ports();  
  if (online_Mode_Statu)
  { online.run();
    Send_Reseive_Data(false, true); // resive Data from Phone
  }else {offline.run();}
  {
    Ardoino_on_Off_out_Relay_Value = true;
    digitalWrite(Ardoino_on_Off_out_Relay, HIGH);
  }
}

void loop()
{
  if (Ardoino_on_Off_out_Relay_Value)
  {
 ///////////////////////////     Offline         /////////////////////////////////////   
    if (offline_Mode_Statu)
    {
      online_Mode_Statu = false;
      
        if (Auto_Mode_Button_Value)
          offline.Start_Auto_Mode();
        else
          offline.Start_Manual_Mode();
    }
 ////////////////////     Online       ////////////////////////////////////   
    if (online_Mode_Statu)
    { Send_Reseive_Data(false, true); // resive Data from Phone
      offline_Mode_Statu = false;
      if (Auto_Mode_Button_Value)
          online.Start_Auto_Mode();
        else
          online.Start_Manual_Mode();
        Send_Reseive_Data(true, false); // Send Data from adruino to firebase
        
    
    }
///////////////////////////////////////////////////////////    
  }else{ offline.Start_Manual_Mode();}

  Data.Check_FireBase_Counnection();
}





/*       Send_Reseive_Data from arduino        */
void Send_Reseive_Data(bool send = false, bool reseive = false)
{

  if (send)
  {
    while (!Data.SD_FA_OK)
    {
      Data.Send_Date_From_arduino();
      
    }
    Data.SD_FA_OK = false; // reset the Send_Date_From_arduino to default
  }
  if (reseive)
  {

    while (!Data.RD_FP_OK)
    {
      Data.Reseive_Date_From_Phone();
    }
    Data.RD_FP_OK = false; // reset Reseive_Date_From_Phone to default
  }
}

