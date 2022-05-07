#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
//#include <ESPAsyncWebServer.h>

ESP8266WebServer server(80);
// REPLACE WITH YOUR NETWORK CREDENTIALS
const char *ssid = "rootESP";
const char *password = "1234567890";

//no need authentification
void encenderLED(){
  String message = "Encender LED";
  server.send(200, "text/plain", message);
  digitalWrite(LED_BUILTIN, LOW);  // turn on LED with voltage HIGH
}

void apagarLED(){
  String message = {"Apagar LED"};
  server.send(200, "text/plain", message);
  digitalWrite(LED_BUILTIN, HIGH);  // turn on LED with voltage HIGH
}

void conectado(){
  String message = {"Apagar LED"};
  server.send(200, "text/plain", message);
  digitalWrite(LED_BUILTIN, HIGH);  // turn on LED with voltage HIGH
}

void setup(void){  
  Serial.begin(115200);
   WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Wait for connection
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  pinMode(LED_BUILTIN, OUTPUT); // Onboard LED
  server.on("/encender", encenderLED);
  server.on("/apagar", apagarLED);
  server.on("/", conectado);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}