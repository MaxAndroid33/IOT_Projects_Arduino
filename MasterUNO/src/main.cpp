#include <Arduino.h>
#include <ModbusRtu.h>
#include <SoftwareSerial.h>
Modbus Master(0, Serial, 0);
/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram[2];
// SoftwareSerial mySerial(3, 5);//Create a SoftwareSerial object so that we can use software serial. Search "software serial" on Arduino.cc to find out more details.

void setupSlave(uint8_t code, uint8_t idslave, uint16_t RegAdd, uint16_t CoilsNo, int index);
uint8_t state; //!< machine state
uint8_t query; //!< pointer to message query
unsigned long wait;

// data array for modbus network sharing
uint16_t au16data[16];

void setup()
{
  Serial.begin(19200); // baud-rate at 19200
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);

  setupSlave(3, 1, 0, 4, 0); // Slave Read
  setupSlave(4, 1, 4, 1, 1); // Slave Write
  Master.start();
  Master.setTimeOut(5000); // if there is no answer in 5000 ms, roll over
  wait = millis() + 1000;
  state = query = 0;
}

void loop()
{
  switch (state)
  {
  case 0:
    if (millis() > wait)
      state++; // wait state
    break;
  case 1:
    Master.query(telegram[query]); // send query (only once)
    state++;
    query++;
    if (query > 2)
      query = 0;
    break;
  case 2:
    Master.poll(); // check incoming messages
    if (Master.getState() == COM_IDLE)
    {
      state = 0;
      wait = millis() + 1000;
    }
    break;
  }

  au16data[4] = analogRead(1);
  bitWrite(au16data[0], 0, digitalRead(2)); // read the Green Led
  bitWrite(au16data[0], 1, digitalRead(3)); // read the Red Led
  bitWrite(au16data[0], 2, digitalRead(4)); // read the Yellow Led
  bitWrite(au16data[0], 3, digitalRead(5)); // read the Blue Led
  analogWrite(10, au16data[1]);
}

void setupSlave(uint8_t code, uint8_t idslave, uint16_t RegAdd, uint16_t CoilsNo, int index)
{
  telegram[index].u8id = idslave;              // slave address
  telegram[index].u8fct = code;                // function code
  telegram[index].u16RegAdd = RegAdd;          // start address in slave
  telegram[index].u16CoilsNo = CoilsNo;        // number of elements (coils or registers)
  telegram[index].au16reg = au16data + RegAdd; // pointer to a memory array in the Arduino
}