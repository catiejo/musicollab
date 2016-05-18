#include <SoftwareSerial.h>
#include <CapacitiveSensor.h>

//Beat 1
int led1C = 41;
int led1D = 40;
int led1F = 39;
int led1G = 38;
int led1A = 37;
//Beat 2
int led2C = 36;
int led2D = 35;
int led2F = 34;
int led2G = 33;
int led2A = 32;
//Beat 3
int led3C = 51;
int led3D = 50;
int led3F = 49;
int led3G = 48;
int led3A = 47;
//Beat 4
int led4C = 46;
int led4D = 45;
int led4F = 44;
int led4G = 43;
int led4A = 42;

//Beat 1:
CapacitiveSensor cs1C = CapacitiveSensor(20,13);
CapacitiveSensor cs1D = CapacitiveSensor(20,11);
CapacitiveSensor cs1F = CapacitiveSensor(20,12);
CapacitiveSensor cs1G = CapacitiveSensor(20,10);
CapacitiveSensor cs1A = CapacitiveSensor(20,14);
//Beat 2:
CapacitiveSensor cs2C = CapacitiveSensor(20,9);
CapacitiveSensor cs2D = CapacitiveSensor(20,8);
CapacitiveSensor cs2F = CapacitiveSensor(20,7);
CapacitiveSensor cs2G = CapacitiveSensor(20,6);
CapacitiveSensor cs2A = CapacitiveSensor(20,5);
//Beat 3:
CapacitiveSensor cs3C = CapacitiveSensor(20,30);
CapacitiveSensor cs3D = CapacitiveSensor(20,23);
CapacitiveSensor cs3F = CapacitiveSensor(20,25);
CapacitiveSensor cs3G = CapacitiveSensor(20,27);
CapacitiveSensor cs3A = CapacitiveSensor(20,22);
//Beat 4:
CapacitiveSensor cs4C = CapacitiveSensor(20,29);
CapacitiveSensor cs4D = CapacitiveSensor(20,28);
CapacitiveSensor cs4F = CapacitiveSensor(20,31);
CapacitiveSensor cs4G = CapacitiveSensor(20,24);
CapacitiveSensor cs4A = CapacitiveSensor(20,26);

SoftwareSerial mySerial(2, 3); // RX, TX
byte resetMIDI = 4; //Tied to VS1053 Reset line

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

int beat = 100; //tempo
int granularity = 10; //how often the beat length is interrupted to check sensors
int duration = 8; //number of times a note repeats
long threshold = 420; //sensor threshold for indicating a touch

void setup() {
  //LEDs
  pinMode(led1C, OUTPUT);
  pinMode(led1D, OUTPUT);
  pinMode(led1F, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1A, OUTPUT);
  pinMode(led2C, OUTPUT);
  pinMode(led2D, OUTPUT);
  pinMode(led2F, OUTPUT);
  pinMode(led2G, OUTPUT);
  pinMode(led2A, OUTPUT);
  pinMode(led3C, OUTPUT);
  pinMode(led3D, OUTPUT);
  pinMode(led3F, OUTPUT);
  pinMode(led3G, OUTPUT);
  pinMode(led3A, OUTPUT);
  pinMode(led4C, OUTPUT);
  pinMode(led4D, OUTPUT);
  pinMode(led4F, OUTPUT);
  pinMode(led4G, OUTPUT);
  pinMode(led4A, OUTPUT);
  //Sensors
  cs1C.set_CS_AutocaL_Millis(0xFFFFFFFF); //Calibrate the sensors...
  cs1D.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs1F.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs1G.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs1A.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2C.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2D.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2F.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2G.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2A.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3C.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3D.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3F.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3G.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3A.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4C.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4D.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4F.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4G.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4A.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);
  //Midi
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
  playBeatOne();
  pollForPresses();
  playBeatTwo();
  pollForPresses();
  playBeatThree();
  pollForPresses();
  playBeatFour();
  pollForPresses();
}

void pollForPresses() {
  for (int i = 0; i < granularity; i++) {
    delay(beat/granularity);
    checkPins();
  }
}

