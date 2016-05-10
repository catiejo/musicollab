#include <SoftwareSerial.h>
#include <CapacitiveSensor.h>

int led1 = 51;
int led2 = 50;
int led3 = 49;
int led4 = 48;
int led5 = 47;
int led6 = 46;

CapacitiveSensor cs_20_13 = CapacitiveSensor(20,13);
CapacitiveSensor cs_20_12 = CapacitiveSensor(20,12);
CapacitiveSensor cs_20_11 = CapacitiveSensor(20,11);
CapacitiveSensor cs_20_10 = CapacitiveSensor(20,10);
CapacitiveSensor cs_20_09 = CapacitiveSensor(20,9);
CapacitiveSensor cs_20_08 = CapacitiveSensor(20,8);
CapacitiveSensor cs_20_07 = CapacitiveSensor(20,7);
CapacitiveSensor cs_20_06 = CapacitiveSensor(20,6);
CapacitiveSensor cs_20_05 = CapacitiveSensor(20,5);
CapacitiveSensor cs_20_02 = CapacitiveSensor(20,2);

SoftwareSerial mySerial(2, 3); // RX, TX
byte resetMIDI = 4; //Tied to VS1053 Reset line

long cap1 = 0;
long cap2 = 0;
long cap3 = 0;
long cap4 = 0;
long cap5 = 0;
long cap6 = 0;
long cap7 = 0;
long cap8 = 0;
long cap9 = 0;
long cap10 = 0;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;
int count6 = 0;

int beat = 500;
int granularity = 10;
int duration = 2;
long threshold = 300;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  cs_20_13.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensors...
  cs_20_12.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_11.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_09.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_08.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_07.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_06.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_05.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_02.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  mySerial.begin(31250); //Set up soft serial for music instrument sheild.
  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); //0xB0 is channel message, set channel volume to near max (127)
}

void loop() {
  if (count1 != 0) {
    digitalWrite(led1, HIGH);
    count1--;
  }
  pollForPresses();
  digitalWrite(led1, LOW);

//  if (count2 != 0) {
    digitalWrite(led2, HIGH);
//    count2--;
//  }
  pollForPresses();
  digitalWrite(led2, LOW);

  if (count3 != 0) {
    digitalWrite(led3, HIGH);
    count3--;
  }
  pollForPresses();
  digitalWrite(led3, LOW);

  if (count4 != 0) {
    digitalWrite(led4, HIGH);
    count4--;
  }
  pollForPresses();
  digitalWrite(led4, LOW);

  if (count5 != 0) {
    digitalWrite(led5, HIGH);
    count5--;
  }
  pollForPresses();
  digitalWrite(led5, LOW);

  if (count6 != 0) {
    digitalWrite(led6, HIGH);
    count6--;
  }
  pollForPresses();
  digitalWrite(led6, LOW);

}

void pollForPresses() {
  for (int i = 0; i < granularity; i++) {
    delay(beat/granularity);
    checkPins();
  }
}

void checkPins() {
  talkMIDI(0xB0, 0, 0x00); //Default bank GM1
  talkMIDI(0xC0, 1, 0);
  
  cap1 = cs_20_13.capacitiveSensor(10);
  Serial.print(cap1);
  Serial.print("\t");
  cap2 = cs_20_12.capacitiveSensor(10);
  Serial.print(cap2);
  Serial.print("\t");
  cap3 = cs_20_11.capacitiveSensor(10);
  Serial.print(cap3);
  Serial.print("\t");
  cap4 = cs_20_10.capacitiveSensor(10);
  Serial.print(cap4);
  Serial.print("\t");
  cap5 = cs_20_09.capacitiveSensor(10);
  Serial.print(cap5);
  Serial.print("\t");
  cap6 = cs_20_08.capacitiveSensor(10);
  Serial.print(cap6);
  Serial.print("\t");
  cap7 = cs_20_07.capacitiveSensor(10);
  Serial.print(cap7);
  Serial.print("\t");
  cap8 = cs_20_06.capacitiveSensor(10);
  Serial.print(cap8);
  Serial.print("\t");
  cap9 = cs_20_05.capacitiveSensor(10);
  Serial.print(cap9);
  Serial.print("\t");
  cap10 = cs_20_02.capacitiveSensor(10);
  Serial.print(cap10);
  Serial.println();
  

  if (cap1 >= threshold) {
    noteOn(0, 48, 60);
    delay(50);
    noteOff(0, 48, 60);
    delay(50);
    if (count1 == 0) {
      digitalWrite(led1, HIGH);
    }
    count1 = duration;
  }

  if (cap2 >= threshold) {
    noteOn(0, 50, 60);
    delay(50);
    noteOff(0, 50, 60);
    delay(50);
    if (count2 == 0) {
      digitalWrite(led2, HIGH);
    }
    count2 = duration;
  }

  if (cap3 >= threshold) {
    noteOn(0, 53, 60);
    delay(50);
    noteOff(0, 53, 60);
    delay(50);
    if (count3 == 0) {
      digitalWrite(led3, HIGH);
    }
    count3 = duration;
  }

  if (cap4 >= threshold) {
    noteOn(0, 55, 60);
    delay(50);
    noteOff(0, 55, 60);
    delay(50);
    if (count4 == 0) {
      digitalWrite(led4, HIGH);
    }
    count4 = duration;
  }

  if (cap5 >= threshold) {
    noteOn(0, 57, 60);
    delay(50);
    noteOff(0, 57, 60);
    delay(50);
    if (count5 == 0) {
      digitalWrite(led5, HIGH);
    }
    count5 = duration;
  }

  if (cap6 >= threshold) {
    if (count6 == 0) {
      digitalWrite(led6, HIGH);
    }
    count6 = duration;
  }
}


/*MIDI BUSINESS*/
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {

  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

}

