#include <Arduino.h>
#include<Firebase.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

/* 1. Define the API Key */
#define API_KEY "AIzaSyB8qGZ65FAscsaHWeXMVG-1lstkyhus2u8"

/* 2. Define the RTDB URL */
#define DATABASE_URL "https://auth-9c846-default-rtdb.asia-southeast1.firebasedatabase.app" 
bool n = false;  
#define WIFI_SSID "root"
#define WIFI_PASSWORD "1234567890"


#define USER_EMAIL "joneadoerd123@gmail.com"
#define USER_PASSWORD "jonejone123"
FirebaseAuth auth;
FirebaseConfig config;
FirebaseData fbdo;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() {
   Serial.begin(115200); 
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  // Assign the callback function for the long running token generation task
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;
 
   // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  // Variable to save USER UID
String uid;
  // connect to wifi.  
  initWiFi();   
  Firebase.begin(&config, &auth);
  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.print(uid);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  pinMode(LED_BUILTIN,OUTPUT);
    
}

void loop() {
   // set value  
  if (Firebase.RTDB.getBool(&fbdo,"/Toggle/LED")) {
       
        n = fbdo.boolData();
        Serial.println(n);
      
  }
  Serial.println(n); 
  // handle error  
  if (n==true) {  
      Serial.print("LED is ON");  
      digitalWrite(LED_BUILTIN,HIGH);  
      Serial.println(fbdo.errorReason());   
  }  
 else if (n==false){  
   Serial.print("LED is OFF");  
   digitalWrite(LED_BUILTIN,LOW);  
   Serial.println(fbdo.errorReason()); 
 }  
 else{
    Serial.println("error");
}
}