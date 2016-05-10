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

//CapacitiveSensor cs_20_Y = CapacitiveSensor(20,31);
//CapacitiveSensor cs_20_26 = CapacitiveSensor(20,26);
CapacitiveSensor cs20 = CapacitiveSensor(20,25);
CapacitiveSensor cs19 = CapacitiveSensor(20,24);
CapacitiveSensor cs18 = CapacitiveSensor(20,23);
CapacitiveSensor cs17 = CapacitiveSensor(20,22);
CapacitiveSensor cs16 = CapacitiveSensor(20,22);
CapacitiveSensor cs15 = CapacitiveSensor(20,19);
CapacitiveSensor cs14 = CapacitiveSensor(20,18);
CapacitiveSensor cs13 = CapacitiveSensor(20,17);
CapacitiveSensor cs12 = CapacitiveSensor(20,16);
CapacitiveSensor cs11 = CapacitiveSensor(20,15);
CapacitiveSensor cs10 = CapacitiveSensor(20,14);
CapacitiveSensor cs9 = CapacitiveSensor(20,13);
CapacitiveSensor cs8 = CapacitiveSensor(20,12);
CapacitiveSensor cs7 = CapacitiveSensor(20,11);
CapacitiveSensor cs6 = CapacitiveSensor(20,10);
CapacitiveSensor cs5 = CapacitiveSensor(20,9);
CapacitiveSensor cs4 = CapacitiveSensor(20,8);
CapacitiveSensor cs3 = CapacitiveSensor(20,7);
CapacitiveSensor cs2 = CapacitiveSensor(20,6);
CapacitiveSensor cs1 = CapacitiveSensor(20,5);

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

int counts[21];

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
int granularity = 10;
int duration = 10;
long threshold = 400;

void setup() {
  //LEDs
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
  //Sensors
  cs20.set_CS_AutocaL_Millis(0xFFFFFFFF); //Calibrate the sensors...
  cs19.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs18.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs17.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs16.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs15.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs14.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs13.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs12.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs11.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs10.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs9.set_CS_AutocaL_Millis(0xFFFFFFFF);  
  cs8.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs7.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs6.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs5.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs4.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs3.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF);
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

void checkPins() {
  //Beat 1 
//  count1 = 600;
  count1 = (cs1.capacitiveSensor(1) >= threshold) ? duration : count1;
  count2 = (cs2.capacitiveSensor(1) >= threshold) ? duration : count2;
  count3 = (cs3.capacitiveSensor(1) >= threshold) ? duration : count3;
  count4 = (cs4.capacitiveSensor(1) >= threshold) ? duration : count4;
  count5 = (cs5.capacitiveSensor(1) >= threshold) ? duration : count5;
  //Beat 2
  count6 = (cs6.capacitiveSensor(1) >= threshold) ? duration : count6;
//  count7 = 600;
  count7 = (cs7.capacitiveSensor(1) >= threshold) ? duration : count7;
  count8 = (cs8.capacitiveSensor(1) >= threshold) ? duration : count8;
  count9 = (cs9.capacitiveSensor(1) >= threshold) ? duration : count9;
  count10 = (cs10.capacitiveSensor(1) >= threshold) ? duration : count10;
  //Beat 3
  count11 = (cs11.capacitiveSensor(1) >= threshold) ? duration : count11;
  count12 = (cs12.capacitiveSensor(1) >= threshold) ? duration : count12;
//  count13 = 600;
  count13 = (cs13.capacitiveSensor(1) >= threshold) ? duration : count13;
  count14 = (cs14.capacitiveSensor(1) >= threshold) ? duration : count14;
  count15 = (cs15.capacitiveSensor(1) >= threshold) ? duration : count15;
  Beat 4
  count16 = (cs16.capacitiveSensor(1) >= threshold) ? duration : count16;
  count17 = (cs17.capacitiveSensor(1) >= threshold) ? duration : count17;
  count18 = (cs18.capacitiveSensor(1) >= threshold) ? duration : count18;
//  count19 = 600;
  count19 = (cs19.capacitiveSensor(1) >= threshold) ? duration : count19;
  count20 = (cs20.capacitiveSensor(1) >= threshold) ? duration : count20;    
}

