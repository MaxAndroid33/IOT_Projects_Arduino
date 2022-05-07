#include "System.h"
OneWire ourWire1(Temparture_Sensor);
DallasTemperature sensor1(&ourWire1);

void IRAM_ATTR Water_Level_Sensor_Detected();
void IRAM_ATTR Ardoino_on_Off_in_Btn_Interrupt();
void IRAM_ATTR Full_Mode_Reset();
void IRAM_ATTR Auto_PushBtn_Interrupt();
void IRAM_ATTR Manual_PushBtn_Interrupt();

 //             Inatalization Ports        //
 void initialize::Inisialize_IO_Ports(){
pinMode(Temparture_Sensor,INPUT_PULLUP);
pinMode(WaterLevel_Sensor,INPUT);
pinMode(Full_Mode_Reset_Btn,INPUT);
attachInterrupt(digitalPinToInterrupt(WaterLevel_Sensor), Water_Level_Sensor_Detected, RISING);
attachInterrupt(digitalPinToInterrupt(Ardoino_on_Off_in_Btn),Ardoino_on_Off_in_Btn_Interrupt, RISING);
attachInterrupt(digitalPinToInterrupt(Full_Mode_Reset_Btn), Full_Mode_Reset, RISING);
pinMode(Ardoino_on_Off_in_Btn,INPUT);
pinMode(Reset_Full_Mode_Button,INPUT);
pinMode(Full_Mode_Lamp, OUTPUT);  
pinMode(Pump,OUTPUT);
pinMode(Main_valve,OUTPUT);
pinMode(Storage_valve,OUTPUT);
pinMode(Ardoino_on_Off_out_Relay,OUTPUT);
pinMode(Offline_Online_Mode_Relay,OUTPUT);
pinMode(Auto_Manual_Mode_Relay,OUTPUT);
pinMode(Auto_Mode_Button,INPUT);
attachInterrupt(digitalPinToInterrupt(Auto_Mode_Button), Auto_PushBtn_Interrupt, RISING);
attachInterrupt(digitalPinToInterrupt(Manual_Mode_Button), Manual_PushBtn_Interrupt, RISING);
pinMode(Manual_Mode_Button,INPUT);

}



/*               Start Auto mode With All Sensor  */
  bool Auto_Mode::Start_Auto_Mode(void){
          sensor1.begin();
      if(Auto_Mode_Button_Value==true || (Full_Mode_Lamp_Value==false && Manual_Mode_Button_Value==false&&WaterLevel_Sensor_Value==false)){
            digitalWrite(Auto_Manual_Mode_Relay,HIGH);
            temparture_Sensor_Value=Reading_Temp_Sensor();
            temparture_Sensor_Now="Enabled";

            return true;
      
      }
      else{
             temparture_Sensor_Now="Disabled";
             digitalWrite(Auto_Manual_Mode_Relay,LOW);    // Manual_Mode is Active
             Manual_Mode_Button_Value=false;           

             return false;
             
      }




  }

  /////////
  /*             Temperature Sensor         */
  float Auto_Mode::Reading_Temp_Sensor(void){
   // while(!Full_Mode_Lamp_Value){

               sensor1.requestTemperatures();
              temparture_Sensor_Value=sensor1.getTempCByIndex(0);
         if(temparture_Sensor_Value>=120 && WaterLevel_Sensor_Value==false&& Manual_Mode_Button_Value==false){ 

        Main_valve_Value= Main_Valve(true);
        Storage_valve_Value=Storage_Valve(true);
        delay(1000);
        Pump_Value= Run_pump_Auto(true);
        

         }else{
          Pump_Value= Run_pump_Auto(false);
          if(Main_valve_Value)delay(2000);
          Main_valve_Value= Main_Valve(false);
          Storage_valve_Value=Storage_Valve(false);

        }

   // }
          return temparture_Sensor_Value;

  }

/*            Water_Level_Sensor_Detected Auto               */
void Water_Level_Sensor_Detected(){
      Auto_Mode s;
      Auto_Mode_Button_Value=false;
      WaterLevel_Sensor_Value=true;
      Full_Mode_Lamp_Value=true;
      digitalWrite(Full_Mode_Lamp,HIGH);
          Pump_Value= s.Run_pump_Auto(false);
          if(Main_valve_Value)delay(2000);
          Main_valve_Value= s.Main_Valve(false);
          Storage_valve_Value=s.Storage_Valve(false);
       digitalWrite(Auto_Manual_Mode_Relay,LOW);                        // Manual_Mode is Active

}

/*            Run Pump Auto               */
 bool  Auto_Mode::Run_pump_Auto(bool statu){
   if(statu==true){digitalWrite(Pump,HIGH); return true;}   // Start Pump
   else{digitalWrite(Pump,LOW); return false;}  //Stop Pump
 }


 /*         Main_Valve Auto           */

 bool Auto_Mode::Main_Valve(bool statu){

    if(statu==true){digitalWrite(Main_valve,HIGH); return true;}   // Open Main_Valve
   else{digitalWrite(Main_valve,LOW); return false;}  //Close Main_Valve
 }

 /*         Storage_Valve Auto           */

 bool Auto_Mode::Storage_Valve(bool statu){

    if(statu==true){digitalWrite(Storage_valve,HIGH); return true;}   // Open  Storage_Valve
   else{digitalWrite(Storage_valve,LOW); return false;}  //Close  Storage_Valve
 }

 /*            Auto_PushBtn_Interrupt           */
 void Auto_PushBtn_Interrupt( void){
   Manual_Mode_Button_Value=false;
   Auto_Mode_Button_Value=true;
   Auto_Manual_Mode_Relay_Value=true;
   digitalWrite(Auto_Manual_Mode_Relay,HIGH);

}


//////////////////////////////////////////////////////////////////////////////////////////
 /*            Start_Manual_Mode            */
 bool Manual_Mode::Start_Manual_Mode(void){
   if(Manual_Mode_Button_Value==true ||(Auto_Manual_Mode_Relay_Value==false && Auto_Mode_Button_Value==false)){
      digitalWrite(Auto_Manual_Mode_Relay,LOW);
      Auto_Manual_Mode_Relay_Value=false;
      return true;
   }
   else return false;



 }

 /*            Full_Mode_Reset             */
void Full_Mode_Reset(void){
    WaterLevel_Sensor_Value =false;
    Full_Mode_Lamp_Value =false;
    digitalWrite(Full_Mode_Lamp,LOW);
}

/*            Manual_PushBtn_Interrupt             */
 void Manual_PushBtn_Interrupt( void){
   Manual_Mode_Button_Value=true;
   Auto_Mode_Button_Value=false;
   Auto_Manual_Mode_Relay_Value=false;
   digitalWrite(Auto_Manual_Mode_Relay,LOW);
 }

 void Ardoino_on_Off_in_Btn_Interrupt(void){
   Ardoino_on_Off_out_Relay_Value=false;
  digitalWrite(Ardoino_on_Off_out_Relay,LOW);

 }
  