#define DIR_1        4 
#define SPEED_1      5 
#define SPEED_2      6 
#define DIR_2        7 


#define LEFT_SIDE_ECHO 8
#define LEFT_SIDE_TRIGGER 9
#define FRONT_SIDE_ECHO 11
#define FRONT_SIDE_TRIGGER 12

const int LD = 23;
const int FD = 23;
const int CD = 16;
int ld = 0;
int fd = 0;

int prev_ld = 0;
int counter = 0;

void move(int rightSideSpeed, int leftSideSpeed) {
  digitalWrite(DIR_1, rightSideSpeed <= 0);
  digitalWrite(DIR_2, leftSideSpeed > 0);
  analogWrite(SPEED_1, abs(rightSideSpeed));
  analogWrite(SPEED_2, abs(leftSideSpeed));
}

void stop() {
  move(0, 0);
}

void forward() {
  move(255, 255);
}

void turn_left() {
  move(255, 100);
}

void turn_right() {
  move(100, 255);
}

void rotate_left() {
  move(255, 0);
}

void rotate_right() {
  move(0, 255);
}

void back() {
  // rotate_right();
  // rotate_right();
  move(-255, 255);
}

long get_distance(int triggerPin, int echoPin){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 29.1;
}

void setup() {
  Serial.begin(9600);
  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(LEFT_SIDE_ECHO, INPUT);
  pinMode(LEFT_SIDE_TRIGGER, OUTPUT);
  pinMode(FRONT_SIDE_ECHO, INPUT);
  pinMode(FRONT_SIDE_TRIGGER, OUTPUT);
}

bool isRotating = false;
long lastTime = millis();
int last_fd = FD * 2;

void loop() {
  fd = get_distance(FRONT_SIDE_TRIGGER, FRONT_SIDE_ECHO);
  ld = get_distance(LEFT_SIDE_TRIGGER, LEFT_SIDE_ECHO);

  Serial.print("Current state: ");
  if (fd < FD && ld < LD) {
    // stop();
    // delay(200);
    rotate_right();
    Serial.println("ROTATE RIGHT");
    // delay(300);
  }
  else if (ld > LD && fd < FD) {
    // stop();
    // delay(200);
    rotate_left();
    Serial.println("ROTATE LEFT");
  }
  else if (ld < CD - 3 && prev_ld < CD) {
    turn_right();
    Serial.println("TURN RIGHT");
    delay(100);
  }
  else if (ld > CD && prev_ld > CD) {
    turn_left();
    Serial.println("TURN LEFT");
    delay(100);
  } else if (last_fd > FD + 5) {
    forward();
    Serial.println("FORWARD");
  }  if (fd <= 5) {
    back();
    Serial.println("BACK");
    delay(500);
  }
  
  if (millis() - lastTime > 500) {
    prev_ld = ld;
    last_fd = fd;
    lastTime = millis();
  }
  
  Serial.println("Current fd & ld: ");
  Serial.print(fd);
  Serial.print(" ");
  Serial.println(ld);
  // delay(500);
}
