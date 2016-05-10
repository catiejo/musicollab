#include <SoftwareSerial.h>
#include <CapacitiveSensor.h>

int led1 = 51;
int led2 = 50;
int led3 = 49;
int led4 = 48;
int led5 = 47;
int led6 = 46;
int led7 = 45;
int led8 = 44;
int led9 = 43;
int led10 = 42;
int led11 = 41;
int led12 = 40;
int led13 = 39;
int led14 = 38;
int led15 = 37;
int led16 = 36;
int led17 = 35;
int led18 = 34;
int led19 = 33;
int led20 = 32;

CapacitiveSensor cs_20_25 = CapacitiveSensor(20,24);
CapacitiveSensor cs_20_24 = CapacitiveSensor(20,24);
CapacitiveSensor cs_20_23 = CapacitiveSensor(20,23);
CapacitiveSensor cs_20_22 = CapacitiveSensor(20,22);
CapacitiveSensor cs_20_21 = CapacitiveSensor(20,22);
CapacitiveSensor cs_20_19 = CapacitiveSensor(20,19);
CapacitiveSensor cs_20_18 = CapacitiveSensor(20,18);
CapacitiveSensor cs_20_17 = CapacitiveSensor(20,17);
CapacitiveSensor cs_20_16 = CapacitiveSensor(20,16);
CapacitiveSensor cs_20_15 = CapacitiveSensor(20,15);
CapacitiveSensor cs_20_14 = CapacitiveSensor(20,14);
CapacitiveSensor cs_20_13 = CapacitiveSensor(20,13);
CapacitiveSensor cs_20_12 = CapacitiveSensor(20,12);
CapacitiveSensor cs_20_11 = CapacitiveSensor(20,11);
CapacitiveSensor cs_20_10 = CapacitiveSensor(20,10);
CapacitiveSensor cs_20_09 = CapacitiveSensor(20,9);
CapacitiveSensor cs_20_08 = CapacitiveSensor(20,8);
CapacitiveSensor cs_20_07 = CapacitiveSensor(20,7);
CapacitiveSensor cs_20_06 = CapacitiveSensor(20,6);
CapacitiveSensor cs_20_05 = CapacitiveSensor(20,5);

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
long cap11 = 0;
long cap12 = 0;
long cap13 = 0;
long cap14 = 0;
long cap15 = 0;
long cap16 = 0;
long cap17 = 0;
long cap18 = 0;
long cap19 = 0;
long cap20 = 0;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;
int count6 = 0;
int count7 = 0;
int count8 = 0;
int count9 = 0;
int count10 = 0;
int count11 = 0;
int count12 = 0;
int count13 = 0;
int count14 = 0;
int count15 = 0;
int count16 = 0;
int count17 = 0;
int count18 = 0;
int count19 = 0;
int count20 = 0;

int beat = 100;
int granularity = 5;
int duration = 2;
long threshold = 300;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(led14, OUTPUT);
  pinMode(led15, OUTPUT);
  pinMode(led16, OUTPUT);
  pinMode(led17, OUTPUT);
  pinMode(led18, OUTPUT);
  pinMode(led19, OUTPUT);
  pinMode(led20, OUTPUT);
  cs_20_25.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_24.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_23.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_22.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_22.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_21.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_19.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_18.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_17.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_16.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_15.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_14.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_13.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensors...
  cs_20_12.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_11.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_09.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_08.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_07.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_06.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs_20_05.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  mySerial.begin(31250); //Set up soft serial for music instrument sheild.
  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 120); //0xB0 is channel message, set channel volume to near max (127)
  talkMIDI(0xB0, 0, 0x00); //Default bank GM1
  talkMIDI(0xC0, 1, 0);
}

