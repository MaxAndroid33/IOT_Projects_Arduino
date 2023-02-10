#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266_ISR_Servo.h>



// Published values for SG90 servos; adjust if needed

#define TIMER_INTERRUPT_DEBUG 1
#define ISR_SERVO_DEBUG 1
#define MIN_MICROS 800 // 544
#define MAX_MICROS 2450
#define Up_Down_Servo_Pin D8
#define Left_Right_Servo_Pin D7
int servoindexUpDown = -1;
int servoindexLeftRight = -1;
int ImageCenterX;
int ImageCenterY;
int positionx = 90;
int positiony = 0;
int thresholdX = 20;
float SpeedY = 2;
int thresholdY = 10;
float SpeedX = 1.5;
void SetPOS(String Xp, String Yp);

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char *ssid = "rootESP";
const char *password = "1234567890";
const char *X_Pos = "XPOS"; // http//192.168.1.4/get?XPOS=4444
const char *Y_Pos = "YPOS";
String x, y;
void Get_Postion(AsyncWebServerRequest *request)
{
  if (request->hasParam(X_Pos))
  {
    x = request->getParam(X_Pos)->value();
  }
  else if (request->hasParam(Y_Pos))
  {
    y = request->getParam(Y_Pos)->value();
  }
  Serial.println("X:" + x + "    Y:" + y);
  request->send(200, "text/text", x);
}

void notfound(AsyncWebServerRequest *request) { request->send(404, "text/plain", "Not Found"); }

void setup()
{
  Serial.begin(115200);
  // Wifi Setup
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  // Server Steup
  server.on("/get", HTTP_GET, Get_Postion);
  server.onNotFound(notfound);
  server.begin();
  // Servo Setup
  servoindexUpDown = ISR_Servo.setupServo(Up_Down_Servo_Pin, MIN_MICROS, MAX_MICROS);
  servoindexLeftRight = ISR_Servo.setupServo(Left_Right_Servo_Pin, MIN_MICROS, MAX_MICROS);
  ISR_Servo.setPosition(servoindexUpDown, 0);
  ISR_Servo.setPosition(servoindexLeftRight, positionx);

  if (servoindexUpDown != -1)
    Serial.println(F("Setup Servo UP/DOWN OK"));
  else
    Serial.println(F("Setup ServoUP/DOWN failed"));

  if (servoindexLeftRight != -1)
    Serial.println(F("Setup Servo RIGHT/LEFT OK"));
  else
    Serial.println(F("Setup Servo RIGHT/LEFT failed"));
}

void loop()
{
  Serial.println("X:" + x + "    Y:" + y);
  SetPOS(x, y);
  delay(1000);
}

void SetPOS(String Xp, String Yp)
{
  int xx = Xp.toInt();
  int yy = Yp.toInt();
  if (xx != 0)
  {

    if (xx < ( thresholdX))
    {
      positionx = positionx + SpeedX;
      ISR_Servo.setPosition(servoindexLeftRight, positionx);
    }
    else if (xx > (thresholdX))
    {
      positionx = positionx - SpeedX;
      ISR_Servo.setPosition(servoindexLeftRight, positionx - SpeedX);
    }
  }
  if (yy != 0)
  {

    if (yy < thresholdY)
    {
      positiony = positiony + SpeedY;
      ISR_Servo.setPosition(servoindexUpDown, positiony + SpeedY);
    }
    else if (yy > thresholdY)
    {
      positiony = positiony - SpeedY;
      ISR_Servo.setPosition(servoindexUpDown, positiony - SpeedY);
    }
  }
}