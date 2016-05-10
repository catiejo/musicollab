#include <CapacitiveSensor.h>

int led1 = 13;
int led2 = 12;
int led3 = 11;

CapacitiveSensor cs24 = CapacitiveSensor(2,4);
CapacitiveSensor cs26 = CapacitiveSensor(2,6);
CapacitiveSensor cs28 = CapacitiveSensor(2,8);

long cap1 = 0;
long cap2 = 0;
long cap3 = 0;

int count1 = 0;
int count2 = 0;
int count3 = 0;

int beat = 500;
int granularity = 10;
int duration = 2;
long threshold = 300;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  cs24.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
  cs26.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
  cs28.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor... 
  Serial.begin(9600);
}

void loop() {
  if (count1 != 0) {
    digitalWrite(led1, HIGH);
    count1--;
  }
  pollForPresses();
  digitalWrite(led1, LOW);
  if (count2 != 0) {
    digitalWrite(led2, HIGH);
    count2--;
  }
  pollForPresses();
  digitalWrite(led2, LOW);
  if (count3 != 0) {
    digitalWrite(led3, HIGH);
    count3--;
  }
  pollForPresses();
  digitalWrite(led3, LOW);
}

void pollForPresses() {
  for (int i = 0; i < granularity; i++) {
    delay(beat/granularity);
    checkPins();
  }
}

void checkPins() {
  cap1 = cs24.capacitiveSensor(10);
//  Serial.println(cap1);
  cap2 = cs26.capacitiveSensor(10);
  Serial.println(cap2);
  cap3 = cs28.capacitiveSensor(10);
//  Serial.println(cap3);
  if (cap1 >= threshold) {
    if (count1 == 0) {
      digitalWrite(led1, HIGH);
    }
    count1 = duration;
  }
  if (cap2 >= threshold) {
    if (count2 == 0) {
      digitalWrite(led2, HIGH);
    }
    count2 = duration;
  }  
  if (cap3 >= threshold) {
    if (count3 == 0) {
      digitalWrite(led3, HIGH);
    }
    count3 = duration;
  }
}

