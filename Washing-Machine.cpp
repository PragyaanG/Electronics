int en  = 9;
int in1 = 7;
int in2 = 8;

int led = 4;
int buzzer = 5;

int maxSpeed = 120;
int stepSize = 5;
int stepDelay = 30;
int holdTime = 2000;

void setup() {
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

//LED

void motorMoving() {
  digitalWrite(led, HIGH);
}

void motorStopped() {
  digitalWrite(led, LOW);
}

//DIRECTION

void setForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void setReverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

//RAMPS

void rampUp(int targetSpeed) {
  motorMoving();
  for (int speed = 0; speed <= targetSpeed; speed += stepSize) {
    analogWrite(en, speed);
    delay(stepDelay);
  }
}

void rampDown(int startSpeed) {
  for (int speed = startSpeed; speed >= 0; speed -= stepSize) {
    analogWrite(en, speed);
    delay(stepDelay);
  }
  analogWrite(en, 0);
  motorStopped();
}

//BUZZER

void playBuzzer() {
  tone(buzzer, 1000);
  delay(800);
  noTone(buzzer);
}

//CYCLE

void loop() {

  setForward();
  rampUp(maxSpeed);
  delay(holdTime);
  rampDown(maxSpeed);

  delay(1000);

  setReverse();
  rampUp(maxSpeed);
  delay(holdTime);
  rampDown(maxSpeed);

  playBuzzer();

  delay(1000);
}
