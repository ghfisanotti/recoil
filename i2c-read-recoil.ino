/*
 * Author: Gerardo Fisanotti - 30-may-2020
 * Function: Read the impulse of a rifle recoil by reading time and analog value of a 
 *           variable resistor moved by the energy of the recoil
 *           Will send results (microseconds, voltage) via I2C bus to a requesting master.
 * Hardware: MCU D1 Mini (ESP8266 based), 
 *           MCU pin D2-(SDA) to Raspberry GPIO pin #3 (SDA) 
 *           MCU pin D1-(SCL) to Raspberry GPIO pin #5 (SCL) 
 *           MCU pin A0 to wiper of measuring variable resistor, extremes of resistor to 3.3V and GND
 *           MCU pin D6 to green LED anode thru 220 ohm resistor, LED cathode to ground
 *           MCU pin D7 to yellow LED anode thru 220 ohm resistor, LED cathode to ground
 */
 
#include <Wire.h>

const int pot=A0; //potentiometer wiper
const int maxSample=1025; //Max # of samples to be stored
const int readyLED=D6; //green LED, ready to take samples
const int finishedLED=D7; //Yellow LED, waiting for I2C master to read values
unsigned long bt=0;
unsigned count=0; 
unsigned ant=0;
unsigned long tim_a[maxSample];
unsigned val;
unsigned val_a[maxSample];
bool finished=true;
char line[16];
volatile unsigned next=0;

void setup() {
  pinMode(pot, INPUT);
  pinMode(readyLED, OUTPUT);
  pinMode(finishedLED, OUTPUT);
  Serial.begin(115200);
  Wire.begin(0x08);                // join i2c bus as slave with address #8
  Wire.onRequest(requestEvent); // register event
}

void requestEvent() {
  if (next < count) {
    sprintf(line, "%8u, %4u", tim_a[next], val_a[next]);
    } else {
    sprintf(line, "%8u, %4u", 0, 0);
  }
  Wire.write(line,14);
  next++;
}

void dumpTable() {
  Serial.print("Time(us): ");
  Serial.println(micros()-bt);
  Serial.print("Samples: ");
  Serial.println(count);
  for (int i=0;i<count;i++) {
    sprintf(line, "%8u, %4u", int(tim_a[i]), int(val_a[i]));
    Serial.println(line);
    yield(); //important for ESP8266, lets background processes run!
  }
}

void getReady() {
  bt=micros(); 
  count=0; 
  ant=0; 
  finished=false;
  digitalWrite(readyLED, HIGH);
  digitalWrite(finishedLED, LOW);
}

void finish() {
  finished=true; 
  digitalWrite(finishedLED, HIGH);
  dumpTable();
  next=0; 
  digitalWrite(readyLED, LOW);
}

void loop() {
  val=analogRead(pot);
  if (val<25) {
    getReady();
  } else {
    if (val>ant) {
      ant=val;
      if (!finished) {
        tim_a[count]=micros()-bt;
        val_a[count]=val;
        if (count<maxSample) { count++; };
        if (val>=1023) {finish();}
      }
    }
  }
}
