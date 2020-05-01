/*
 * Author: Gerardo Fisanotti - 30-mar-2020
 * Function: Read the impulse of a rifle recoil by reading time and analog value of a 
 *           variable resistor moved by the energy of the recoil
 *           Will send results (milliseconds, voltage) via I2C bus to a requesting master.
 * Hardware: Arduino nano, pins A4(SDA) and A5(SCL) I2C bus, pin A0 to measuring variable resistor
 */
 
#include <Wire.h>

const int pot=A0; //potentiometer wiper
const int maxSample=350; //Max # of samples to be stored
const int readyLED=11; //green LED, ready to take samples
const int finishedLED=12; //Yellow LED, waiting for I2C master to read values
unsigned long bt=0;
unsigned count=0; 
byte ant=0;
unsigned tim_a[maxSample];
unsigned val_a[maxSample];
bool finished=false;
char line[13];
volatile unsigned next=0;

void setup() {
  pinMode(pot, INPUT);
  pinMode(readyLED, OUTPUT);
  pinMode(finishedLED, OUTPUT);
  Serial.begin(19200);
  Wire.begin(8);                // join i2c bus as slave with address #8
  Wire.onRequest(requestEvent); // register event
  getReady();
}

void requestEvent() {
  if (next < count) {
    sprintf(line, "%6u, %4u", tim_a[next], val_a[next]);
    } else {
    sprintf(line, "%6u, %4u", 0, 0);
  }
  Wire.write(line,12);
  next++;
}

void dumpTable() {
  Serial.print("Time(us): ");
  Serial.println(micros()-bt);
  Serial.print("Samples: ");
  Serial.println(count);
  for (int i=0;i<count;i++) {
    sprintf(line, "%6u, %4u", int(tim_a[i]), int(val_a[i]));
    Serial.println(line);
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
  digitalWrite(readyLED, LOW);
  digitalWrite(finishedLED, HIGH);
  dumpTable();
  next=0; 
}

void loop() {
  unsigned val=analogRead(pot);
  if (val==0) {getReady();}
  if (val>ant & !finished) { 
    tim_a[count]=(micros()-bt)/10;
    val_a[count]=val;
    ant=val_a[count];
    if (count<maxSample) { count++; };
    if (val==1023) {finish();}
  }
  delayMicroseconds(1000);
}