void printCaps() {
//  Serial.print(cs1C.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs1D.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs1F.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs1G.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs1A.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs2C.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs2D.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs2F.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs2G.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs2A.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs3C.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs3D.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs3F.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs3G.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs3A.capacitiveSensor(1));
//  Serial.print("\t");
  Serial.print(cs4C.capacitiveSensor(1));
  Serial.print("\t");
  Serial.print(cs4D.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs4F.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs4G.capacitiveSensor(1));
//  Serial.print("\t");
//  Serial.print(cs4A.capacitiveSensor(1));
  Serial.println();
//  delay(5); //slow so the screen doesn't go by too fast.
}

void checkPins() {
  printCaps(); //DEBUGGING
  //Beat 1
  count1 = (cs1C.capacitiveSensor(1) >= threshold) ? duration : count1;
  count2 = (cs1D.capacitiveSensor(1) >= threshold) ? duration : count2; //loose solder pin 6
  count3 = (cs1F.capacitiveSensor(1) >= threshold) ? duration : count3;
  count4 = (cs1G.capacitiveSensor(1) >= threshold) ? duration : count4;
  count5 = (cs1A.capacitiveSensor(1) >= threshold) ? duration : count5;
  //Beat 2
  count6 = (cs2C.capacitiveSensor(1) >= threshold) ? duration : count6;
  count7 = (cs2D.capacitiveSensor(1) >= threshold) ? duration : count7;
  count8 = (cs2F.capacitiveSensor(1) >= threshold) ? duration : count8;
  count9 = (cs2G.capacitiveSensor(1) >= threshold) ? duration : count9;
  count10 = (cs2A.capacitiveSensor(1) >= threshold) ? duration : count10;
  //Beat 3
  count11 = (cs3C.capacitiveSensor(1) >= threshold) ? duration : count11;
  count12 = (cs3D.capacitiveSensor(1) >= threshold) ? duration : count12;
  count13 = (cs3F.capacitiveSensor(1) >= threshold) ? duration : count13;
  count14 = (cs3G.capacitiveSensor(1) >= threshold) ? duration : count14;
  count15 = (cs3A.capacitiveSensor(1) >= threshold) ? duration : count15;
  //Beat 4
  count16 = (cs4C.capacitiveSensor(1) >= threshold) ? duration : count16;
  count17 = (cs4D.capacitiveSensor(1) >= threshold) ? duration : count17;
  count18 = (cs4F.capacitiveSensor(1) >= threshold) ? duration : count18;
  count19 = (cs4G.capacitiveSensor(1) >= threshold) ? duration : count19;
  count20 = (cs4A.capacitiveSensor(1) >= threshold) ? duration : count20;
}

void playBeatOne() {
  if (count1 > 0) {
    digitalWrite(led1C, HIGH);
    noteOn(0, 48, 60);
  }
  if (count2 > 0) {
    digitalWrite(led1D, HIGH);
    noteOn(0, 50, 60);
  }
  if (count3 > 0) {
    digitalWrite(led1F, HIGH);
    noteOn(0, 53, 60);
  }
  if (count4 > 0) {
    digitalWrite(led1G, HIGH);
    noteOn(0, 55, 60);
  }
  if (count5 > 0) {
    digitalWrite(led1A, HIGH);
    noteOn(0, 57, 60);
  }
  delay(50);
  if (count1 > 0) {
    digitalWrite(led1C, LOW);
    noteOff(0, 48, 60);
    count1--;
  }
  if (count2 > 0) {
    digitalWrite(led1D, LOW);
    noteOff(0, 50, 60);
    count2--;
  }
  if (count3 > 0) {
    digitalWrite(led1F, LOW);
    noteOff(0, 53, 60);
    count3--;
  }
  if (count4 > 0) {
    digitalWrite(led1G, LOW);
    noteOff(0, 55, 60);
    count4--;
  }
  if (count5 > 0) {
    digitalWrite(led1A, LOW);
    noteOff(0, 57, 60);
    count5--;
  }
}

