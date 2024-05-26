#include <SoftwareSerial.h>

#define DIR_1        4 
#define SPEED_1      5 
#define SPEED_2      6 
#define DIR_2        7 

#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

// RX TX
SoftwareSerial bluetoothSerial(10, 11);

int states[4][2] = {
    {LOW, LOW},
    {LOW, HIGH},
    {HIGH, LOW},
    {HIGH, HIGH}
};

int calibratedIndices[] = {0, 0, 0, 0};
// right left rightTurning leftTurning
int calibratedSpeed[] = {255, 255, 100, 100};

bool calibrationMode = false;
int currentIdx = 0;
int speedIdx = 0;
bool keySelected = false;
bool isTurning = false;
bool speedCalibrationMode = false;

void move(int rightSideSpeed, int leftSideSpeed) {
  digitalWrite(DIR_1, states[calibratedIndices[currentIdx]][0]);
  digitalWrite(DIR_2, states[calibratedIndices[currentIdx]][1]);
  analogWrite(SPEED_1, abs(rightSideSpeed));
  analogWrite(SPEED_2, abs(leftSideSpeed));
}

void stop() {
  move(0, 0);
}

void forward() {
  move(calibratedSpeed[0], calibratedSpeed[1]);
}

void turn_left() {
  move(calibratedSpeed[0], calibratedSpeed[3]);
}

void turn_right() {
  move(calibratedSpeed[2], calibratedSpeed[1]);
}

void rotate_left() {
  move(255, 0);
}

void rotate_right() {
  move(0, 255);
}

void back() {
  move(-calibratedSpeed[0], -calibratedSpeed[1]);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  bluetoothSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetoothSerial.available()) {
    char cmd = bluetoothSerial.read();
    Serial.println(cmd);
    switch (cmd) {
      case FORWARD:
        if (speedCalibrationMode) {
          calibratedSpeed[speedIdx % 2] += 5;
          calibratedSpeed[speedIdx % 2] %= 255;
        } else {
          currentIdx = 0;
          keySelected = true;
        }
        forward();
        break;
      case BACKWARD:
        if (speedCalibrationMode) {
          calibratedSpeed[speedIdx % 2] -= 5;
          calibratedSpeed[speedIdx % 2] = abs(calibratedSpeed[speedIdx]);
          forward();
        } else {
          currentIdx = 1;
          keySelected = true;
          back();
        }
        break;
      case LEFT:
        if (speedCalibrationMode) {
          speedIdx = 1 + 2 * isTurning;
        } else {
          currentIdx = 2;
          keySelected = true;
          turn_left();
          isTurning = true;
        }
        break;
      case RIGHT:
        if (speedCalibrationMode) {
          speedIdx = 0 + 2 * isTurning;
        } else {
          currentIdx = 3;
          keySelected = true;
          turn_right();
          isTurning = true;
        }
        break;
      case CIRCLE:
        if (calibrationMode) {
          speedCalibrationMode = !speedCalibrationMode;
        }
        break;
      case CROSS:
        stop();
        break;
      case TRIANGLE:
        if (!speedCalibrationMode) {
          keySelected = false;
        } else {
          isTurning = !isTurning;
        }
        break;
      case SQUARE:
        if (keySelected && !speedCalibrationMode) {
          calibratedIndices[currentIdx] += 1;
          calibratedIndices[currentIdx] %= 4;
          Serial.println(calibratedIndices[currentIdx]);
        }
        break;
      case START:
        currentIdx = 0;
        keySelected = false;
        calibrationMode = true;
        Serial.println("Calibration started");
        break;
      case PAUSE:
        if (calibrationMode) {
          calibrationMode = false;
          Serial.println("Calibration finished");
        }
        break;
      default:
        break;
    }
  }
}
