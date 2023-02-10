#include <Arduino.h>
#include <ModbusRtu.h>
#define ID 1

Modbus slave(ID, Serial, 0);
boolean led;
int8_t state = 0;
unsigned long wait;

uint16_t au16data[16];
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT); // pot for control the motor in mastor A1
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(10, 0); // PWM 0%

  Serial.begin(19200);
  slave.start();
  wait = millis() + 100;
  digitalWrite(13, HIGH);
}

void loop()
{
  state = slave.poll(au16data, 16);

  if (state > 4)
  {
    wait = millis() + 50;
    digitalWrite(13, HIGH);
  }
  if (millis() > 50)
    digitalWrite(13, LOW);

  digitalWrite(2, bitRead(au16data[0], 0));
  digitalWrite(3, bitRead(au16data[0], 1));
  digitalWrite(4, bitRead(au16data[0], 2));
  digitalWrite(6, bitRead(au16data[0], 3));
  au16data[1] = analogRead(1);
  analogWrite(10, au16data[4]);
}