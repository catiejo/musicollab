int led1 = 13;
int led2 = 12;
int led3 = 11;
int led4 = 10;

int button1 = 53;
int button2 = 52;
int button3 = 51;
int button4 = 50;

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;

int duration = 1;
int beat = 500;
int granularity = 10;

bool debug = false;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  digitalWrite(button1, LOW);
  digitalWrite(button2, LOW);
  digitalWrite(button3, LOW);
  digitalWrite(button4, LOW);
}

void loop() {
  if (debug == true) {
    debugPins(2);
  } else {
    debugPins(1);
  }
  debug = !debug;
  Serial.print("count is: ");
  Serial.print(count1);
  Serial.print("\n");
  if (count1 != 0) {
    digitalWrite(led1, HIGH);
    Serial.print("LED should be on");
    count1--;
  }
  delay(beat);
//  pollForPresses();
  digitalWrite(led1, LOW);
  Serial.print("LED should be off");
  if (count2 != 0) {
    digitalWrite(led2, HIGH);
    count2--;
  }
//  pollForPresses();
  digitalWrite(led2, LOW);
  if (count3 != 0) {
    digitalWrite(led3, HIGH);
    count3--;
  }
//  pollForPresses();
  digitalWrite(led3, LOW);
  if (count4 != 0) {
    digitalWrite(led4, HIGH);
    count4--;
  }
//  pollForPresses();
  digitalWrite(led4, LOW);
}

void pollForPresses() {
  for (int i=0; i < granularity; i++) {
    delay(beat/granularity);
    checkPins();
  }
}

void checkPins() {
  if (digitalRead(button1) == HIGH) {
    Serial.print("button 1 is pressed\n");
    count1 = duration;
  } else {
    Serial.print("button 1 is NOT pressed\n");
  }
  if (digitalRead(button2) == HIGH) {
//    Serial.print("button 2 is pressed\n");
    count2 = duration;
  }
  if (digitalRead(button3) == HIGH) {
//    Serial.print("button 3 is pressed\n");
    count3 = duration;
  }
  if (digitalRead(button4) == HIGH) {
//    Serial.print("button 4 is pressed\n");
    count4 = duration;
  }
}

void debugPins(int seq) {
  if (seq == 0) {
    //do nothing
  } else if (seq == 1) {
    digitalWrite(button1, HIGH);
    digitalWrite(button2, HIGH);
    digitalWrite(button3, HIGH);
    digitalWrite(button4, HIGH);
    checkPins();
  } else if (seq == 2) {
    digitalWrite(button1, LOW);
    digitalWrite(button2, LOW);
    digitalWrite(button3, LOW);
    digitalWrite(button4, LOW);
    checkPins();
  }
  delay(beat);
}

