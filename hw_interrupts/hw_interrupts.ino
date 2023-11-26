#define BUTTON_PIN 2
#define BOUNCE_TIME 50
#define PRESSED LOW

int previous = 0;
volatile long int press_time = 0;
volatile bool check_button = false;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(0, process_button_click, FALLING);

  cli(); // stop interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = (1 << TOIE1);
  TCCR1B |= (1 << CS10);
  pinMode(LED_BUILTIN, OUTPUT);
  sei(); // allow interrupts
}

ISR(TIMER1_OVF_vect)
{
  if(check_button && digitalRead(BUTTON_PIN) == PRESSED) {
    counter++;
    check_button = false;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  if (counter > 0) {
    Serial.print("clicked: ");
    Serial.println(counter);
    counter = 0;  
  }
}

void process_button_click() {
  if (!check_button) {
    press_time = millis();
    check_button = true;
  }
}