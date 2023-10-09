#define LED_PIN 13

void setup(){
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  if (Serial.available() > 0){
    char cmd = Serial.read();
    if (cmd == 'u'){
      digitalWrite(LED_PIN, HIGH);
      Serial.print("Led is up!"); 
    } else if (cmd == 'd'){
      digitalWrite(LED_PIN, LOW);
      Serial.print("Led is down!");
    }
  }
}