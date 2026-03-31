#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = A0;
int ledPin = 7;

const int numSamples = 10;
float readings[numSamples];
int index = 0;
float total = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);

  for(int i = 0; i < numSamples; i++) {
    readings[i] = 0;
  }
}

void loop() {

  int value = analogRead(sensorPin);
  float voltage = value * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  total -= readings[index];
  readings[index] = temperature;
  total += readings[index];

  index = (index + 1) % numSamples;

  float smoothTemp = total / numSamples;

  if(smoothTemp > 37.5) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temperature:");

  lcd.setCursor(0,1);
  lcd.print(smoothTemp);
  lcd.print(" C");

  delay(500);
}
