#define PNP_PIN1 9
#define PNP_PIN2 10

void setup()
{
  pinMode(PNP_PIN1, OUTPUT);
  pinMode(PNP_PIN2, OUTPUT);  
  Serial.println("Input fw *speed* for forward");
  Serial.println("Input bk *speed* for back");
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    String cmd = input.substring(0, 2);
    int speed = input.substring(3).toInt();
    if (speed > 255 || speed < 0) {
      Serial.println("Speed must be between 0 and 255");
      return;
    }
    if (cmd == "bk") {
      digitalWrite(PNP_PIN1, LOW);
      analogWrite(PNP_PIN2, speed);
    } else if (cmd == "fw") {
      digitalWrite(PNP_PIN2, LOW);
      analogWrite(PNP_PIN1, speed);
    }
  }
}