void playBeatTwo() {
  if (count6 > 0) {
    digitalWrite(led2C, HIGH);
    noteOn(0, 48, 60);
  }
  if (count7 > 0) {
    digitalWrite(led2D, HIGH);
    noteOn(0, 50, 60);
  }
  if (count8 > 0) {
    digitalWrite(led2F, HIGH);
    noteOn(0, 53, 60);
  }
  if (count9 > 0) {
    digitalWrite(led2G, HIGH);
    noteOn(0, 55, 60);
  }
  if (count10 > 0) {
    digitalWrite(led2A, HIGH);
    noteOn(0, 57, 60);
  }
  delay(50);
  if (count6 > 0) {
    digitalWrite(led2C, LOW);
    noteOff(0, 48, 60);
    count6--;
  }
  if (count7 > 0) {
    digitalWrite(led2D, LOW);
    noteOff(0, 50, 60);
    count7--;
  }
  if (count8 > 0) {
    digitalWrite(led2F, LOW);
    noteOff(0, 53, 60);
    count8--;
  }
  if (count9 > 0) {
    digitalWrite(led2G, LOW);
    noteOff(0, 55, 60);
    count9--;
  }
  if (count10 > 0) {
    digitalWrite(led2A, LOW);
    noteOff(0, 57, 60);
    count10--;
  }
}

void playBeatThree() {
  if (count11 > 0) {
    digitalWrite(led3C, HIGH);
    noteOn(0, 48, 60);
  }
  if (count12 > 0) {
    digitalWrite(led3D, HIGH);
    noteOn(0, 50, 60);
  }
  if (count13 > 0) {
    digitalWrite(led3F, HIGH);
    noteOn(0, 53, 60);
  }
  if (count14 > 0) {
    digitalWrite(led3G, HIGH);
    noteOn(0, 55, 60);
  }
  if (count15 > 0) {
    digitalWrite(led3A, HIGH);
    noteOn(0, 57, 60);
  }
  delay(50);
  if (count11 > 0) {
    digitalWrite(led3C, LOW);
    noteOff(0, 48, 60);
    count11--;
  }
  if (count12 > 0) {
    digitalWrite(led3D, LOW);
    noteOff(0, 50, 60);
    count12--;
  }
  if (count13 > 0) {
    digitalWrite(led3F, LOW);
    noteOff(0, 53, 60);
    count13--;
  }
  if (count14 > 0) {
    digitalWrite(led3G, LOW);
    noteOff(0, 55, 60);
    count14--;
  }
  if (count15 > 0) {
    digitalWrite(led3A, LOW);
    noteOff(0, 57, 60);
    count15--;
  }
}

void playBeatFour() {
  if (count16 > 0) {
    digitalWrite(led4C, HIGH);
    noteOn(0, 48, 60);
  }
  if (count17 > 0) {
    digitalWrite(led4D, HIGH);
    noteOn(0, 50, 60);
  }
  if (count18 > 0) {
    digitalWrite(led4F, HIGH);
    noteOn(0, 53, 60);
  }
  if (count19 > 0) {
    digitalWrite(led4G, HIGH);
    noteOn(0, 55, 60);
  }
  if (count20 > 0) {
    digitalWrite(led4A, HIGH);
    noteOn(0, 57, 60);
  }
  delay(50);
  if (count16 > 0) {
    digitalWrite(led4C, LOW);
    noteOff(0, 48, 60);
    count16--;
  }
  if (count17 > 0) {
    digitalWrite(led4D, LOW);
    noteOff(0, 50, 60);
    count17--;
  }
  if (count18 > 0) {
    digitalWrite(led4F, LOW);
    noteOff(0, 53, 60);
    count18--;
  }
  if (count19 > 0) {
    digitalWrite(led4G, LOW);
    noteOff(0, 55, 60);
    count19--;
  }
  if (count20 > 0) {
    digitalWrite(led4A, LOW);
    noteOff(0, 57, 60);
    count20--;
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
