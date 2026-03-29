const int buzzerPin = 10;

const int buttonPins[] = {9, 8, 7, 6, 5, 4, 3, 2};
const int numButtons = 8;

const int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  pinMode(buzzerPin, OUTPUT);
  
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  bool buttonPressed = false;

  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      tone(buzzerPin, notes[i]);
      buttonPressed = true;
      break;
    }
  }

  if (!buttonPressed) {
    noTone(buzzerPin);
  }
}
