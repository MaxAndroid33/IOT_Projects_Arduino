

#include "Network.h"
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "root"
#define WIFI_PASSWORD "1234567890"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB-7682sEywT1kmdjGpq4cAA6oiOMib9qU"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://sun-water-heater-default-rtdb.asia-southeast1.firebasedatabase.app" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


///////////////////////////////////////////////////////////////
void Network_Counnection::Check_Wifi_Counnection(void){
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


}
//////////////////////////////////////////////////////////////////
bool Network_Counnection::Check_Internet_Avialable(void){

return false;
}
////////////////////////////////////////////////////////////////
 void FireBase_Counnection:: Check_FireBase_Counnection(void){
/* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
    FB_CO_OK =true;
    
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    FB_CO_OK =false;
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
    
 }
/////////////////////////////////////////////////////////////////////////////////
void FireBase_Counnection::Send_Date_From_arduino(void){

if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "test/int", count)){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      SD_FA_OK=true;
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
       SD_FA_OK=false;
    }
    count++;
        // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "test/float", 0.01 + random(0,100))){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      SD_FA_OK=true; 
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      SD_FA_OK=false;
    }
    
 
}

     
 }


 /* Reseive Date From FireBase  */
void FireBase_Counnection::Reseive_Date_From_Phone(void){

if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
      }
      RD_FP_OK =true;
    }
    else {
      Serial.println(fbdo.errorReason());
      RD_FP_OK = false;
    }
    
    if (Firebase.RTDB.getFloat(&fbdo, "/test/float")) {
      if (fbdo.dataType() == "float") {
        temparture_Sensor_Value = fbdo.floatData();
        Serial.println(temparture_Sensor_Value);
      }
      RD_FP_OK =true;
    }
    else {
      Serial.println(fbdo.errorReason());
      RD_FP_OK =false;
    }
  }


  
}