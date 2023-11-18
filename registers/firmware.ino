#define latchPin 5 // защелка
#define clockPin 6 // синхронизатор регистра сдвига
#define dataPin  4 // вход

// 2 3 4 5 6 7 8 9 
// A B . C D E G F
// bool digits[10][8] = {
//   {0,1,1,0,1,1,1,1},  // 0
//   {0,0,1,0,0,0,0,1},  // 1
//   {0,1,1,1,0,1,1,0},  // 2
//   {0,1,1,1,0,0,1,1},  // 3
//   {0,0,1,1,1,0,0,1},  // 4
//   {0,1,0,1,1,0,1,1},  // 5
//   {0,1,0,1,1,1,1,1},  // 6
//   {0,1,1,0,0,0,0,1},  // 7
//   {0,1,1,1,1,1,1,1},  // 8
//   {0,1,1,1,1,0,1,1}   // 9
// };

byte digits[10] = {
  0b01101111,
  0b00100001,
  0b01110110,
  0b01110011,
  0b00111001,
  0b01011011,
  0b01011111,
  0b01100001,
  0b01111111,
  0b01111011
};

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);

  for (int i = 0; i < 10; i++) {
    show_number(i);
    delay(500);
  }

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char user_input = Serial.read(); 
    int digit = (int)(user_input - '0');
    show_number(digit);
  }
}

void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  if(digit < 0 or digit > 9) {
    return;
  }
  shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
  // for (int i = 7; i >=0; i--) {
    // shift_and_set(digits[digit][i]);
  // }
  digitalWrite(latchPin, HIGH);
}

void shift_and_set(bool val) {
  digitalWrite(dataPin, val);
  digitalWrite(clockPin, HIGH);
  delay(10);
  digitalWrite(clockPin, LOW);
}