void playBeatOne() {
  if (count1 > 0) {
    if (count1 == 0) {
      digitalWrite(led1, HIGH);
    }
    noteOn(0, 48, 60);
  }
  if (count2 > 0) {
    if (count2 == 0) {
      digitalWrite(led1, HIGH);
    }
    noteOn(0, 50, 60);  
  }
  if (count3 > 0) {
    if (count3 == 0) {
      digitalWrite(led1, HIGH);
    }
    noteOn(0, 53, 60);  
  }
  if (count4 > 0) {
    if (count4 == 0) {
      digitalWrite(led1, HIGH);
    }
    noteOn(0, 55, 60);  
  }
  if (count5 > 0) {
    if (count5 == 0) {
      digitalWrite(led1, HIGH);
    }
    noteOn(0, 57, 60);   
  }
  delay(50);
  if (count1 > 0) {
    if (count1 == 0) {
      digitalWrite(led1, LOW);
    }
    noteOff(0, 48, 60);
    count1--;
  }
  if (count2 > 0) {
    if (count2 == 0) {
      digitalWrite(led2, LOW);
    }
    noteOff(0, 50, 60);  
    count2--;  
  }
  if (count3 > 0) {
    if (count3 == 0) {
      digitalWrite(led3, LOW);
    }
    noteOff(0, 53, 60);  
    count3--;  
  }
  if (count4 > 0) {
    if (count4 == 0) {
      digitalWrite(led4, LOW);
    }
    noteOff(0, 55, 60);  
    count4--;  
  }
  if (count5 > 0) {
    if (count5 == 0) {
      digitalWrite(led5, LOW);
    }
    noteOff(0, 57, 60);   
    count5--; 
  }
}

void playBeatTwo() {
  if (count6 > 0) {
    noteOn(0, 48, 60);
  }
  if (count7 > 0) {
    noteOn(0, 50, 60);  
  }
  if (count8 > 0) {
    noteOn(0, 53, 60);  
  }
  if (count9 > 0) {
    noteOn(0, 55, 60);  
  }
  if (count10 > 0) {
    noteOn(0, 57, 60);   
  }
  delay(50);
  if (count6 > 0) {
    if (count6 == 0) {
      digitalWrite(led6, LOW);
    }
    noteOff(0, 48, 60);
    count6--;
  }
  if (count7 > 0) {
    if (count7 == 0) {
      digitalWrite(led7, LOW);
    }
    noteOff(0, 50, 60);  
    count7--;  
  }
  if (count8 > 0) {
    if (count8 == 0) {
      digitalWrite(led8, LOW);
    }
    noteOff(0, 53, 60);  
    count8--;  
  }
  if (count9 > 0) {
    if (count9 == 0) {
      digitalWrite(led9, LOW);
    }
    noteOff(0, 55, 60);  
    count9--;  
  }
  if (count10 > 0) {
    if (count10 == 0) {
      digitalWrite(led10, LOW);
    }
    noteOff(0, 57, 60);   
    count10--; 
  }
}

void playBeatThree() {
  if (count11 > 0) {
    noteOn(0, 48, 60);
  }
  if (count12 > 0) {
    noteOn(0, 50, 60);  
  }
  if (count13 > 0) {
    noteOn(0, 53, 60);  
  }
  if (count14 > 0) {
    noteOn(0, 55, 60);  
  }
  if (count15 > 0) {
    noteOn(0, 57, 60);   
  }
  delay(50);
  if (count11 > 0) {
    if (count11 == 0) {
      digitalWrite(led11, LOW);
    }
    noteOff(0, 48, 60);
    count11--;
  }
  if (count12 > 0) {
    if (count12 == 0) {
      digitalWrite(led12, LOW);
    }
    noteOff(0, 50, 60);  
    count12--;  
  }
  if (count13 > 0) {
    if (count13 == 0) {
      digitalWrite(led13, LOW);
    }
    noteOff(0, 53, 60);  
    count13--;  
  }
  if (count14 > 0) {
    if (count14 == 0) {
      digitalWrite(led14, LOW);
    }
    noteOff(0, 55, 60);  
    count14--;  
  }
  if (count15 > 0) {
    if (count15 == 0) {
      digitalWrite(led15, LOW);
    }
    noteOff(0, 57, 60);   
    count15--; 
  }
}

void playBeatFour() {
  if (count16 > 0) {
    noteOn(0, 48, 60);
  }
  if (count17 > 0) {
    noteOn(0, 50, 60);  
  }
  if (count18 > 0) {
    noteOn(0, 53, 60);  
  }
  if (count19 > 0) {
    noteOn(0, 55, 60);  
  }
  if (count20 > 0) {
    noteOn(0, 57, 60);   
  }
  delay(50);
  if (count16 > 0) {
    if (count16 == 0) {
      digitalWrite(led16, LOW);
    }
    noteOff(0, 48, 60);
    count16--;
  }
  if (count17 > 0) {
    if (count17 == 0) {
      digitalWrite(led17, LOW);
    }
    noteOff(0, 50, 60);  
    count17--;  
  }
  if (count18 > 0) {
    if (count18 == 0) {
      digitalWrite(led18, LOW);
    }
    noteOff(0, 53, 60);  
    count18--;  
  }
  if (count19 > 0) {
    if (count19 == 0) {
      digitalWrite(led19, LOW);
    }
    noteOff(0, 55, 60);  
    count19--;  
  }
  if (count20 > 0) {
    if (count20 == 0) {
      digitalWrite(led20, LOW);
    }
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

