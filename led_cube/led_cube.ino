const int ledpins[] = {3, 5, 6, 9};
const int groundpins[] = {12, 13};
const int numLeds = sizeof(ledpins) / sizeof(ledpins[0]);
const int numGrounds = sizeof(groundpins) / sizeof(groundpins[0]);
const int delayTime = 100;

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledpins[i], OUTPUT);
  }
  for (int i = 0; i < numGrounds; i++) {
    pinMode(groundpins[i], OUTPUT);
  }
}

void loop() {
  twist();
  drop();
  diagonal();
}

void twist() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(groundpins[0], HIGH);
    delay(delayTime);
    digitalWrite(ledpins[i], HIGH);
    delay(delayTime);
    digitalWrite(ledpins[i], LOW);
    delay(delayTime);
    digitalWrite(groundpins[0], LOW);
  }
}

void drop() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(groundpins[0], HIGH);
    digitalWrite(ledpins[i], HIGH);
    delay(delayTime);
    digitalWrite(groundpins[0], LOW);
    digitalWrite(groundpins[1], HIGH);
    delay(delayTime);
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[i], LOW);
  }
}

void diagonal() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(groundpins[1], HIGH);
    digitalWrite(ledpins[i % numLeds], HIGH);
    delay(delayTime);
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[i % numLeds], LOW);
    delay(delayTime);
  }
}