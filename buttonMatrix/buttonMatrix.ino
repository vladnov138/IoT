#define ROW1 8
#define ROW2 9
#define COL1 10
#define COL2 11

bool state = 0;
int lastChecksum = 0;

void setup() {
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool btnPressedArr[4] = {0, 0, 0, 0};
  bool isAnyPressed = false;
  int checksum = 0;
  int pressedNum = 0;
  for (int i = 0; i < 2; i++){
    digitalWrite(ROW1, state);
    state = !state;
    digitalWrite(ROW2, state);
    for (int j = 0; j < 2; j++) {
      byte btnIdx = i * 2 + j;
      int rowIdx = btnIdx < 2 ? ROW1 : ROW2;
      int colIdx = !(btnIdx % 2) ? COL1 : COL2;
      if (!digitalRead(rowIdx) && !digitalRead(colIdx)) {
        btnPressedArr[btnIdx] = 1;
        isAnyPressed = true;
        checksum += btnIdx * btnIdx + 1;
        pressedNum++;
      }
    }
  }
  if (isAnyPressed && checksum != lastChecksum){
    Serial.print("Pressed buttons: ");
    int k = 0;
    for (int i = 0; i < 4; i++) {
      if (btnPressedArr[i] == 1) {
        Serial.print(i + 1);
        if (pressedNum - 1 != k) {
          Serial.print(", ");
        }
        k++;
      }
    }
    Serial.println(" ");
  } else if (checksum != lastChecksum && !checksum) {
    Serial.println("No buttons pressed");
  }
  lastChecksum = checksum;
}