void loop() {
  playBeat(&count1, &count2, &count3, &count4, &count5);
  if (count1 == 0) {
    digitalWrite(led1, LOW);
  }
  if (count2 == 0) {
    digitalWrite(led2, LOW);
  }
  if (count3 == 0) {
    digitalWrite(led3, LOW);
  }
  if (count4 == 0) {
    digitalWrite(led4, LOW);
  }
  if (count5 == 0) {
    digitalWrite(led5, LOW);
  }
  pollForPresses();

  playBeat(&count6, &count7, &count8, &count9, &count10);
  if (count6 == 0) {
    digitalWrite(led6, LOW);
  }
  if (count7 == 0) {
    digitalWrite(led7, LOW);
  }
  if (count8 == 0) {
    digitalWrite(led8, LOW);
  }
  if (count9 == 0) {
    digitalWrite(led9, LOW);
  }
  if (count10 == 0) {
    digitalWrite(led10, LOW);
  }
  pollForPresses();

  playBeat(&count11, &count12, &count13, &count14, &count15);
  if (count11 == 0) {
    digitalWrite(led11, LOW);
  }
  if (count12 == 0) {
    digitalWrite(led12, LOW);
  }
  if (count13 == 0) {
    digitalWrite(led13, LOW);
  }
  if (count14 == 0) {
    digitalWrite(led14, LOW);
  }
  if (count15 == 0) {
    digitalWrite(led15, LOW);
  }
  pollForPresses();

  playBeat(&count16, &count17, &count18, &count19, &count20);
  if (count16 == 0) {
    digitalWrite(led16, LOW);
  }
  if (count17 == 0) {
    digitalWrite(led17, LOW);
  }
  if (count18 == 0) {
    digitalWrite(led18, LOW);
  }
  if (count19 == 0) {
    digitalWrite(led19, LOW);
  }
  if (count20 == 0) {
    digitalWrite(led20, LOW);
  }
  pollForPresses();
}

void pollForPresses() {
  for (int i = 0; i < granularity; i++) {
    delay(beat/granularity);
    checkPins();
  }
}

void checkPins() {  
  cap1 = cs_20_13.capacitiveSensor(10);
  cap2 = cs_20_12.capacitiveSensor(10);
  cap3 = cs_20_11.capacitiveSensor(10);
  cap4 = cs_20_10.capacitiveSensor(10);
  cap5 = cs_20_09.capacitiveSensor(10);
  cap6 = cs_20_08.capacitiveSensor(10);
  cap7 = cs_20_07.capacitiveSensor(10);
  cap8 = cs_20_06.capacitiveSensor(10);
  cap9 = cs_20_05.capacitiveSensor(10);
  cap10 = cs_20_14.capacitiveSensor(10);
  printCaps();
  

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

  if (cap4 >= threshold) {
    if (count4 == 0) {
      digitalWrite(led4, HIGH);
    }
    count4 = duration;
  }

  if (cap5 >= threshold) {
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

void playBeat(int* countC, int* countD, int* countF, int* countG, int* countA) {
  if (countC != 0) {
    noteOn(0, 48, 60);
  }
  if (countD > 0) {
    noteOn(0, 50, 60);  
  }
  if (countF > 0) {
    noteOn(0, 53, 60);  
  }
  if (countG > 0) {
    noteOn(0, 55, 60);  
  }
  if (countA > 0) {
    noteOn(0, 57, 60);   
  }
  delay(50);
  if (countC > 0) {
    noteOff(0, 48, 60);
    countC--;
  }
  if (countD > 0) {
    noteOff(0, 50, 60);  
    countD--;  
  }
  if (countF > 0) {
    noteOff(0, 53, 60);  
    countF--;  
  }
  if (countG > 0) {
    noteOff(0, 55, 60);  
    countG--;  
  }
  if (countA > 0) {
    noteOff(0, 57, 60);   
    countA--; 
  }
}

void printCaps() {
  Serial.print(cap1);
  Serial.print("\t");
  Serial.print(cap2);
  Serial.print("\t");
  Serial.print(cap3);
  Serial.print("\t");
  Serial.print(cap4);
  Serial.print("\t");
  Serial.print(cap5);
  Serial.print("\t");
  Serial.print(cap6);
  Serial.print("\t");
  Serial.print(cap7);
  Serial.print("\t");
  Serial.print(cap8);
  Serial.print("\t");
  Serial.print(cap9);
  Serial.print("\t");
  Serial.print(cap10);
  Serial.print("\t");
  Serial.print(cap11);
  Serial.print("\t");
  Serial.print(cap12);
  Serial.print("\t");
  Serial.print(cap13);
  Serial.print("\t");
  Serial.print(cap14);
  Serial.print("\t");
  Serial.print(cap15);
  Serial.print("\t");
  Serial.print(cap16);
  Serial.print("\t");
  Serial.print(cap17);
  Serial.print("\t");
  Serial.print(cap18);
  Serial.print("\t");
  Serial.print(cap19);
  Serial.print("\t");
  Serial.print(cap20);
  Serial.println();
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

